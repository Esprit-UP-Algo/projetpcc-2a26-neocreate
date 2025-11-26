#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "staff.h"
#include <QToolButton>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "materiel.h"
#include <QPushButton>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QtPrintSupport/QPrinter>
#include <QPrintDialog>
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
#include <QSqlQueryModel>
#include <QScopedPointer>
#include <QApplication>
#include "sponsor.h"
#include "gestioncreateur.h"
#include <QToolBar>
#include <QToolButton>
#include <QLabel>
#include <QTimer>
#include "chatwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , staff(nullptr)
    , sponsorManager(nullptr)
    , currentSponsorId("")  // Initialiser ici
{
    ui->setupUi(this);
    this->showFullScreen();
    this->showMaximized();

    qDebug() << "=== DÉBUT INITIALISATION ===";
    // Dans ton MainWindow ou Dialog principal

    // ========== INITIALISATION STAFF ==========
    staff = new Staff();
    staff->initS(ui->lineEditid, ui->lineEditNom, ui->lineEditPrenom,
                 ui->comboBoxP, ui->lineEditTel, ui->lineEditMail,
                 ui->lineEditMot, ui->radioButton1, ui->radioButton2, ui->radioButton3);

    staff->initTab(ui->tabl);

    qDebug() << "=== INITIALISATION RECHERCHE ===";
    qDebug() << "lineEditD pointer:" << ui->lineEditD;
    qDebug() << "toolButtonR pointer:" << ui->toolButtonR;
    staff->initRechercheID(ui->lineEditD, ui->toolButtonR);
    qDebug() << "=== INITIALISATION TERMINÉE ===";

    staff->initTrier(ui->comboBox);
    staff->refTab();
    staff->initAfficherTout(ui->toolButtonAff);
    qDebug() << "Bouton afficher tout initialisé";

    // ========== INITIALISATION SPONSOR MANAGER ==========
    sponsorManager = new SponsorManager(this);  // UNE SEULE fois

    // ========== CONNECTIONS STAFF ==========
    connect(ui->toolButtonAjouter, &QToolButton::clicked, staff, &Staff::ConfS);
    connect(ui->toolButtonMod, &QToolButton::clicked, staff, &Staff::modifS);
    connect(ui->toolButtonSupp, &QToolButton::clicked, staff, &Staff::suppS);
    connect(ui->toolButtonAnnuler, &QToolButton::clicked, staff, &Staff::reinitS);
    connect(ui->toolButton_24, &QToolButton::clicked, staff, &Staff::expoS);

    // ========== CONNECTIONS NAVIGATION ==========
    connect(ui->btn_staff,    &QToolButton::clicked, this, &MainWindow::showStaff);
    connect(ui->btn_client,   &QToolButton::clicked, this, &MainWindow::showClient);
    connect(ui->btn_materiel, &QToolButton::clicked, this, &MainWindow::showMateriel);
    connect(ui->btn_projet,   &QToolButton::clicked, this, &MainWindow::showProjet);
    connect(ui->btn_sponsor,  &QToolButton::clicked, this, &MainWindow::showSponsor);
    connect(ui->btn_createur, &QToolButton::clicked, this, &MainWindow::showCreateur);
    // SUPPRIMER la connexion dupliquée pour btn_createur

    // ========== CONNECTIONS SPONSOR ==========
    connect(ui->AjouterSponsor, &QPushButton::clicked, this, &MainWindow::on_AjouterSponsor_clicked);
    connect(ui->exportationpdf, &QPushButton::clicked, this, [this]() {
        SponsorManager::executerExportPDF(ui->tableWidget_2, this);
    });
    connect(ui->btn_actualiser, &QPushButton::clicked, this, [this]() {
        SponsorManager::afficherDashboardKPI(ui->groupBox_8);
    });

    // ========== CONFIGURATION TABLEAU SPONSOR ==========
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->tableWidget_2, &QTableWidget::cellClicked, this, &MainWindow::on_tableWidget_2_cellClicked);

    // Configuration combobox contribution
    ui->combobox_contribution->addItems({"Services", "Matériels", "Autre"});

    // ========== SYSTÈME DE NOTIFICATION ==========
    QToolButton *btnNotification = new QToolButton(this);
    btnNotification->setText("🔔 Notifications");
    btnNotification->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    btnNotification->setStyleSheet(
        "QToolButton { "
        "font-size: 14px; background: #3498db; color: white; border: none; "
        "padding: 8px 15px; border-radius: 6px; margin: 5px; "
        "font-weight: bold; "
        "}"
        "QToolButton:hover { background: #2980b9; }"
        "QToolButton:pressed { background: #21618c; }"
        );

    // Badge de notification
    QLabel *badge = new QLabel("0", btnNotification);
    badge->setStyleSheet(
        "QLabel { "
        "background: #e74c3c; color: white; font-size: 10px; font-weight: bold; "
        "border-radius: 8px; padding: 2px 6px; min-width: 18px; min-height: 18px; "
        "border: 2px solid white; "
        "}"
        );
    badge->setAlignment(Qt::AlignCenter);
    badge->move(btnNotification->width() - 25, 5); // Position dans le bouton
    badge->setVisible(false);

    connect(btnNotification, &QToolButton::clicked, this, [this]() {
        SponsorManager::afficherFenetreNotifications(this);
    });

    // Barre d'outils notification en HAUT À DROITE
    QToolBar *notificationBar = new QToolBar("Notifications", this);
    notificationBar->setMovable(false);
    notificationBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    addToolBar(Qt::TopToolBarArea, notificationBar);

    // ⭐⭐ UN SEUL SPACER ⭐⭐
    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    notificationBar->addWidget(spacer);

    notificationBar->addWidget(btnNotification);

    // Timer pour rafraîchissement notifications
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [badge, btnNotification]() {
        int count = SponsorManager::getNombreNotifications();
        badge->setText(QString::number(count));
        badge->setVisible(count > 0);

        // Recalculer la position du badge si la taille du bouton change
        badge->move(btnNotification->width() - 25, 5);
    });
    timer->start(60000); // 1 minute

    // Premier rafraîchissement
    int count = SponsorManager::getNombreNotifications();
    badge->setText(QString::number(count));
    badge->setVisible(count > 0);
    // ========== INITIALISATION FINALE ==========
    // ========== INITIALISATION FINALE ==========
    GestionCreateur *gestionCreateur = new GestionCreateur(ui, this);
    SponsorManager::afficherDashboardKPI(ui->groupBox_8);

    qDebug() << "=== INITIALISATION COMPLÈTE ===";

    // ========== NOTIFICATIONS AUTOMATIQUES ==========
    // Démarrer les notifications APRÈS que la fenêtre soit affichée
    QTimer::singleShot(3000, this, [this]() {
        if (sponsorManager) {
            // Notification de bienvenue
            sponsorManager->showNotification("Application lancée", "Bienvenue dans la gestion des sponsors !");

            // Démarrer les notifications toast automatiques
            sponsorManager->demarrerNotificationsAutomatiques(this);
        }
    });
}
// AJOUTER - Appelle materiel.ajouter()
            void MainWindow::on_ajouter_clicked()
{
    QString idstr = ui->id_materiel->text().trimmed();
    QString nom = ui->nom->text().trimmed();
    QString type = ui->comboBox_6->currentText().trimmed();
    QString etat = recupererEtat();
    QString localisation = recupererLocalisation();

    // Validation
    if (idstr.isEmpty() || nom.isEmpty() || type.isEmpty() || etat.isEmpty() || localisation.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Remplissez tous les champs !");
        return;
    }

    if (!Materiel::validerId(idstr)) {
        QMessageBox::warning(this, "Erreur", "ID doit avoir 8 chiffres !");
        return;
    }

    if (!Materiel::validerNom(nom)) {
        QMessageBox::warning(this, "Erreur", "Nom doit commencer par majuscule !");
        return;
    }

    if (Materiel::existeId(idstr)) {
        QMessageBox::warning(this, "Erreur", "ID existe déjà !");
        return;
    }

    // Appel à la classe Materiel
    Materiel m(idstr, nom, type, etat, localisation);
    if (m.ajouter()) {
        QMessageBox::information(this, "Succès", "Matériel ajouté !");
        viderChamps();
        Materiel::afficherTableau(ui->tableWidget_4);
    } else {
        QMessageBox::critical(this, "Erreur", "Échec d'ajout !");
    }
}

// MODIFIER - Appelle materiel.modifier()
void MainWindow::on_modifier_clicked()
{
    QString idstr = ui->id_materiel->text().trimmed();
    QString nom = ui->nom->text().trimmed();
    QString type = ui->comboBox_6->currentText().trimmed();
    QString etat = recupererEtat();
    QString localisation = recupererLocalisation();

    // Validation
    if (idstr.isEmpty() || nom.isEmpty() || type.isEmpty() || etat.isEmpty() || localisation.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Remplissez tous les champs !");
        return;
    }

    if (!Materiel::existeId(idstr)) {
        QMessageBox::warning(this, "Erreur", "Matériel non trouvé !");
        return;
    }

    // Appel à la classe Materiel
    Materiel m(idstr, nom, type, etat, localisation);
    if (m.modifier()) {
        QMessageBox::information(this, "Succès", "Matériel modifié !");
        viderChamps();
        Materiel::afficherTableau(ui->tableWidget_4);
    } else {
        QMessageBox::critical(this, "Erreur", "Échec modification !");
    }
}

// SUPPRIMER - Appelle materiel.supprimer()
void MainWindow::on_supprimer_clicked()
{
    QList<QTableWidgetItem *> selection = ui->tableWidget_4->selectedItems();
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Sélectionnez une ligne !");
        return;
    }

    int row = selection.first()->row();
    QString idstr = ui->tableWidget_4->item(row, 0)->text();

    // Appel à la classe Materiel
    Materiel m;
    m.setId(idstr);

    if (m.supprimer()) {
        QMessageBox::information(this, "Succès", "Matériel supprimé !");
        Materiel::afficherTableau(ui->tableWidget_4);
    } else {
        QMessageBox::critical(this, "Erreur", "Échec suppression !");
    }
}

// AFFICHER - Appelle materiel.afficherTableau()
void MainWindow::on_afficher_clicked()
{
    Materiel::afficherTableau(ui->tableWidget_4);
}

// CHERCHER - Appelle materiel.chercher()
void MainWindow::on_chercher_2_clicked()
{
    QString recherche = ui->chercher->text().trimmed();

    if (recherche.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Entrez un ID !");
        return;
    }

    QList<Materiel> resultats = Materiel::chercher(recherche);

    if (resultats.isEmpty()) {
        QMessageBox::information(this, "Résultat", "Aucun matériel trouvé !");
    } else {
        // Afficher le résultat
        ui->tableWidget_4->setRowCount(1);
        const Materiel &m = resultats.first();
        ui->tableWidget_4->setItem(0, 0, new QTableWidgetItem(m.getId()));
        ui->tableWidget_4->setItem(0, 1, new QTableWidgetItem(m.getNom()));
        ui->tableWidget_4->setItem(0, 2, new QTableWidgetItem(m.getType()));
        ui->tableWidget_4->setItem(0, 3, new QTableWidgetItem(m.getEtat()));
        ui->tableWidget_4->setItem(0, 4, new QTableWidgetItem(m.getLocalisation()));

        QMessageBox::information(this, "Résultat", "Matériel trouvé !");
    }
}

// TRIER - Appelle materiel.trier()
void MainWindow::on_comboBox_7_currentIndexChanged(int index)
{
    QString choix = ui->comboBox_7->currentText();

    if (choix == "Aucun") {
        Materiel::afficherTableau(ui->tableWidget_4);
        return;
    }

    QList<Materiel> resultats = Materiel::trier(choix);

    ui->tableWidget_4->setRowCount(0);
    for (const Materiel &m : resultats) {
        int row = ui->tableWidget_4->rowCount();
        ui->tableWidget_4->insertRow(row);
        ui->tableWidget_4->setItem(row, 0, new QTableWidgetItem(m.getId()));
        ui->tableWidget_4->setItem(row, 1, new QTableWidgetItem(m.getNom()));
        ui->tableWidget_4->setItem(row, 2, new QTableWidgetItem(m.getType()));
        ui->tableWidget_4->setItem(row, 3, new QTableWidgetItem(m.getEtat()));
        ui->tableWidget_4->setItem(row, 4, new QTableWidgetItem(m.getLocalisation()));
    }
}

void MainWindow::on_tableWidget_4_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();
    ui->id_materiel->setText(ui->tableWidget_4->item(row, 0)->text());
    ui->nom->setText(ui->tableWidget_4->item(row, 1)->text());

    QString type = ui->tableWidget_4->item(row, 2)->text();
    int index = ui->comboBox_6->findText(type);
    if (index != -1) ui->comboBox_6->setCurrentIndex(index);

    QString etat = ui->tableWidget_4->item(row, 3)->text();
    ui->fonctionnel->setChecked(etat == "Fonctionnel");
    ui->en_panne->setChecked(etat == "En panne");
    ui->en_maintenace->setChecked(etat == "En maintenance");
    ui->hors_service->setChecked(etat == "Hors service");

    QString localisation = ui->tableWidget_4->item(row, 4)->text();
    ui->studio_tournage->setChecked(localisation == "Studio tournage");
    ui->salle_montage->setChecked(localisation == "Salle montage");
    ui->salle_podcast->setChecked(localisation == "Salle podcast");
}

QString MainWindow::recupererEtat() const
{
    if (ui->en_panne->isChecked()) return "En panne";
    if (ui->fonctionnel->isChecked()) return "Fonctionnel";
    if (ui->en_maintenace->isChecked()) return "En maintenance";
    if (ui->hors_service->isChecked()) return "Hors service";
    return "";
}

QString MainWindow::recupererLocalisation() const
{
    if (ui->studio_tournage->isChecked()) return "Studio tournage";
    if (ui->salle_montage->isChecked()) return "Salle montage";
    if (ui->salle_podcast->isChecked()) return "Salle podcast";
    return "";
}

void MainWindow::viderChamps()
{
    ui->id_materiel->clear();
    ui->nom->clear();
    ui->comboBox_6->setCurrentIndex(0);

    QList<QRadioButton*> etatButtons = {ui->fonctionnel, ui->en_panne, ui->en_maintenace, ui->hors_service};
    for (auto* btn : etatButtons) {
        btn->setAutoExclusive(false);
        btn->setChecked(false);
        btn->setAutoExclusive(true);
    }

    ui->studio_tournage->setChecked(false);
    ui->salle_montage->setChecked(false);
    ui->salle_podcast->setChecked(false);

    ui->id_materiel->setFocus();
}

void MainWindow::on_annuler_clicked()
{
    viderChamps();
}

void MainWindow::on_exporter_clicked()
{
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

    html += "<h2> Liste du matériel exportée</h2>";
    html += "<p>Date d'exportation : " + QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss") + "</p>";
    html += "<table><tr><th>ID</th><th>Nom</th><th>Type</th><th>État</th><th>Localisation</th></tr>";

    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");
    if (!db.isOpen())
        db.open();

    if (!db.isOpen()) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir la base : " + db.lastError().text());
        return;
    }

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

    QString condition = "('" + idsTable.join("','") + "')";
    QString queryStr = "SELECT id_materiel, nom, type, etat, localisation FROM materiel WHERE id_materiel IN " + condition;

    QSqlQuery query(db);
    if (!query.exec(queryStr)) {
        QMessageBox::warning(this, "Erreur", "Échec de lecture dans la base : " + query.lastError().text());
        return;
    }

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

    QMessageBox::information(this, "Exportation réussie ",
                             "Seuls les matériels encore présents dans la base et dans la table ont été exportés :\n" + filePath);
}
//client;
void MainWindow::setupTabClient()
{
    ui->tableWidget_8->setColumnCount(7);
    QStringList headers{ "", "ID_CLIENT", "NOM", "PRENOM", "ENTREPRISE", "EMAIL", "TYPE" };
    ui->tableWidget_8->setHorizontalHeaderLabels(headers);

    ui->tableWidget_8->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_8->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_8->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_8->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_8->setColumnWidth(0, 56);

    connect(ui->tableWidget_8, &QTableWidget::cellClicked, this, [this](int row, int col){
        if (row < 0 || col == 0) return;
        populateClientFormFromRow(row);
        setClientFormMode(true);
    });
}

void MainWindow::refreshClientsGrid()
{
    ui->tableWidget_8->setRowCount(0);
    const auto rows = ClientDAO::fetchAll();
    for (int i = 0; i < rows.size(); ++i) {
        const auto &c = rows[i];
        ui->tableWidget_8->insertRow(i);
        ui->tableWidget_8->setItem(i,1, new QTableWidgetItem(QString::number(c.ID_CLIENT)));
        ui->tableWidget_8->setItem(i,2, new QTableWidgetItem(c.NOM));
        ui->tableWidget_8->setItem(i,3, new QTableWidgetItem(c.PRENOM));
        ui->tableWidget_8->setItem(i,4, new QTableWidgetItem(c.ENTREPRISE));
        ui->tableWidget_8->setItem(i,5, new QTableWidgetItem(c.EMAIL));
        ui->tableWidget_8->setItem(i,6, new QTableWidgetItem(c.TYPE));
        addClientEditPenForRow(i);
    }
}

Client MainWindow::readClientForm() const
{
    Client c;
    c.ID_CLIENT  = ui->ID_CLIENT->text().trimmed().toInt();
    c.NOM        = ui->NOM->text().trimmed();
    c.PRENOM     = ui->PRENOM->text().trimmed();
    c.ENTREPRISE = ui->ENTR->text().trimmed();

    // Gérer les radio buttons pour TYPE
    if (ui->entr->isChecked()) {
        c.TYPE = "entreprise";
    } else if (ui->inst->isChecked()) {
        c.TYPE = "instagrameur";
    } else if (ui->aut->isChecked()) {
        c.TYPE = "Autre";
    } else {
        c.TYPE = "";  // Aucun sélectionné
    }

    return c;
}

void MainWindow::setClientFormMode(bool edit)
{
    if (edit) {
        ui->ID_CLIENT->setEnabled(false);
    } else {
        ui->ID_CLIENT->setEnabled(true);
        ui->ID_CLIENT->clear();
        ui->NOM->clear();
        ui->PRENOM->clear();
        ui->ENTR->clear();
        // Réinitialiser les radio buttons
        ui->entr->setChecked(false);
        ui->inst->setChecked(false);
        ui->aut->setChecked(false);
    }
}

void MainWindow::populateClientFormFromRow(int row)
{
    if (row < 0) return;
    ui->ID_CLIENT->setText(ui->tableWidget_8->item(row,1)->text());
    ui->NOM->setText(ui->tableWidget_8->item(row,2)->text());
    ui->PRENOM->setText(ui->tableWidget_8->item(row,3)->text());
    ui->ENTR->setText(ui->tableWidget_8->item(row,4)->text());

    // Gérer les radio buttons pour TYPE
    QString type = ui->tableWidget_8->item(row,6)->text().toLower();
    ui->entr->setChecked(false);
    ui->inst->setChecked(false);
    ui->aut->setChecked(false);

    if (type.contains("entreprise") || type == "entreprise") {
        ui->entr->setChecked(true);
    } else if (type.contains("instagram") || type == "instagrameur") {
        ui->inst->setChecked(true);
    } else if (!type.isEmpty()) {
        ui->aut->setChecked(true);
    }
}

void MainWindow::addClientEditPenForRow(int row)
{
    auto *editBtn = new QPushButton;
    editBtn->setToolTip("Edit");
    editBtn->setFlat(true);
    editBtn->setCursor(Qt::PointingHandCursor);
    const char* kPen = ":/image/ressource/edit.png";
    if (QFile::exists(kPen)) editBtn->setIcon(QIcon(kPen));
    else editBtn->setText("✎");
    editBtn->setIconSize(QSize(18,18));
    editBtn->setStyleSheet("QPushButton{border:none;}");
    editBtn->setFixedSize(26,26);

    connect(editBtn, &QPushButton::clicked, this, [this, editBtn](){
        QWidget* cell = editBtn->parentWidget();
        QPoint p = cell->mapTo(ui->tableWidget_8->viewport(), QPoint(2,2));
        int row = ui->tableWidget_8->indexAt(p).row();
        if (row < 0) return;
        populateClientFormFromRow(row);
        setClientFormMode(true);
    });

    auto *cell = new QWidget;
    auto *lay  = new QHBoxLayout(cell);
    lay->setContentsMargins(2,0,2,0);
    lay->setAlignment(Qt::AlignCenter);
    lay->addWidget(editBtn);
    ui->tableWidget_8->setCellWidget(row, 0, cell);
}

// ===============================
//  CONFIRM : ADD / UPDATE
// ===============================
void MainWindow::on_id_confirm_clicked()
{
    // Contrôles de saisie AVANT conversion/SQL
    const QString idT  = ui->ID_CLIENT->text().trimmed();
    const QString nomT = ui->NOM->text().trimmed();
    const QString preT = ui->PRENOM->text().trimmed();
    const QString entT = ui->ENTR->text().trimmed();

    // Vérifier qu'un type est sélectionné
    bool typeSelected = ui->entr->isChecked() || ui->inst->isChecked() || ui->aut->isChecked();

    static const QRegularExpression reInt(R"(^\d+$)");
    if (idT.isEmpty() || nomT.isEmpty() || preT.isEmpty() ||
        entT.isEmpty()  || !typeSelected) {
        QMessageBox::warning(this, "Validation", "Tous les champs sont obligatoires.");
        return;
    }
    if (!reInt.match(idT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "ID_CLIENT doit être un entier positif.");
        ui->ID_CLIENT->setFocus();
        return;
    }

    Client c = readClientForm();

    if (!m_clientEditMode) {
        if (ClientDAO::exists(c.ID_CLIENT)) {
            QMessageBox::warning(this, "Doublon", "ID_CLIENT existe déjà.");
            return;
        }
        if (!ClientDAO::create(c)) return;
        QMessageBox::information(this, "Succès", "Client ajouté.");
    } else {
        if (!ClientDAO::update(c)) return;
        QMessageBox::information(this, "Succès", "Client mis à jour.");
    }

    refreshClientsGrid();
    setClientFormMode(false);
}

// ===============================
//  DELETE via line_id
// ===============================
void MainWindow::on_id_delete_clicked()
{
    const QString t = ui->ID_CLIENT->text().trimmed();
    static const QRegularExpression reInt(R"(^\d+$)");
    if (!reInt.match(t).hasMatch()) {
        QMessageBox::warning(this, "Suppression", "Saisis un ID_CLIENT entier valide.");
        return;
    }
    const int id = t.toInt();

    if (QMessageBox::question(this, "Confirmer",
                              QString("Supprimer le client %1 ?").arg(id)) != QMessageBox::Yes) return;

    if (ClientDAO::remove(id)) {
        refreshClientsGrid();
        ui->ID_CLIENT->clear();
    }
}
//projet;
// ===================================================
    //                  PROJETS
    // ===================================================
    void MainWindow::setupTabProjet()
{
    ui->tableWidget_7->setColumnCount(6);
    QStringList headers{ "ID_PROJET", "TYPE", "DATE_D", "DATE_F", "PAIMENT", "ID_CLIENT" };
    ui->tableWidget_7->setHorizontalHeaderLabels(headers);

    ui->tableWidget_7->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_7->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_7->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_7->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::refreshProjetsGrid()
{
    ui->tableWidget_7->setRowCount(0);

    Projet projet;
    QSqlQueryModel* model = projet.AfficherProjets();

    if (!model) return;

    for (int i = 0; i < model->rowCount(); ++i) {
        ui->tableWidget_7->insertRow(i);
        ui->tableWidget_7->setItem(i, 0, new QTableWidgetItem(model->data(model->index(i, 0)).toString()));
        ui->tableWidget_7->setItem(i, 1, new QTableWidgetItem(model->data(model->index(i, 1)).toString()));
        ui->tableWidget_7->setItem(i, 2, new QTableWidgetItem(model->data(model->index(i, 2)).toString()));
        ui->tableWidget_7->setItem(i, 3, new QTableWidgetItem(model->data(model->index(i, 3)).toString()));
        ui->tableWidget_7->setItem(i, 4, new QTableWidgetItem(model->data(model->index(i, 4)).toString()));
        ui->tableWidget_7->setItem(i, 5, new QTableWidgetItem(model->data(model->index(i, 5)).toString()));
    }

    delete model;
}

Projet MainWindow::readProjetForm() const
{
    Projet p;
    p.setId(ui->lineEdit_31->text().trimmed().toInt());
    p.setType(ui->comboBox_13->currentText());
    p.setDateDebut(ui->dateEdit_7->date());
    p.setDateFin(ui->dateEdit_8->date());
    // Dans la base, PAIMENT est NUMBER(10,2), donc on utilise montant
    p.setMontant(ui->lineEdit_32->text().trimmed().toDouble());
    // comboBox_14 contient le type de paiement (cash/virement) - stocké dans paiment (QString)
    p.setPaiment(ui->comboBox_14->currentText());
    // ID_CLIENT: utiliser lineEdit_38 pour ID_CLIENT (saisie manuelle)
    // Si lineEdit_38 est vide ou invalide, on utilisera 0 (sera validé avant insertion)
    const QString idClientStr = ui->lineEdit_38->text().trimmed();
    if (!idClientStr.isEmpty()) {
        bool ok;
        int idClient = idClientStr.toInt(&ok);
        if (ok && idClient > 0) {
            p.setIdClient(idClient);
        } else {
            p.setIdClient(0); // Sera validé dans on_toolButton_52_clicked
        }
    } else {
        p.setIdClient(0); // Sera validé dans on_toolButton_52_clicked
    }

    return p;
}

void MainWindow::clearProjetForm()
{
    ui->lineEdit_31->clear();
    ui->comboBox_13->setCurrentIndex(0);
    ui->dateEdit_7->setDate(QDate::currentDate());
    ui->dateEdit_8->setDate(QDate::currentDate());
    ui->lineEdit_32->clear();
    ui->comboBox_14->setCurrentIndex(0);
    ui->lineEdit_38->clear(); // ID_CLIENT
}

void MainWindow::populateProjetFormFromRow(int row)
{
    if (row < 0 || row >= ui->tableWidget_7->rowCount()) return;

    // Colonnes: 0=ID_PROJET, 1=TYPE, 2=DATE_D, 3=DATE_F, 4=PAIMENT, 5=ID_CLIENT
    QTableWidgetItem* idItem = ui->tableWidget_7->item(row, 0);
    QTableWidgetItem* typeItem = ui->tableWidget_7->item(row, 1);
    QTableWidgetItem* dateDItem = ui->tableWidget_7->item(row, 2);
    QTableWidgetItem* dateFItem = ui->tableWidget_7->item(row, 3);
    QTableWidgetItem* montantItem = ui->tableWidget_7->item(row, 4);
    QTableWidgetItem* idClientItem = ui->tableWidget_7->item(row, 5);

    if (idItem) ui->lineEdit_31->setText(idItem->text());
    if (typeItem) {
        int index = ui->comboBox_13->findText(typeItem->text());
        if (index >= 0) ui->comboBox_13->setCurrentIndex(index);
    }
    if (dateDItem) {
        QDate dateD = QDate::fromString(dateDItem->text(), "yyyy-MM-dd");
        if (dateD.isValid()) ui->dateEdit_7->setDate(dateD);
    }
    if (dateFItem) {
        QDate dateF = QDate::fromString(dateFItem->text(), "yyyy-MM-dd");
        if (dateF.isValid()) ui->dateEdit_8->setDate(dateF);
    }
    if (montantItem) ui->lineEdit_32->setText(montantItem->text());
    if (idClientItem && !idClientItem->text().isEmpty() && idClientItem->text() != "NULL") {
        ui->lineEdit_38->setText(idClientItem->text());
    } else {
        ui->lineEdit_38->clear();
    }
}

void MainWindow::setProjetFormMode(bool edit)
{
    m_projetEditMode = edit;
    if (edit) {
        ui->toolButton_52->setText("Modifier");
        ui->lineEdit_31->setEnabled(false); // ID_PROJET ne peut pas être modifié
    } else {
        ui->toolButton_52->setText("Ajouter");
        ui->lineEdit_31->setEnabled(true);
        clearProjetForm();
    }
}

// ===============================
//  AJOUTER PROJET
// ===============================
void MainWindow::on_toolButton_52_clicked()
{
    const QString idT = ui->lineEdit_31->text().trimmed();
    const QString montantT = ui->lineEdit_32->text().trimmed();
    const QString idClientT = ui->lineEdit_38->text().trimmed();

    static const QRegularExpression reInt(R"(^\d+$)");
    static const QRegularExpression reDouble(R"(^\d+(\.\d+)?$)");

    // ID_CLIENT est optionnel (clé étrangère)
    if (idT.isEmpty() || montantT.isEmpty() || ui->comboBox_13->currentText().isEmpty()) {
        QMessageBox::warning(this, "Validation", "ID_PROJET, TYPE et Montant sont obligatoires.");
        return;
    }

    if (!reInt.match(idT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "ID_PROJET doit être un entier positif.");
        ui->lineEdit_31->setFocus();
        return;
    }

    // Valider ID_CLIENT seulement s'il est fourni
    if (!idClientT.isEmpty()) {
        if (!reInt.match(idClientT).hasMatch()) {
            QMessageBox::warning(this, "Validation", "ID_CLIENT doit être un entier positif.");
            ui->lineEdit_38->setFocus();
            return;
        }

        int idClient = idClientT.toInt();
        if (!ClientDAO::exists(idClient)) {
            QMessageBox::warning(this, "Validation", QString("ID_CLIENT %1 n'existe pas dans la table CLIENT.").arg(idClient));
            ui->lineEdit_38->setFocus();
            return;
        }
    }

    if (!reDouble.match(montantT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Montant doit être un nombre valide.");
        ui->lineEdit_32->setFocus();
        return;
    }

    if (ui->dateEdit_7->date() > ui->dateEdit_8->date()) {
        QMessageBox::warning(this, "Validation", "La date de début doit être antérieure ou égale à la date de fin.");
        return;
    }

    Projet p = readProjetForm();

    if (!m_projetEditMode) {
        // Mode Ajout
        if (p.AjouterProjet()) {
            QMessageBox::information(this, "Succès", "Projet ajouté avec succès.");
            clearProjetForm();
            refreshProjetsGrid();
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout du projet. Vérifiez les logs.");
        }
    } else {
        // Mode Modification
        if (p.ModifierProjet()) {
            QMessageBox::information(this, "Succès", "Projet modifié avec succès.");
            setProjetFormMode(false);
            refreshProjetsGrid();
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la modification du projet. Vérifiez les logs.");
        }
    }
}

// ===============================
//  AFFICHER PROJETS
// ===============================
void MainWindow::on_toolButton_56_clicked()
{
    refreshProjetsGrid();
}

// ===============================
//  SUPPRIMER PROJET
// ===============================
void MainWindow::on_toolButton_57_clicked()
{
    // Récupérer la ligne sélectionnée dans le tableau
    int currentRow = ui->tableWidget_7->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Suppression", "Sélectionne une ligne dans le tableau pour supprimer un projet.");
        return;
    }

    // Récupérer l'ID_PROJET depuis la colonne 0 de la ligne sélectionnée
    QTableWidgetItem* idItem = ui->tableWidget_7->item(currentRow, 0);
    if (!idItem) {
        QMessageBox::warning(this, "Suppression", "Impossible de récupérer l'ID_PROJET de la ligne sélectionnée.");
        return;
    }

    bool ok;
    const int id = idItem->text().toInt(&ok);

    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Suppression", "ID_PROJET invalide.");
        return;
    }

    if (QMessageBox::question(this, "Confirmer",
                              QString("Supprimer le projet %1 ?").arg(id),
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    Projet projet;
    if (projet.SupprimerProjet(id)) {
        QMessageBox::information(this, "Succès", QString("Projet %1 supprimé avec succès.").arg(id));
        refreshProjetsGrid();
    } else {
        QMessageBox::critical(this, "Erreur", QString("Erreur lors de la suppression du projet %1.\nLe projet n'existe peut-être pas.").arg(id));
    }
}

// ===============================
//  ÉDITER PROJET (remplit le formulaire)
// ===============================
void MainWindow::on_toolButton_58_clicked()
{
    // Récupérer la ligne sélectionnée dans le tableau
    int currentRow = ui->tableWidget_7->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Édition", "Sélectionne une ligne dans le tableau pour éditer un projet.");
        return;
    }

    // Remplir le formulaire avec les données de la ligne sélectionnée
    populateProjetFormFromRow(currentRow);
    setProjetFormMode(true);
}

// ===============================
//  ANNULER (réinitialise le formulaire)
// ===============================
//sponsor;
// ----------------- AJOUTER - COMME PROJET -----------------
void MainWindow::on_AjouterSponsor_clicked()
{
    // Récupérer les valeurs depuis l'UI
    QString id = ui->lineEdit_id->text().trimmed();
    QString nom = ui->lineEdit_nom->text().trimmed();
    QString contribution = ui->combobox_contribution->currentText().trimmed();
    QDate dateDebut = ui->date_debut->date();
    QDate dateFin = ui->date_fin->date();
    QString email = ui->lineEdit_email->text().trimmed();

    // Contrôles de saisie
    if (id.isEmpty() || nom.isEmpty() || contribution.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Tous les champs doivent être remplis.");
        return;
    }

    // ID: doit être 8 chiffres
    if (id.length() != 8 || !id.toInt()) {
        QMessageBox::warning(this, "Validation", "L'ID doit être exactement 8 chiffres.");
        return;
    }

    // Dates
    if (dateDebut >= dateFin) {
        QMessageBox::warning(this, "Validation", "La date de début doit être avant la date de fin.");
        return;
    }

    // Validation Email
    QRegularExpression reEmail("^[A-Za-z0-9]+@gmail\\.com$");
    if (!reEmail.match(email).hasMatch()) {
        QMessageBox::warning(this, "Validation Email",
                             "Email invalide !\n"
                             "Format accepté : uniquement lettres et chiffres@gmail.com\n"
                             "Exemples : john123@gmail.com, marie56@gmail.com");
        return;
    }

    // Construire l'objet et ajouter
    Sponsor s(id, nom, contribution, dateDebut, dateFin, email);
    bool ok = s.ajouter();

    if (ok) {
        QMessageBox::information(this, "Succès", "Sponsor ajouté en base.");
        on_AnnulerSponsor_clicked();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout en base.");
    }
}

// ----------------- MODIFIER - COMME PROJET -----------------
void MainWindow::on_ModifierSponsor_clicked()
{
    if (currentSponsorId.isEmpty()) {
        QMessageBox::warning(this, "Modification", "Sélectionnez d'abord un sponsor à modifier (cliquez sur une ligne du tableau).");
        return;
    }

    // Récupérer les valeurs depuis l'UI
    QString id = ui->lineEdit_id->text().trimmed();
    QString nom = ui->lineEdit_nom->text().trimmed();
    QString contribution = ui->combobox_contribution->currentText().trimmed();
    QDate dateDebut = ui->date_debut->date();
    QDate dateFin = ui->date_fin->date();
    QString email = ui->lineEdit_email->text().trimmed();

    // Contrôles de saisie
    if (id.isEmpty() || nom.isEmpty() || contribution.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Tous les champs doivent être remplis.");
        return;
    }

    // Dates
    if (dateDebut >= dateFin) {
        QMessageBox::warning(this, "Validation", "La date de début doit être avant la date de fin.");
        return;
    }

    // Validation Email
    QRegularExpression reEmail("^[A-Za-z0-9]+@gmail\\.com$");
    if (!reEmail.match(email).hasMatch()) {
        QMessageBox::warning(this, "Validation Email",
                             "Email invalide !\n"
                             "Format accepté : uniquement lettres et chiffres@gmail.com\n"
                             "Exemples : john123@gmail.com, marie56@gmail.com");
        return;
    }

    // Construire et modifier en base
    Sponsor s(id, nom, contribution, dateDebut, dateFin, email);
    s.setId(currentSponsorId); // Garder l'ID sélectionné comme clé

    qDebug() << "[MainWindow] Modification sponsor, ID=" << currentSponsorId;

    bool ok = s.modifier();
    if (!ok) {
        QMessageBox::critical(this, "Erreur", "Échec de la modification en base.");
        return;
    }

    QMessageBox::information(this, "Succès", "Sponsor modifié en base.");

    // Rafraîchir tableau
    on_AfficherSponsor_clicked();
}

// ----------------- SUPPRIMER - COMME PROJET -----------------
void MainWindow::on_SupprimerSponsor_clicked()
{
    if (currentSponsorId.isEmpty()) {
        QMessageBox::warning(this, "Suppression", "Sélectionnez d'abord un sponsor à supprimer (cliquez sur une ligne du tableau).");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(this, "Confirmation",
                                                              "Voulez-vous vraiment supprimer le sponsor ID: " + currentSponsorId + " ?",
                                                              QMessageBox::Yes|QMessageBox::No);

    if (reply != QMessageBox::Yes) return;

    // Suppression en base
    Sponsor s;
    bool removed = s.supprimer(currentSponsorId);

    if (removed) {
        QMessageBox::information(this, "Suppression", "Le sponsor a été supprimé en base.");

        // Rafraîchir depuis la base
        on_AfficherSponsor_clicked();

        // Clear form
        on_AnnulerSponsor_clicked();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression en base.");
    }
}

// ----------------- AFFICHER - COMME PROJET -----------------

void MainWindow::on_AfficherSponsor_clicked()
{
    // DEBUG
    if (ui->comboBox_tri) {
        qDebug() << "🔍 ComboBox tri - Texte actuel:" << ui->comboBox_tri->currentText();
    }

    // ACTION 1 : AFFICHER LE TABLEAU
    Sponsor::afficherDansTableau(ui->tableWidget_2);

    // ACTION 2 : APPLIQUER LE TRI - COMPARAISON SANS CASSE
    if (ui->comboBox_tri && ui->comboBox_tri->currentText().toLower() == "nom") {
        ui->tableWidget_2->setSortingEnabled(true);
        ui->tableWidget_2->sortByColumn(1, Qt::AscendingOrder);
        ui->tableWidget_2->setSortingEnabled(false);
        qDebug() << "✅ Tableau affiché ET trié par nom";
    } else {
        qDebug() << "❌ Tri NON appliqué";
    }
}

// ----------------- ANNULER - COMME PROJET -----------------
void MainWindow::on_AnnulerSponsor_clicked()
{
    ui->lineEdit_id->clear();
    ui->lineEdit_nom->clear();
    ui->combobox_contribution->setCurrentIndex(0);
    ui->date_debut->setDate(QDate::currentDate());
    ui->date_fin->setDate(QDate::currentDate());
    ui->lineEdit_email->clear();
    ui->lineEdit_chercher->clear();

    // Reset current ID
    currentSponsorId = "";

    // Réinitialiser les couleurs du tableau
    for (int row = 0; row < ui->tableWidget_2->rowCount(); ++row) {
        for (int col = 0; col < ui->tableWidget_2->columnCount(); ++col) {
            QTableWidgetItem* item = ui->tableWidget_2->item(row, col);
            if (item) {
                item->setBackground(QBrush()); // Couleur par défaut
            }
        }
    }
}

// ----------------- RECHERCHER - COMME PROJET -----------------
void MainWindow::on_RechercherSponsor_clicked()
{
    QString idRecherche = ui->lineEdit_chercher->text().trimmed();

    if (idRecherche.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Entrez un ID pour la recherche.");
        return;
    }

    // Variables pour stocker les résultats
    QString nom, contribution, email;
    QDate dateDebut, dateFin;

    // Recherche en base
    if (Sponsor::rechercherParId(idRecherche, nom, contribution, dateDebut, dateFin, email)) {
        // REMPLIR les champs
        ui->lineEdit_id->setText(idRecherche);
        ui->lineEdit_nom->setText(nom);

        // Trouver l'index de la contribution
        int index = ui->combobox_contribution->findText(contribution);
        if (index >= 0) {
            ui->combobox_contribution->setCurrentIndex(index);
        }

        ui->date_debut->setDate(dateDebut);
        ui->date_fin->setDate(dateFin);
        ui->lineEdit_email->setText(email);

        // Set current ID
        currentSponsorId = idRecherche;

        // Colorier la ligne en rose
        bool trouve = false;
        for (int row = 0; row < ui->tableWidget_2->rowCount(); ++row) {
            QTableWidgetItem* itemId = ui->tableWidget_2->item(row, 0);
            if (itemId && itemId->text() == idRecherche) {
                trouve = true;
                // Colorier toute la ligne en rose pastel
                for (int col = 0; col < ui->tableWidget_2->columnCount(); ++col) {
                    QTableWidgetItem* item = ui->tableWidget_2->item(row, col);
                    if (item) {
                        item->setBackground(QColor(255, 182, 193)); // Rose pastel
                    }
                }
                break;
            }
        }

        if (trouve) {
            QMessageBox::information(this, "Recherche", "Sponsor trouvé !\nLa ligne est surlignée en rose.");
        } else {
            QMessageBox::information(this, "Recherche", "Sponsor trouvé !\nCliquez sur 'Afficher' pour voir dans le tableau.");
        }
    } else {
        QMessageBox::information(this, "Recherche", "Aucun sponsor trouvé avec l'ID: " + idRecherche);
        on_AnnulerSponsor_clicked();
    }
}

// ----------------- CLIC TABLEAU - COMME PROJET -----------------
void MainWindow::on_tableWidget_2_cellClicked(int row, int column)
{
    // Lire directement depuis le tableau
    QTableWidgetItem *itemId = ui->tableWidget_2->item(row, 0);
    if (!itemId) return;

    QString id = itemId->text().trimmed();

    // Set currentSponsorId immédiatement
    currentSponsorId = id;

    // Remplir les champs du formulaire
    ui->lineEdit_id->setText(id);

    QTableWidgetItem *itemNom = ui->tableWidget_2->item(row, 1);
    if (itemNom) {
        ui->lineEdit_nom->setText(itemNom->text());
    }

    QTableWidgetItem *itemContribution = ui->tableWidget_2->item(row, 2);
    if (itemContribution) {
        QString contribution = itemContribution->text();
        int idx = ui->combobox_contribution->findText(contribution);
        if (idx >= 0) ui->combobox_contribution->setCurrentIndex(idx);
    }

    QTableWidgetItem *itemDateDebut = ui->tableWidget_2->item(row, 3);
    if (itemDateDebut) {
        QDate dateDebut = QDate::fromString(itemDateDebut->text(), "dd/MM/yyyy");
        if (dateDebut.isValid()) ui->date_debut->setDate(dateDebut);
    }

    QTableWidgetItem *itemDateFin = ui->tableWidget_2->item(row, 4);
    if (itemDateFin) {
        QDate dateFin = QDate::fromString(itemDateFin->text(), "dd/MM/yyyy");
        if (dateFin.isValid()) ui->date_fin->setDate(dateFin);
    }

    QTableWidgetItem *itemEmail = ui->tableWidget_2->item(row, 5);
    if (itemEmail) {
        ui->lineEdit_email->setText(itemEmail->text());
    }

    qDebug() << "[MainWindow] Row clicked, currentSponsorId set to:" << currentSponsorId;
}
void MainWindow::on_toolButton_53_clicked()
{
    setProjetFormMode(false);
}
void MainWindow::on_btnIA_clicked()
{
    ChatWindow *chat = new ChatWindow(this);
    chat->show();
}
void MainWindow::lancerNotificationDemarrage()
{
    if (sponsorManager) {
        sponsorManager->showNotification("Connexion réussie ✓",
                                         "Bienvenue dans la gestion des sponsors !");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showStaff()    { ui->stackedWidget->setCurrentIndex(0); }
void MainWindow::showClient()   { ui->stackedWidget->setCurrentIndex(1); }
void MainWindow::showMateriel() { ui->stackedWidget->setCurrentIndex(2); }
void MainWindow::showProjet()   { ui->stackedWidget->setCurrentIndex(3); }
void MainWindow::showSponsor()  { ui->stackedWidget->setCurrentIndex(4); }
void MainWindow::showCreateur() { ui->stackedWidget->setCurrentIndex(5); }
// ========== MÉTHODE EXPORT PDF ==========
