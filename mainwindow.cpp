#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include "materiel.h"
#include "connection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QSqlError>
#include <QDateTime>
#include <QtPrintSupport/QPrinter>
#include <QPrintDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Boutons menu
    connect(ui->btn_staff,    &QPushButton::clicked, this, &MainWindow::showStaff);
    connect(ui->btn_client,   &QPushButton::clicked, this, &MainWindow::showClient);
    connect(ui->btn_materiel, &QPushButton::clicked, this, &MainWindow::showMateriel);
    connect(ui->btn_projet,   &QPushButton::clicked, this, &MainWindow::showProjet);
    connect(ui->btn_sponsor,  &QPushButton::clicked, this, &MainWindow::showSponsor);
    connect(ui->btn_createur, &QPushButton::clicked, this, &MainWindow::showCreateur);

    ui->stackedWidget->setCurrentIndex(0);
    afficherTableau();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Navigation
void MainWindow::showStaff()    { ui->stackedWidget->setCurrentIndex(0); }
void MainWindow::showClient()   { ui->stackedWidget->setCurrentIndex(1); }
void MainWindow::showMateriel() { ui->stackedWidget->setCurrentIndex(2); }
void MainWindow::showProjet()   { ui->stackedWidget->setCurrentIndex(3); }
void MainWindow::showSponsor()  { ui->stackedWidget->setCurrentIndex(4); }
void MainWindow::showCreateur() { ui->stackedWidget->setCurrentIndex(5); }

//


void MainWindow::afficherTableau()
{
    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");

    if (!db.isOpen()) {
        qDebug() << "❌ Base non ouverte dans afficherTableau()";
        if (!Connection::instance()->createconnect()) {
            QMessageBox::critical(this, "Erreur", "Connexion à la base échouée !");
            return;
        }
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM materiel")) {
        qDebug() << "❌ Erreur SELECT:" << query.lastError().text();
        return;
    }

    ui->tableWidget_4->setRowCount(0);
    int row = 0;

    while (query.next()) {
        ui->tableWidget_4->insertRow(row);
        ui->tableWidget_4->setItem(row, 0, new QTableWidgetItem(query.value("id_materiel").toString()));
        ui->tableWidget_4->setItem(row, 1, new QTableWidgetItem(query.value("nom").toString()));
        ui->tableWidget_4->setItem(row, 2, new QTableWidgetItem(query.value("type").toString()));
        ui->tableWidget_4->setItem(row, 3, new QTableWidgetItem(query.value("etat").toString()));
        ui->tableWidget_4->setItem(row, 4, new QTableWidgetItem(query.value("localisation").toString()));
        row++;
    }

    qDebug() << "[AFFICHAGE] Tableau mis à jour avec" << row << " lignes.";
}




void MainWindow::on_ajouter_clicked()
{
    QString idstr = ui->id_materiel->text().trimmed();
    QString nom = ui->nom->text().trimmed();
    QString type = ui->type->text().trimmed();
    QString etat = recupererEtat();
    // Récupération de la localisation à partir des 3 checkboxes
    QString localisation;
    int nbCoches = 0;

    if (ui->studio_tournage->isChecked()) {
        localisation = "Studio tournage";
        nbCoches++;
    }
    if (ui->salle_montage->isChecked()) {
        localisation = "Salle montage";
        nbCoches++;
    }
    if (ui->salle_podcast->isChecked()) {
        localisation = "Salle podcast";
        nbCoches++;
    }

    // ⚠️ Si plus d'une case est cochée, erreur
    if (nbCoches > 1) {
        QMessageBox::warning(this, "Erreur", "Veuillez choisir une seule localisation !");
        return;
    }

    qDebug() << "[AJOUT] appel -> id_materiel:" << idstr << "nom:" << nom << "type:" << type << "etat:" << etat << "loc:" << localisation;

    if (idstr.isEmpty() || nom.isEmpty() || type.isEmpty() || etat.isEmpty() || localisation.isEmpty()) {
        qDebug() << "[AJOUT] champs manquants";
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs.");
        return;
    }
    bool ok;
    int id_materiel = idstr.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Erreur", "L'ID doit être un nombre entier !");
        return;
    }
    if (idstr.length() != 8) {
        QMessageBox::warning(this, "Erreur", "L'ID doit contenir exactement 8 caractères !");
        return;
    }
    if (!nom.at(0).isUpper()) {
        QMessageBox::warning(this, "Erreur Nom", "Le nom doit commencer par une lettre majuscule !");
        return;
    }

    // Empêcher doublon d'ID : si un élément a déjà cet id, on refuse (ou on modifie selon ton choix)
    for (const Materiel &m : qAsConst(listeMateriel)) {
        if (m.getId() == idstr) {
            qDebug() << "[AJOUT] doublon id détecté:" << id_materiel;
            QMessageBox::warning(this, "Doublon", "Un matériel avec cet ID existe déjà.");
            return;
        }
    }

    // Construire et stocker
    Materiel m(idstr, nom, type, etat, localisation);
    listeMateriel.append(m);
    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");
    if (!db.isOpen()) {
        db.open();
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO materiel (id_materiel, nom, type, etat, localisation) "
                  "VALUES (:id_materiel, :nom, :type, :etat, :localisation)");
    query.bindValue(":id_materiel", idstr);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    query.bindValue(":localisation", localisation);

    if (!query.exec()) {
        qDebug() << "[AJOUT SQL] Erreur:" << query.lastError().text();
        QMessageBox::critical(this, "Erreur Base", "Échec de l’ajout dans la base !");
    } else {
        qDebug() << "[AJOUT SQL] Insertion réussie dans la base";
    }


    // Insérer dans table (synchronisé avec liste)
    int row = ui->tableWidget_4->rowCount();
    ui->tableWidget_4->insertRow(row);
    ui->tableWidget_4->setItem(row, 0, new QTableWidgetItem(m.getId()));
    ui->tableWidget_4->setItem(row, 1, new QTableWidgetItem(m.getNom()));
    ui->tableWidget_4->setItem(row, 2, new QTableWidgetItem(m.getType()));
    ui->tableWidget_4->setItem(row, 3, new QTableWidgetItem(m.getEtat()));
    ui->tableWidget_4->setItem(row, 4, new QTableWidgetItem(m.getLocalisation()));

    QMessageBox::information(this, "Ajout", "Matériel ajouté avec succès !");
}

// ✏️ Modifier
void MainWindow::on_modifier_clicked()
{
    QString idstr = ui->id_materiel->text().trimmed();
    QString nom = ui->nom->text().trimmed();
    QString type = ui->type->text().trimmed();
    QString etat = recupererEtat();

    // Récupérer localisation (même logique que ajout)
    QString localisation;
    int nbCoches = 0;
    if (ui->studio_tournage->isChecked()) { localisation = "Studio tournage"; nbCoches++; }
    if (ui->salle_montage->isChecked())   { localisation = "Salle montage"; nbCoches++; }
    if (ui->salle_podcast->isChecked())   { localisation = "Salle podcast"; nbCoches++; }
    if (nbCoches > 1) {
        QMessageBox::warning(this, "Erreur", "Veuillez choisir une seule localisation !");
        return;
    }

    if (idstr.isEmpty() || nom.isEmpty() || type.isEmpty() || etat.isEmpty() || localisation.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Remplis tous les champs !");
        return;
    }

    // ✅ 1. Mettre à jour dans la base
    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");
    if (!db.isOpen()) db.open();

    QSqlQuery query(db);
    query.prepare("UPDATE materiel "
                  "SET nom = :nom, type = :type, etat = :etat, localisation = :localisation "
                  "WHERE id_materiel = :id_materiel");
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    query.bindValue(":localisation", localisation);
    query.bindValue(":id_materiel", idstr);

    if (!query.exec()) {
        qDebug() << "[MODIF SQL] Erreur:" << query.lastError().text();
        QMessageBox::critical(this, "Erreur", "Échec de la mise à jour dans la base !");
        return;
    } else {
        qDebug() << "[MODIF SQL] ✅ Mise à jour réussie dans la base";
    }

    // ✅ 2. Mettre à jour dans la liste interne
    for (int i = 0; i < listeMateriel.size(); ++i) {
        if (listeMateriel[i].getId() == idstr) {
            listeMateriel[i] = Materiel(idstr, nom, type, etat, localisation);
            break;
        }
    }

    // ✅ 3. Mettre à jour dans le tableau
    for (int r = 0; r < ui->tableWidget_4->rowCount(); ++r) {
        if (ui->tableWidget_4->item(r, 0) && ui->tableWidget_4->item(r, 0)->text() == idstr) {
            ui->tableWidget_4->setItem(r, 1, new QTableWidgetItem(nom));
            ui->tableWidget_4->setItem(r, 2, new QTableWidgetItem(type));
            ui->tableWidget_4->setItem(r, 3, new QTableWidgetItem(etat));
            ui->tableWidget_4->setItem(r, 4, new QTableWidgetItem(localisation));
            break;
        }
    }

    QMessageBox::information(this, "Modification", "✅ Matériel modifié avec succès !");
}


//
// ❌ SUPPRIMER
//
void MainWindow::on_supprimer_clicked()
{
    QList<QTableWidgetItem *> selection = ui->tableWidget_4->selectedItems();
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Suppression", "⚠️ Sélectionnez une ligne à supprimer !");
        return;
    }

    int row = selection.first()->row();
    QString idstr = ui->tableWidget_4->item(row, 0)->text();

    // ✅ 1. Supprimer de la base
    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");
    if (!db.isOpen()) db.open();

    QSqlQuery query(db);
    query.prepare("DELETE FROM materiel WHERE id_materiel = :id_materiel");
    query.bindValue(":id_materiel", idstr);

    if (!query.exec()) {
        qDebug() << "[SUPPR SQL] Erreur:" << query.lastError().text();
        QMessageBox::critical(this, "Erreur", "Échec de la suppression dans la base !");
        return;
    } else {
        qDebug() << "[SUPPR SQL] ✅ Suppression réussie dans la base";
    }

    // ✅ 2. Supprimer de la liste interne
    for (int i = 0; i < listeMateriel.size(); ++i) {
        if (listeMateriel[i].getId() == idstr) {
            listeMateriel.removeAt(i);
            break;
        }
    }

    // ✅ 3. Supprimer du tableau
    ui->tableWidget_4->removeRow(row);

    QMessageBox::information(this, "Suppression", "🗑️ Matériel supprimé avec succès !");
}


//
// 🖱️ Quand on clique sur une ligne
//
void MainWindow::on_tableWidget_4_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();
    ui->id_materiel->setText(ui->tableWidget_4->item(row, 0)->text());
    ui->nom->setText(ui->tableWidget_4->item(row, 1)->text());
    ui->type->setText(ui->tableWidget_4->item(row, 2)->text());

    QString etat = ui->tableWidget_4->item(row, 3)->text();
    ui->fonctionnel->setChecked(etat == "Fonctionnel");
    ui->en_panne->setChecked(etat == "En panne");
    ui->en_maintenance->setChecked(etat == "En maintenance");
    ui->hors_service->setChecked(etat == "Hors service");

    QString localisation = ui->tableWidget_4->item(row, 4)->text();
    ui->studio_tournage->setChecked(localisation == "Studio tournage");
    ui->salle_montage->setChecked(localisation == "Salle montage");
    ui->salle_podcast->setChecked(localisation == "Salle podcast");
}

//
// 👁️ AFFICHER
//
void MainWindow::on_afficher_clicked()
{
    ui->tableWidget_4->setRowCount(listeMateriel.size());
    for (int i = 0; i < listeMateriel.size(); ++i) {
        const Materiel &m = listeMateriel[i];
        ui->tableWidget_4->setItem(i, 0, new QTableWidgetItem(m.getId()));
        ui->tableWidget_4->setItem(i, 1, new QTableWidgetItem(m.getNom()));
        ui->tableWidget_4->setItem(i, 2, new QTableWidgetItem(m.getType()));
        ui->tableWidget_4->setItem(i, 3, new QTableWidgetItem(m.getEtat()));
        ui->tableWidget_4->setItem(i, 4, new QTableWidgetItem(m.getLocalisation()));
    }
    afficherTableau();
}

//
// 🔍 CHERCHER
//
void MainWindow::on_chercher_2_clicked()
{
    QString recherche = ui->chercher->text().trimmed();

    if (recherche.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un ID à rechercher !");
        return;
    }

    QList<Materiel> resultats;

    // ----------------------------
    // 1️⃣ Recherche dans la base
    // ----------------------------
    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");
    if (!db.isOpen()) {
        db.open();
    }

    if (db.isOpen()) {
        QSqlQuery query(db);
        query.prepare("SELECT id_materiel, nom, type, etat, localisation "
                      "FROM materiel WHERE id_materiel = :id");
        query.bindValue(":id", recherche);

        if (!query.exec()) {
            QMessageBox::critical(this, "Erreur", "Échec de la recherche dans la base : " + query.lastError().text());
        } else {
            while (query.next()) {
                Materiel m;
                m.setId(query.value(0).toString());
                m.setNom(query.value(1).toString());
                m.setType(query.value(2).toString());
                m.setEtat(query.value(3).toString());
                m.setLocalisation(query.value(4).toString());
                resultats.append(m);
            }
        }
    } else {
        qDebug() << "[CHERCHE] Base non ouverte.";
    }

    // ----------------------------
    // 2️⃣ Si rien trouvé dans la base → chercher dans la liste locale
    // ----------------------------
    if (resultats.isEmpty()) {
        for (const Materiel &m : qAsConst(listeMateriel)) {
            if (m.getId() == recherche) {
                resultats.append(m);
                break; // ID unique
            }
        }
    }

    // ----------------------------
    // 3️⃣ Mise à jour du tableau
    // ----------------------------
    ui->tableWidget_4->clear();
    ui->tableWidget_4->setRowCount(resultats.size());
    ui->tableWidget_4->setColumnCount(5);
    ui->tableWidget_4->setHorizontalHeaderLabels(
        QStringList() << "ID" << "Nom" << "Type" << "État" << "Localisation"
        );

    for (int i = 0; i < resultats.size(); ++i) {
        const Materiel &m = resultats[i];
        ui->tableWidget_4->setItem(i, 0, new QTableWidgetItem(m.getId()));
        ui->tableWidget_4->setItem(i, 1, new QTableWidgetItem(m.getNom()));
        ui->tableWidget_4->setItem(i, 2, new QTableWidgetItem(m.getType()));
        ui->tableWidget_4->setItem(i, 3, new QTableWidgetItem(m.getEtat()));
        ui->tableWidget_4->setItem(i, 4, new QTableWidgetItem(m.getLocalisation()));
    }

    // ----------------------------
    // 4️⃣ Résultat message
    // ----------------------------
    if (resultats.isEmpty()) {
        QMessageBox::information(this, "Résultat", "Aucun matériel trouvé avec cet ID !");
    } else {
        QMessageBox::information(this, "Résultat", "✅ Matériel trouvé !");
    }
}




QString MainWindow::recupererEtat()
{
    QString etat;
    if (ui->en_panne->isChecked())
        etat = "En panne";
    else if (ui->fonctionnel->isChecked())
        etat = "Fonctionnel";
    else if (ui->en_maintenance->isChecked())
        etat = "En maintenance";
    else if (ui->hors_service->isChecked())
        etat = "hors service";
    else
        etat = "Inconnu";
    return etat;
}

QString MainWindow::recupererLocalisation() {
    QStringList locs;

    if (ui->studio_tournage->isChecked()) locs << "Studio Tournage";
    if (ui->salle_montage->isChecked()) locs << "Salle Montage";
    if (ui->salle_podcast->isChecked()) locs << "Salle Podcast";

    // Joindre les localisations choisies séparées par une virgule
    return locs.join(", ");
}


void MainWindow::on_exporter_clicked()
{
    // Choisir le chemin du PDF
    QString filePath = QFileDialog::getSaveFileName(this, "Exporter en PDF", "materiels_export.pdf", "Fichiers PDF (*.pdf)");
    if (filePath.isEmpty())
        return;

    QString html;
    html += "<html><head><meta charset='UTF-8'>";
    html += "<style>"
            "table { border-collapse: collapse; width: 100%; font-size: 10pt; }"
            "th, td { border: 1px solid black; padding: 6px; text-align: center; }"
            "th { background-color: #f0f0f0; }"
            "h2 { text-align: center; }"
            "</style></head><body>";

    html += "<h2>📋 Liste du matériel exportée</h2>";
    html += "<p>Date d'exportation : " + QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss") + "</p>";
    html += "<table><tr><th>ID</th><th>Nom</th><th>Type</th><th>État</th><th>Localisation</th></tr>";

    // Connexion à la base
    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");
    if (!db.isOpen())
        db.open();

    if (!db.isOpen()) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir la base : " + db.lastError().text());
        return;
    }

    // 🔹 Étape 1 : Récupérer tous les ID présents dans la table actuelle (ceux visibles à l'écran)
    QStringList idsTable;
    for (int i = 0; i < ui->tableWidget_4->rowCount(); ++i) {
        QTableWidgetItem *item = ui->tableWidget_4->item(i, 0); // colonne ID
        if (item)
            idsTable << item->text();
    }

    if (idsTable.isEmpty()) {
        QMessageBox::information(this, "Exportation", "Aucun élément à exporter (table vide).");
        return;
    }

    // 🔹 Étape 2 : Préparer la requête SQL pour ne sélectionner que les ID présents dans la table
    QString condition = "('" + idsTable.join("','") + "')";
    QString queryStr = "SELECT id_materiel, nom, type, etat, localisation FROM materiel WHERE id_materiel IN " + condition;

    QSqlQuery query(db);
    if (!query.exec(queryStr)) {
        QMessageBox::warning(this, "Erreur", "Échec de lecture dans la base : " + query.lastError().text());
        return;
    }

    // 🔹 Étape 3 : Ajouter les résultats dans le PDF
    while (query.next()) {
        html += "<tr>";
        html += "<td>" + query.value(0).toString() + "</td>";
        html += "<td>" + query.value(1).toString() + "</td>";
        html += "<td>" + query.value(2).toString() + "</td>";
        html += "<td>" + query.value(3).toString() + "</td>";
        html += "<td>" + query.value(4).toString() + "</td>";
        html += "</tr>";
    }

    html += "</table></body></html>";

    // 🔹 Étape 4 : Génération du PDF
    QTextDocument doc;
    doc.setHtml(html);

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    doc.print(&printer);

    QMessageBox::information(this, "Exportation réussie ✅",
                             "Seuls les matériels encore présents dans la base et dans la table ont été exportés :\n" + filePath);
}






