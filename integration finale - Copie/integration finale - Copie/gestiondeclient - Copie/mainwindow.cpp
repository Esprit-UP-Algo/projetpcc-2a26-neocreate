#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "staff.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QTableWidgetItem>
#include <QRegularExpression>
#include <QPushButton>

#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Boutons menu (doivent exister dans mainwindow.ui)
    connect(ui->btn_staff,    &QPushButton::clicked, this, &MainWindow::showStaff);
    connect(ui->btn_client,   &QPushButton::clicked, this, &MainWindow::showClient);
    connect(ui->btn_materiel, &QPushButton::clicked, this, &MainWindow::showMateriel);
    connect(ui->btn_projet,   &QPushButton::clicked, this, &MainWindow::showProjet);
    connect(ui->btn_sponsor,  &QPushButton::clicked, this, &MainWindow::showSponsor);
    connect(ui->btn_createur, &QPushButton::clicked, this, &MainWindow::showCreateur);
    // Page d’accueil au démarrage (adapte l’index si besoin)
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->tabl, &QTableWidget::itemChanged, this, &MainWindow::onTableItemChanged);
    // Initialisation du comboBoxP pour le poste
    ui->comboBoxP->clear();
    ui->comboBoxP->insertItem(0, "");           // option vide par défaut
    ui->comboBoxP->addItem("Materiel");
    ui->comboBoxP->addItem("Sponsor");
    ui->comboBoxP->addItem("Createur");
    ui->comboBoxP->setCurrentIndex(0);
    ui->tabl->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked | QAbstractItemView::EditKeyPressed);


    // Chargement initial des données du staff
    afficherStaff();

    // Connexions des boutons

    connect(ui->toolButtonSupp, &QToolButton::clicked, this, &MainWindow::supprimerStaff);

    // 🔹 Quand tu cliques sur "Modifier", tu entres en mode modification (édition possible)
    connect(ui->toolButtonMod, &QToolButton::clicked, this, &MainWindow::activerModeModification);

    // 🔹 Ces deux lignes existent déjà et sont correctes :
    connect(ui->tabl, &QTableWidget::cellChanged, this, &MainWindow::miseAJourCellule);

    connect(ui->tabl, &QTableWidget::cellClicked, this, &MainWindow::remplirChampsDepuisTableau);
    connect(ui->toolButtonAff, &QToolButton::clicked, this, &MainWindow::afficherParID);

}

MainWindow::~MainWindow()
{
    delete ui;

}
// Adapte les indices selon l’ordre réel des pages dans stackedWidget
void MainWindow::showStaff()    { ui->stackedWidget->setCurrentIndex(0); }
void MainWindow::showClient()   { ui->stackedWidget->setCurrentIndex(1); }
void MainWindow::showMateriel() { ui->stackedWidget->setCurrentIndex(2); }
void MainWindow::showProjet()   { ui->stackedWidget->setCurrentIndex(3); }
void MainWindow::showSponsor()  { ui->stackedWidget->setCurrentIndex(4); }
void MainWindow::showCreateur() { ui->stackedWidget->setCurrentIndex(5); }
void MainWindow::onTableItemChanged(QTableWidgetItem *item) {
    // Exemple : afficher la nouvelle valeur
    if (item) {
        qDebug() << "Nouvelle valeur : " << item->text();
    }
}

// 🧩 Fonction pour afficher les employés
void MainWindow::afficherStaff()
{
    QSqlQuery query("SELECT * FROM Employe ORDER BY id_employe");

    ui->tabl->setRowCount(0);
    ui->tabl->setColumnCount(7);
    QStringList labels = {"ID", "Nom", "Prénom", "Poste","Compétence", "Téléphone", "Email"};
    ui->tabl->setHorizontalHeaderLabels(labels);

    int row = 0;
    while (query.next()) {
        ui->tabl->insertRow(row);
        ui->tabl->setItem(row, 0, new QTableWidgetItem(query.value("id_employe").toString()));
        ui->tabl->setItem(row, 1, new QTableWidgetItem(query.value("nom").toString()));
        ui->tabl->setItem(row, 2, new QTableWidgetItem(query.value("prenom").toString()));
        ui->tabl->setItem(row, 3, new QTableWidgetItem(query.value("poste").toString()));
        ui->tabl->setItem(row, 4, new QTableWidgetItem(query.value("competence").toString()));
        ui->tabl->setItem(row, 5, new QTableWidgetItem(query.value("telephone").toString()));
        ui->tabl->setItem(row, 6, new QTableWidgetItem(query.value("email").toString()));

        row++;
    }
}
void MainWindow::on_btnQuitter_clicked()
{
    close(); // ferme la fenêtre principale
}

void MainWindow::on_btnStaff_clicked()
{
    // Si tu veux ouvrir la page du staff (par exemple afficher un onglet)
    // Tu peux afficher le widget du staff ici
    ui->stackedWidget->setCurrentIndex(1); // si tu utilises un QStackedWidget
    // ou simplement afficher un message
    // QMessageBox::information(this, "Info", "Page Staff ouverte !");
}

void MainWindow::on_btnConnecter_clicked()
{
    // Exemple simple : vérifier la connexion à la base
    QMessageBox::information(this, "Connexion", "Connexion réussie !");
}

// ➕ Ajouter un employé
void MainWindow::on_toolButtonAjouter_clicked()
{
    QString id = ui->lineEditid->text().trimmed();
    // Vérifier que l'ID n'est pas vide
    if (id.isEmpty()) {
        QMessageBox::warning(this, "Erreur ID", "L'ID ne peut pas être vide !");
        return;
    }

    // Vérifier que l'ID contient exactement 8 chiffres
    QRegularExpression reg("^\\d{8}$"); // exactement 8 chiffres
    if (!reg.match(id).hasMatch()) {
        QMessageBox::warning(this, "Erreur ID", "L'ID doit contenir exactement 8 chiffres !");
        return;
    }

    QString nom = ui->lineEditNom->text().trimmed();
    QString prenom = ui->lineEditPrenom->text().trimmed();

    if (!verifierNomOuPrenom(nom)) {
        QMessageBox::warning(this, "Erreur Nom", "Le nom doit commencer par une majuscule et ne contenir que des lettres !");
        return;
    }

    if (!verifierNomOuPrenom(prenom)) {
        QMessageBox::warning(this, "Erreur Prénom", "Le prénom doit commencer par une majuscule et ne contenir que des lettres !");
        return;
    }
    // Vérifier si l'ID existe déjà
    if (idExisteDeja(id)) {
        QMessageBox::warning(this, "Erreur ID", "Cet ID existe déjà dans la base !");
        return;
    }


    QString poste = ui->comboBoxP->currentText().trimmed();
    if (poste.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un poste !");
        return;
    }


    QString competence;
    if (ui->radioButton1->isChecked())
        competence = "Débutant";
    else if (ui->radioButton2->isChecked())
        competence = "Intermédiaire";
    else if (ui->radioButton3->isChecked())
        competence = "Avancé";
    else{
            QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une compétence !");
            return;
        }
    // Vérifier le téléphone
    QString telephone = ui->lineEditTel->text().trimmed();
    QRegularExpression regTel("^\\d{8}$"); // exactement 8 chiffres
    if (!regTel.match(telephone).hasMatch()) {
        QMessageBox::warning(this, "Erreur Téléphone", "Le numéro de téléphone doit contenir exactement 8 chiffres !");
        return;
    }

    // Vérifier l'email
    QString email = ui->lineEditMail->text().trimmed();
    QRegularExpression regEmail("^[A-Z][A-Za-z0-9._%+-]*@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    if (!regEmail.match(email).hasMatch()) {
        QMessageBox::warning(this, "Erreur Email", "L'email doit commencer par une majuscule et contenir un '@'.");
        return;
    }


    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE (ID_EMPLOYE, NOM, PRENOM, POSTE, COMPETENCE, TELEPHONE, EMAIL) "
                  "VALUES (:id, :nom, :prenom, :poste, :competence, :telephone, :email)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":competence", competence);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Ajout effectué avec succès ✅");

        // ➕ Ajout direct dans le tableau sans supprimer les anciennes lignes
        int row = ui->tabl->rowCount();
        ui->tabl->insertRow(row);
        ui->tabl->setItem(row, 0, new QTableWidgetItem(id));
        ui->tabl->setItem(row, 1, new QTableWidgetItem(nom));
        ui->tabl->setItem(row, 2, new QTableWidgetItem(prenom));
        ui->tabl->setItem(row, 3, new QTableWidgetItem(poste));
        ui->tabl->setItem(row, 4, new QTableWidgetItem(competence));
        ui->tabl->setItem(row, 5, new QTableWidgetItem(telephone));
        ui->tabl->setItem(row, 6, new QTableWidgetItem(email));
    } else {
        QMessageBox::warning(this, "Erreur", "Échec de l’ajout. Vérifie les données.");
        qDebug() << "Erreur SQL :" << query.lastError().text();
    }
}



// ❌ Supprimer un employé
void MainWindow::supprimerStaff()
{
    int row = ui->tabl->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Attention", "Sélectionnez une ligne à supprimer.");
        return;
    }

    QTableWidgetItem *idItem = ui->tabl->item(row, 0);
    if (!idItem) {
        QMessageBox::warning(this, "Erreur", "Impossible de lire l'ID de la ligne sélectionnée.");
        return;
    }

    QString id = idItem->text();
    if (id.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "ID vide pour la ligne sélectionnée.");
        return;
    }

    // confirmation
    if (QMessageBox::question(this, "Confirmer suppression",
                              "Voulez-vous vraiment supprimer l'employé ID = " + id + " ?",
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    // Utiliser transaction pour sécurité
    QSqlDatabase db = QSqlDatabase::database();
    bool started = db.transaction();

    QSqlQuery query;
    // <-- ADAPTE ICI le nom exact de la colonne ID dans ta table Oracle
    // Exemples possibles : ID_EMPLOYE, ID_EMPLOYE (majuscule), id_employe
    QString idCol = "ID_EMPLOYE"; // <<== mets le nom exact de ta colonne
    QString sql = QString("DELETE FROM EMPLOYE WHERE ID_EMPLOYE = :id").arg(idCol);
    query.prepare(sql);
    query.bindValue(":id", id);

    if (!query.exec()) {
        // rollback si on avait commencé la transaction
        if (started) db.rollback();

        QString err = query.lastError().text();
        qDebug() << "Erreur DELETE:" << err;
        // Affiche erreur une seule fois
        QMessageBox::critical(this, "Erreur SQL", "Suppression échouée :\n" + err);
        return;
    }

    // commit
    if (started) db.commit();

    // Rafraîchir le tableau sans déclencher cellChanged
    m_ignoreCellChanged = true;
    afficherStaff();   // ta fonction d'affichage
    m_ignoreCellChanged = false;

    QMessageBox::information(this, "Succès", "Employé supprimé (ID=" + id + ").");
}


// ✏️ Modifier un employé
void MainWindow::activerModeModification()
{
    // ✅ Autorise la modification directe dans ton QTableWidget
    ui->tabl->setEditTriggers(QAbstractItemView::DoubleClicked |
                              QAbstractItemView::SelectedClicked |
                              QAbstractItemView::EditKeyPressed);

    QMessageBox::information(this, "Mode modification",
                             "Tu peux maintenant modifier une cellule.\n"
                             "Appuie sur Entrée pour enregistrer dans la base.");
}


void MainWindow::modifierStaff()
{
    activerModeModification();
}


// ==========================
// Quand une cellule change → mise à jour SQL
// ==========================
// 🔄 MISE À JOUR AUTOMATIQUE (silencieuse)
// ============================
void MainWindow::miseAJourCellule(int row, int column)
{
    QString id = ui->tabl->item(row, 0)->text();
    QString nouvelleValeur = ui->tabl->item(row, column)->text();

    QString champ;
    switch (column) {
    case 1: champ = "NOM"; break;
    case 2: champ = "PRENOM"; break;
    case 3: champ = "POSTE"; break;
    case 4: champ = "COMPETENCE"; break;
    case 5: champ = "TELEPHONE"; break;
    case 6: champ = "EMAIL"; break;
    default: return;
    }

    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET " + champ + " = :val WHERE ID_EMPLOYE = :id");
    query.bindValue(":val", nouvelleValeur);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur mise à jour:" << query.lastError().text();
    }
}
void MainWindow::rechercherStaff()
{
    QString id = ui->lineEditD->text().trimmed();

    if (id.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez entrer un ID à rechercher.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT id_employe, nom, prenom, poste, competence, telephone, email "
                  "FROM employe WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL", "Échec de la recherche : " + query.lastError().text());
        return;
    }

    // Efface le tableau avant d’afficher le résultat
    ui->tabl->setRowCount(0);

    int row = 0;
    while (query.next()) {
        ui->tabl->insertRow(row);
        ui->tabl->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->tabl->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->tabl->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->tabl->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        ui->tabl->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
        ui->tabl->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
        ui->tabl->setItem(row, 6, new QTableWidgetItem(query.value(6).toString()));
        row++;
    }

    if (row == 0)
        QMessageBox::information(this, "Résultat", "Aucun employé trouvé avec cet ID.");
}
void MainWindow::afficherParID()
{
    QString idText = ui->lineEditD->text().trimmed();


    QRegularExpression reg("^\\d{8}$"); // exactement 8 chiffres
    if (!reg.match(idText).hasMatch()) {
        QMessageBox::warning(this, "Erreur ID", "L'ID doit contenir exactement 8 chiffres !");
        return;
    }



    int id = idText.toInt();  // conversion en entier

    QSqlQuery query;
    query.prepare("SELECT ID_EMPLOYE, NOM, PRENOM, POSTE, COMPETENCE, TELEPHONE, EMAIL "
                  "FROM employe WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL", "Échec de la recherche : " + query.lastError().text());
        return;
    }

    // Configurer le tableau pour 7 colonnes avec les bons titres
    ui->tabl->setColumnCount(7);
    ui->tabl->setHorizontalHeaderLabels({"ID", "Nom", "Prenom", "Poste", "Competence", "Telephone", "Email"});
    ui->tabl->setRowCount(0);

    int row = 0;
    while (query.next()) {
        ui->tabl->insertRow(row);
        ui->tabl->setItem(row, 0, new QTableWidgetItem(query.value("ID_EMPLOYE").toString()));
        ui->tabl->setItem(row, 1, new QTableWidgetItem(query.value("NOM").toString()));
        ui->tabl->setItem(row, 2, new QTableWidgetItem(query.value("PRENOM").toString()));
        ui->tabl->setItem(row, 3, new QTableWidgetItem(query.value("POSTE").toString()));
        ui->tabl->setItem(row, 4, new QTableWidgetItem(query.value("COMPETENCE").toString()));
        ui->tabl->setItem(row, 5, new QTableWidgetItem(query.value("TELEPHONE").toString()));
        ui->tabl->setItem(row, 6, new QTableWidgetItem(query.value("EMAIL").toString()));
        row++;
    }

    if (row == 0) {
        QMessageBox::information(this, "Résultat", "Aucun employé trouvé avec cet ID.");
    }
}
QString MainWindow::genererIDNumerique()
{
    QString id;
    do {
        id.clear();
        for (int i = 0; i < 8; ++i) {
            int digit = QRandomGenerator::global()->bounded(10);
            id += QString::number(digit);
        }
    } while (idExisteDeja(id));
    return id;
}

// Vérifie que le texte contient uniquement des lettres et commence par une majuscule
bool MainWindow::verifierNomOuPrenom(const QString &texte)
{
    QRegularExpression regex("^[A-Z][a-zA-Z]*$");
    return regex.match(texte).hasMatch();

}

// Vérifie si l'ID existe déjà dans la base
bool MainWindow::idExisteDeja(const QString &id)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM employe WHERE ID_EMPLOYE = :id");
    query.bindValue(":id", id);
    if (query.exec() && query.next())
        return query.value(0).toInt() > 0;
    return false;
}



// 🧾 Remplir les champs quand on clique sur un employé dans le tableau
void MainWindow::remplirChampsDepuisTableau(int row, int)
{
    ui->lineEditid->setText(ui->tabl->item(row, 0)->text());
    ui->lineEditNom->setText(ui->tabl->item(row, 1)->text());
    ui->lineEditPrenom->setText(ui->tabl->item(row, 2)->text());
    ui->comboBoxP->setCurrentText(ui->tabl->item(row, 3)->text());
    QString comp = ui->tabl->item(row, 4)->text();
    ui->radioButton1->setChecked(comp == ui->radioButton1->text());
    ui->radioButton2->setChecked(comp == ui->radioButton2->text());
    ui->radioButton3->setChecked(comp == ui->radioButton3->text());
    ui->lineEditTel->setText(ui->tabl->item(row, 5)->text());
    ui->lineEditMail->setText(ui->tabl->item(row, 6)->text());
}
