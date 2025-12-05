#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AppDesign.h"
#include <QDebug>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QIcon>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QTextTableFormat>
#include <QTextCharFormat>
#include <QTextBlockFormat>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>
#include <QDebug>
#include <QFile>
#include <QRegularExpression>
#include <QLineEdit>
#include <QToolButton>
#include <QRadioButton>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateEdit>
#include <QComboBox>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include "client.h"
#include "staff.h"
#include "materiel.h"
#include "sponsor.h"
#include "gestioncreateur.h"
#include "sponsormanager.h"
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <QDir>
#include <QScrollArea>
#include <QProgressBar>
#include <QFrame>
#include <QFileDialog>
#include <QDateTime>
#include <QTimer>
#include <QDir>
#include <QScrollArea>
#include <QProgressBar>
#include <QFrame>
#include <QPrintDialog>
#include <QScopedPointer>
#include <QtPrintSupport/QPrinter>
#include <QMap>
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLayoutItem>
#include <QFont>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QRandomGenerator>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <QDir>
#include <QScrollArea>
#include <QProgressBar>
#include <QFrame>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QMessageBox>
#include <QPrintDialog>
#include <QScopedPointer>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QPainter>
#include <QBrush>
#include <QColor>
#include <cmath>

// Qt Charts
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>

// =====================
//  CONSTRUCTEUR
// =====================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), sponsorManager(nullptr), currentSponsorId("")
{
    ui->setupUi(this);
    this->showMaximized();
    sponsorManager = new SponsorManager(this);
    GestionCreateur *gestionCreateur = new GestionCreateur(ui, this);

    ui->groupBox_2->setStyleSheet(AppDesign::navigationPanelStyle());


    // 2. Collecter les boutons de navigation
    QList<QToolButton*> navButtons;
    navButtons << ui->btn_staff
               << ui->btn_client
               << ui->btn_materiel
               << ui->btn_projet
               << ui->btn_sponsor
               << ui->btn_createur;

    // 3. Ajouter les émojis aux boutons
    AppDesign::addEmojiIcons(navButtons);


    // 3. Appliquer le style à TOUTES les pages


     // Table sponsor
    // ===== PARTIE 2 : LE RESTE DE TON CODE EXISTANT =====


    qDebug() << "🏁 Début initialisation MainWindow";

    // TES CONNEXIONS EXISTANTES RESTENT IDENTIQUES...
    connect(ui->btn_staff,    &QToolButton::clicked, this, &MainWindow::showStaff);
    connect(ui->btn_client,  &QToolButton::clicked, this, &MainWindow::showClient);
    connect(ui->btn_materiel, &QToolButton::clicked, this, &MainWindow::showMateriel);
    connect(ui->btn_projet,   &QToolButton::clicked, this, &MainWindow::showProjet);
    connect(ui->btn_sponsor,  &QToolButton::clicked, this, &MainWindow::showSponsor);
    connect(ui->btn_createur, &QToolButton::clicked, this, &MainWindow::showCreateur);
    connect(ui->toolButton_3, &QToolButton::clicked, this, &MainWindow::close);
    // Connexion pour le bouton quitter (style amélioré)


    // Clients
    setupTabClient();
    refreshClientsGrid();

    // Projets
    setupTabProjet();
    refreshProjetsGrid();

    // Staff
    setupTabStaff();
    refreshStaffGrid();

    // Materiel
    setupTabMateriel();
    refreshMaterielGrid();



    // Setup button groups for radio buttons
    setupButtonGroups();

    // Connexion explicite des boutons CRUD (si l'auto-connect ne marche pas)
    connect(ui->id_confirm, &QToolButton::clicked, this, &MainWindow::on_id_confirm_clicked);
    connect(ui->id_delete,  &QToolButton::clicked, this, &MainWindow::on_id_delete_clicked);

    // Connexion des boutons CRUD PROJET
    connect(ui->toolButton_52, &QToolButton::clicked, this, &MainWindow::on_toolButton_52_clicked);
    connect(ui->toolButton_56, &QToolButton::clicked, this, &MainWindow::on_toolButton_56_clicked);
    connect(ui->toolButton_57, &QToolButton::clicked, this, &MainWindow::on_toolButton_57_clicked);
    connect(ui->toolButton_58, &QToolButton::clicked, this, &MainWindow::on_toolButton_58_clicked);
    connect(ui->toolButton_53, &QToolButton::clicked, this, &MainWindow::on_toolButton_53_clicked);

    // Connexion des boutons CRUD STAFF
    connect(ui->toolButton_15, &QToolButton::clicked, this, &MainWindow::on_toolButton_15_clicked);
    connect(ui->toolButton_23, &QToolButton::clicked, this, &MainWindow::on_toolButton_23_clicked);
    connect(ui->toolButton_25, &QToolButton::clicked, this, &MainWindow::on_toolButton_25_clicked);
    connect(ui->toolButton_26, &QToolButton::clicked, this, &MainWindow::on_toolButton_26_clicked);

    // Connexion des boutons CRUD MATERIEL
    connect(ui->toolButton_31, &QToolButton::clicked, this, &MainWindow::on_toolButton_31_clicked);
    connect(ui->toolButton_33, &QToolButton::clicked, this, &MainWindow::on_toolButton_33_clicked);
    connect(ui->toolButton_34, &QToolButton::clicked, this, &MainWindow::on_toolButton_34_clicked);
    connect(ui->toolButton_35, &QToolButton::clicked, this, &MainWindow::on_toolButton_35_clicked);
    connect(ui->toolButton_36, &QToolButton::clicked, this, &MainWindow::on_toolButton_36_clicked);

    // Connexion du comboBox pour tri matériel
    connect(ui->comboBox_4, QOverload<const QString &>::of(&QComboBox::currentTextChanged),
            this, &MainWindow::on_comboBox_4_currentTextChanged);

    // Connexion des boutons CRUD SPONSOR
   connect(ui->AjouterSponsor, &QPushButton::clicked, this, &MainWindow::on_AjouterSponsor_clicked);
    // ========== CONNECTIONS SPONSOR - AJOUTER CES LIGNES ==========
    // Connexion du bouton Modifier
    connect(ui->ModifierSponsor, &QPushButton::clicked, this, &MainWindow::on_ModifierSponsor_clicked);

    // Connexion du bouton Supprimer
    connect(ui->SupprimerSponsor, &QPushButton::clicked, this, &MainWindow::on_SupprimerSponsor_clicked);

    // Connexion du bouton Annuler
    connect(ui->AnnulerSponsor, &QPushButton::clicked, this, &MainWindow::on_AnnulerSponsor_clicked);

    // Connexion du bouton Afficher (si pas déjà fait)
    connect(ui->AfficherSponsor, &QPushButton::clicked, this, &MainWindow::on_AfficherSponsor_clicked);

    // Connexion du bouton Rechercher
    connect(ui->RechercherSponsor, &QPushButton::clicked, this, &MainWindow::on_RechercherSponsor_clicked);
    // Remplacez l'ancienne connexion PDF par Excel :
    connect(ui->exportationpdf, &QPushButton::clicked, this, [this]() {
        SponsorManager::executerExportExcel(ui->tableWidget_2, this);
    });
    connect(ui->btn_actualiser, &QPushButton::clicked, this, [this]() {
        SponsorManager::afficherDashboardKPI(ui->groupBox_8);
    });
    connect(ui->btn_IA, &QToolButton::clicked, this, &MainWindow::on_btnIA_clicked);
    connect(ui->comboBox_tri, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_comboBox_tri_currentIndexChanged);
    // ========== CONFIGURATION TABLEAU SPONSOR ==========
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(ui->tableWidget_2, &QTableWidget::cellClicked, this, &MainWindow::on_tableWidget_2_cellClicked);

    // Configuration combobox contribution
    ui->combobox_contribution->addItems({"Services", "Matériels", "Autre"});

    // ========== SYSTÈME DE NOTIFICATION ==========
    QToolButton *btnNotification = new QToolButton(this);
    btnNotification->setText("🔔"); // ← ENLEVER L'ESPACE
    btnNotification->setToolButtonStyle(Qt::ToolButtonIconOnly); // ← ICÔNE SEULEMENT
    btnNotification->setFixedSize(50, 50); // ← TAILLE FIXE POUR UN CERCLE

    // Style pour un bouton rond
    btnNotification->setStyleSheet(
        "QToolButton { "
        "    color: white; border: none; "
        "    border-radius: 20px; " // ← CERCLE PARFAIT
        "    padding: 0px; " // ← PAS DE PADDING
        "    font-size: 30px; " // ← TAILLE DE LA CLOCHE
        "    font-weight: bold; "
        "    margin: 2px; "
        "}"
        "QToolButton:hover { background: #FF69B4; }"
        "QToolButton:pressed { background: #21618c; }"
        );

    // Badge de notification - POSITION RÉELLE EN HAUT À DROITE
    QLabel *badge = new QLabel("0", btnNotification);
    badge->setStyleSheet(
        "QLabel { "
        "    background: #e74c3c; color: white; font-size: 9px; font-weight: bold; "
        "    border-radius: 7px; padding: 1px 4px; "
        "    border: 1.5px solid white; "
        "}"
        );
    badge->setAlignment(Qt::AlignCenter);
    badge->setFixedSize(16, 16); // ← TAILLE FIXE
    badge->move(btnNotification->width() - 18, 8); // ← EN HAUT À DROITE
    badge->setVisible(false);

    connect(btnNotification, &QToolButton::clicked, this, [this]() {
        sponsorManager->afficherFenetreNotifications(this);
    });

    // Barre d'outils notification en HAUT À DROITE
    btnNotification->move(1410, 50);
    btnNotification->raise(); // ← METTRE DEVANT TOUS LES AUTRES WIDGETS
    btnNotification->show();

    // Timer pour rafraîchissement notifications
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [badge, btnNotification]() {
        int count = SponsorManager::getNombreNotifications();

        // NOUVEAU : Gestion améliorée du badge
        if (count > 0) {
            badge->setText(count > 9 ? "9+" : QString::number(count));
            badge->setVisible(true);
            btnNotification->setToolTip(QString("%1 notification(s)").arg(count));
        } else {
            badge->setVisible(false);
            btnNotification->setToolTip("Aucune notification");
        }

        // NOUVELLE POSITION : en haut à droite
        badge->move(btnNotification->width() - 18, 2);
    });
    timer->start(60000); // 1 minute

    // Premier rafraîchissement
    // Premier rafraîchissement
    int count = SponsorManager::getNombreNotifications();
    if (count > 0) {
        badge->setText(count > 9 ? "9+" : QString::number(count));
        badge->setVisible(true);
        btnNotification->setToolTip(QString("%1 notification(s)").arg(count));
    } else {
        badge->setVisible(false);
        btnNotification->setToolTip("Aucune notification");
    }
    sponsorManager = new SponsorManager(this);
    // ========== INITIALISATION FINALE ==========
    // ========== INITIALISATION FINALE ==========
    //GestionCreateur *gestionCreateur = new GestionCreateur(ui, this);
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
    ui->stackedWidget->setCurrentIndex(0);

    // Setup flashing timer for projects ending in the next week
    m_flashTimer = new QTimer(this);
    connect(m_flashTimer, &QTimer::timeout, this, &MainWindow::onFlashTimer);
    m_flashTimer->start(500);  // Flash every 500ms

    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow() { delete ui; }

// =====================
//  NAVIGATION
// =====================
// =====================
//  NAVIGATION AMÉLIORÉE
// =====================

void MainWindow::showStaff()
{
    ui->stackedWidget->setCurrentIndex(0);
    updateNavigationStyle(0);  // Active le bouton Staff
}

void MainWindow::showClient()
{
    ui->stackedWidget->setCurrentIndex(1);
    updateNavigationStyle(1);  // Active le bouton Client
}

void MainWindow::showMateriel()
{
    ui->stackedWidget->setCurrentIndex(2);
    updateNavigationStyle(2);  // Active le bouton Materiel
}

void MainWindow::showProjet()
{
    ui->stackedWidget->setCurrentIndex(3);
    updateNavigationStyle(3);  // Active le bouton Projet
}

void MainWindow::showSponsor()
{
    ui->stackedWidget->setCurrentIndex(4);
    updateNavigationStyle(4);  // Active le bouton Sponsor
}

void MainWindow::showCreateur()
{
    ui->stackedWidget->setCurrentIndex(5);
    updateNavigationStyle(5);  // Active le bouton Createur
}
// =====================
//  SETUP BUTTON GROUPS
// =====================
void MainWindow::setupButtonGroups()
{
    // Group for Staff competence radio buttons
    m_staffCompetenceGroup = new QButtonGroup(this);
    m_staffCompetenceGroup->addButton(ui->radioButton);      // Débutant
    m_staffCompetenceGroup->addButton(ui->radioButton_2);    // Intermédiaire
    m_staffCompetenceGroup->addButton(ui->radioButton_3);    // Avancé

    // Group for Materiel etat radio buttons
    m_materielEtatGroup = new QButtonGroup(this);
    m_materielEtatGroup->addButton(ui->radioButton_18);      // fonctionnel
    m_materielEtatGroup->addButton(ui->radioButton_19);      // en panne
    m_materielEtatGroup->addButton(ui->radioButton_20);      // en maintenance
    m_materielEtatGroup->addButton(ui->radioButton_21);      // hors service

    // Group for Materiel localisation radio buttons
    m_materielLocationGroup = new QButtonGroup(this);
    m_materielLocationGroup->addButton(ui->radioButton_22);  // studio tournage
    m_materielLocationGroup->addButton(ui->radioButton_23);  // salle montage
    m_materielLocationGroup->addButton(ui->radioButton_24);  // salle podcast
}

// ===================================================
//                  CLIENTS
// ===================================================
void MainWindow::setupTabClient()
{
    ui->tab_Client->setColumnCount(8);
    QStringList headers{
        "", "ID_CLIENT", "NOM", "PRENOM",
        "ENTREPRISE", "EMAIL", "TYPE", "DATE_AJOUT"
    };
    ui->tab_Client->setHorizontalHeaderLabels(headers);

    ui->tab_Client->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tab_Client->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_Client->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab_Client->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tab_Client->setColumnWidth(0, 56);

    connect(ui->tab_Client, &QTableWidget::cellClicked, this, [this](int row, int col){
        if (row < 0 || col == 0) return;
        populateClientFormFromRow(row);
        setClientFormMode(true);
    });
}

void MainWindow::on_btnCheckSuivi_clicked()
{
    if (ui->tab_Client->rowCount() == 0) {
        QMessageBox::information(this, "Suivi", "Aucun client à suivre.");
        return;
    }

    int totalClients = ui->tab_Client->rowCount();
    int entrepriseCount = 0, instagrameurCount = 0, autreCount = 0;

    for (int i = 0; i < ui->tab_Client->rowCount(); ++i) {
        QTableWidgetItem* typeItem = ui->tab_Client->item(i, 6);
        if (typeItem) {
            QString type = typeItem->text().toLower();
            if (type.contains("entreprise")) entrepriseCount++;
            else if (type.contains("instagram")) instagrameurCount++;
            else autreCount++;
        }
    }

    QString message = QString(
                          "Statistiques clients :\n"
                          "Total clients : %1\n"
                          "- Entreprises : %2\n"
                          "- Instagrameurs : %3\n"
                          "- Autres : %4"
                          ).arg(totalClients).arg(entrepriseCount).arg(instagrameurCount).arg(autreCount);

    QMessageBox::information(this, "Suivi Clients", message);
}

void MainWindow::on_btn_clientStats_clicked()
{
    buildClientStatsCharts();
}

void MainWindow::buildClientStatsCharts()
{
    QDialog statsDialog(this);
    statsDialog.setWindowTitle("Statistiques Clients");
    statsDialog.resize(600, 400);

    QVBoxLayout* layout = new QVBoxLayout(&statsDialog);
    QLabel* statsLabel = new QLabel();
    statsLabel->setText("Graphiques des statistiques clients - À implémenter avec QChart");
    statsLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(statsLabel);
    statsDialog.exec();
}

void MainWindow::refreshClientsGrid()
{
    ui->tab_Client->setRowCount(0);
    const auto rows = ClientDAO::fetchAll();
    for (int i = 0; i < rows.size(); ++i) {
        const auto &c = rows[i];
        ui->tab_Client->insertRow(i);
        ui->tab_Client->setItem(i,1, new QTableWidgetItem(QString::number(c.ID_CLIENT)));
        ui->tab_Client->setItem(i,2, new QTableWidgetItem(c.NOM));
        ui->tab_Client->setItem(i,3, new QTableWidgetItem(c.PRENOM));
        ui->tab_Client->setItem(i,4, new QTableWidgetItem(c.ENTREPRISE));
        ui->tab_Client->setItem(i,5, new QTableWidgetItem(c.EMAIL));
        ui->tab_Client->setItem(i,6, new QTableWidgetItem(c.TYPE));
        ui->tab_Client->setItem(i,7, new QTableWidgetItem(c.DATE_AJOUT.toString("yyyy-MM-dd")));
        addClientEditPenForRow(i);
    }
}

Client MainWindow::readClientForm() const
{
    Client c;
    c.ID_CLIENT  = ui->ID_CLIENT->text().trimmed().toInt();
    c.NOM        = ui->NOM->text().trimmed();
    c.PRENOM     = ui->PRENOM->text().trimmed();
    c.ENTREPRISE = ui->ENTREPRISE->text().trimmed();
    c.EMAIL      = ui->EMAIL->text().trimmed();

    if (ui->entre->isChecked())      c.TYPE = "entreprise";
    else if (ui->insta->isChecked()) c.TYPE = "instagrameur";
    else if (ui->autr->isChecked())  c.TYPE = "Autre";
    else                             c.TYPE = "";

    c.DATE_AJOUT = ui->DATE_AJOUT->date();

    return c;
}

void MainWindow::setClientFormMode(bool edit)
{
    m_clientEditMode = edit;
    if (edit) {
        ui->id_confirm->setText("Modifier");
        ui->ID_CLIENT->setEnabled(false);
    } else {
        ui->id_confirm->setText("Ajouter");
        ui->ID_CLIENT->setEnabled(true);
        ui->ID_CLIENT->clear();
        ui->NOM->clear();
        ui->PRENOM->clear();
        ui->ENTREPRISE->clear();
        ui->EMAIL->clear();
        ui->DATE_AJOUT->setDate(QDate::currentDate());
        ui->entre->setChecked(false);
        ui->insta->setChecked(false);
        ui->autr->setChecked(false);
    }
}

void MainWindow::populateClientFormFromRow(int row)
{
    if (row < 0) return;
    ui->ID_CLIENT->setText(ui->tab_Client->item(row,1)->text());
    ui->NOM->setText(ui->tab_Client->item(row,2)->text());
    ui->PRENOM->setText(ui->tab_Client->item(row,3)->text());
    ui->ENTREPRISE->setText(ui->tab_Client->item(row,4)->text());
    ui->EMAIL->setText(ui->tab_Client->item(row,5)->text());
    ui->DATE_AJOUT->setDate(QDate::fromString(ui->tab_Client->item(row,7)->text(), "yyyy-MM-dd"));

    QString type = ui->tab_Client->item(row,6)->text().toLower();
    ui->entre->setChecked(false);
    ui->insta->setChecked(false);
    ui->autr->setChecked(false);

    if (type.contains("entreprise") || type == "entreprise") {
        ui->entre->setChecked(true);
    } else if (type.contains("instagram") || type == "instagrameur") {
        ui->insta->setChecked(true);
    } else if (!type.isEmpty()) {
        ui->autr->setChecked(true);
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
        QPoint p = cell->mapTo(ui->tab_Client->viewport(), QPoint(2,2));
        int row = ui->tab_Client->indexAt(p).row();
        if (row < 0) return;
        populateClientFormFromRow(row);
        setClientFormMode(true);
    });

    auto *cell = new QWidget;
    auto *lay  = new QHBoxLayout(cell);
    lay->setContentsMargins(2,0,2,0);
    lay->setAlignment(Qt::AlignCenter);
    lay->addWidget(editBtn);
    ui->tab_Client->setCellWidget(row, 0, cell);
}

// ===============================
//  CONFIRM : ADD / UPDATE
// ===============================
void MainWindow::on_id_confirm_clicked()
{
    const QString idT  = ui->ID_CLIENT->text().trimmed();
    const QString nomT = ui->NOM->text().trimmed();
    const QString preT = ui->PRENOM->text().trimmed();
    const QString entT = ui->ENTREPRISE->text().trimmed();
    const QString mailT= ui->EMAIL->text().trimmed();

    bool typeSelected = ui->entre->isChecked() || ui->insta->isChecked() || ui->autr->isChecked();

    static const QRegularExpression reInt(R"(^\d+$)");
    static const QRegularExpression reText(R"(^[a-zA-ZÀ-ÿ\s'-]+$)");
    static const QRegularExpression reEmail(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");

    if (idT.isEmpty() || nomT.isEmpty() || preT.isEmpty() ||
        entT.isEmpty() || mailT.isEmpty() || !typeSelected) {
        QMessageBox::warning(this, "Validation", "Tous les champs sont obligatoires.");
        return;
    }

    if (!reInt.match(idT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "ID_CLIENT doit être un nombre.");
        ui->ID_CLIENT->setFocus();
        return;
    }
    if (idT.length() != 8) {
        QMessageBox::warning(this, "Validation", "ID_CLIENT doit contenir exactement 8 chiffres.");
        ui->ID_CLIENT->setFocus();
        return;
    }

    if (!reText.match(nomT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le nom doit contenir uniquement des lettres.");
        ui->NOM->setFocus();
        return;
    }
    if (!reText.match(preT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le prénom doit contenir uniquement des lettres.");
        ui->PRENOM->setFocus();
        return;
    }
    if (!reText.match(entT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "L'entreprise doit contenir uniquement des lettres.");
        ui->ENTREPRISE->setFocus();
        return;
    }

    if (!reEmail.match(mailT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "L'email doit avoir un format valide (exemple: nom@domaine.com).");
        ui->EMAIL->setFocus();
        return;
    }

    Client c = readClientForm();

    bool ok = false;

    if (!m_clientEditMode) {
        c.DATE_AJOUT = QDate::currentDate();

        if (ClientDAO::exists(c.ID_CLIENT)) {
            QMessageBox::warning(this, "Doublon", "ID_CLIENT existe déjà.");
            return;
        }

        ok = ClientDAO::create(c);
        if (!ok) return;

        QMessageBox::information(this, "Succès", "Client ajouté.");
        ClientHistory::addEntry("Ajout", c.ID_CLIENT, c.NOM);

    } else {
        ok = ClientDAO::update(c);
        if (!ok) return;

        QMessageBox::information(this, "Succès", "Client mis à jour.");
        ClientHistory::addEntry("Modification", c.ID_CLIENT, c.NOM);
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

    QString nomClient;
    for (int row = 0; row < ui->tab_Client->rowCount(); ++row) {
        QTableWidgetItem* idItem = ui->tab_Client->item(row, 1);
        if (idItem && idItem->text() == QString::number(id)) {
            QTableWidgetItem* nomItem = ui->tab_Client->item(row, 2);
            if (nomItem) nomClient = nomItem->text();
            break;
        }
    }

    if (QMessageBox::question(this, "Confirmer",
                              QString("Supprimer le client %1 ?").arg(id))
        != QMessageBox::Yes)
        return;

    if (ClientDAO::remove(id)) {
        refreshClientsGrid();
        ui->ID_CLIENT->clear();

        ClientHistory::addEntry("Suppression", id,
                                nomClient.isEmpty() ? QStringLiteral("Inconnu") : nomClient);
    }
}

void MainWindow::on_toolButton_5_clicked()
{
    QString idText = ui->lineEdit_38->text().trimmed();

    if (idText.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez entrer un ID_CLIENT à rechercher.");
        ui->lineEdit_38->setFocus();
        return;
    }

    bool ok;
    int id = idText.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Recherche", "ID_CLIENT doit être un nombre entier.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM ABIR.CLIENT WHERE ID_CLIENT = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur SQL lors de la recherche.");
        return;
    }

    ui->tab_Client->setRowCount(0);

    if (!query.next()) {
        QMessageBox::information(this, "Recherche", "Aucun client trouvé.");
        return;
    }

    ui->tab_Client->insertRow(0);
    ui->tab_Client->setItem(0,1,new QTableWidgetItem(query.value("ID_CLIENT").toString()));
    ui->tab_Client->setItem(0,2,new QTableWidgetItem(query.value("NOM").toString()));
    ui->tab_Client->setItem(0,3,new QTableWidgetItem(query.value("PRENOM").toString()));
    ui->tab_Client->setItem(0,4,new QTableWidgetItem(query.value("ENTREPRISE").toString()));
    ui->tab_Client->setItem(0,5,new QTableWidgetItem(query.value("EMAIL").toString()));
    ui->tab_Client->setItem(0,6,new QTableWidgetItem(query.value("TYPE").toString()));

    addClientEditPenForRow(0);

    QMessageBox::information(this, "Recherche", "Client trouvé !");
}

void MainWindow::on_comboBox_15_currentTextChanged(const QString &tri)
{
    if (tri == "Par défaut") {
        refreshClientsGrid();
        return;
    }

    QSqlQuery query;

    if (tri == "Nom (A→Z)") {
        query.prepare("SELECT * FROM ABIR.CLIENT ORDER BY NOM ASC");
    }
    else if (tri == "Nom (Z→A)") {
        query.prepare("SELECT * FROM ABIR.CLIENT ORDER BY NOM DESC");
    }
    else {
        refreshClientsGrid();
        return;
    }

    if (!query.exec()) return;

    ui->tab_Client->setRowCount(0);
    int row = 0;

    while (query.next()) {
        ui->tab_Client->insertRow(row);
        ui->tab_Client->setItem(row,1,new QTableWidgetItem(query.value("ID_CLIENT").toString()));
        ui->tab_Client->setItem(row,2,new QTableWidgetItem(query.value("NOM").toString()));
        ui->tab_Client->setItem(row,3,new QTableWidgetItem(query.value("PRENOM").toString()));
        ui->tab_Client->setItem(row,4,new QTableWidgetItem(query.value("ENTREPRISE").toString()));
        ui->tab_Client->setItem(row,5,new QTableWidgetItem(query.value("EMAIL").toString()));
        ui->tab_Client->setItem(row,6,new QTableWidgetItem(query.value("TYPE").toString()));
        addClientEditPenForRow(row);
        row++;
    }
}

/// ===================================================
//                  PROJETS
// ===================================================
void MainWindow::setupTabProjet()
{
    ui->tableWidget_7->setColumnCount(6);
    QStringList headers{ "ID_PROJET", "TYPE", "DATE_D", "DATE_F", "MONTANT", "PAIMENT", "MATRIEL" };
    ui->tableWidget_7->setHorizontalHeaderLabels(headers);

    ui->tableWidget_7->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_7->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_7->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_7->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->comboBox_12->clear();
    ui->comboBox_12->addItem("Par défaut");
    ui->comboBox_12->addItem("Date début (asc)");
    ui->comboBox_12->addItem("Date début (desc)");
    ui->comboBox_12->addItem("Date fin (asc)");
    ui->comboBox_12->addItem("Date fin (desc)");
    ui->comboBox_12->addItem("Montant (asc)");
    ui->comboBox_12->addItem("Montant (desc)");
}

void MainWindow::on_toolButton_55_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Exporter en PDF", "projets_export.pdf", "Fichiers PDF (*.pdf)");
    if (filePath.isEmpty())
        return;

    QString html;
    html += "<html><head><meta charset='UTF-8'>";
    html += "<style>"
            "table { border-collapse: collapse; width: 100%; font-size: 10pt; }"
            "th, td { border: 1px solid black; padding: 6px; text-align: center; }"
            "th { background-color: #d0e0ff; font-weight: bold; }"
            "h2 { text-align: center; }"
            "</style></head><body>";

    html += "<h2>Liste des Projets Exportée</h2>";
    html += "<p>Date d'exportation : " + QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss") + "</p>";

    html += "<table>"
            "<tr>"
            "<th>ID Projet</th>"
            "<th>Type</th>"
            "<th>Date Début</th>"
            "<th>Date Fin</th>"
            "<th>Paiment</th>"
            "<th>Montant</th>"
            "<th>MATRIEL</th>"
            "</tr>";

    Connection* conn = Connection::getInstance();
    QSqlDatabase db = conn->getDatabase();

    if (!db.isOpen()) {
        if (!conn->openConnection()) return;
    }

    QSqlQuery query(db);
    QString queryStr = "SELECT id_projet, type, date_d, date_f, paiment, montant, matriel FROM projet";

    if (!query.exec(queryStr)) {
        QMessageBox::warning(this, "Erreur", "Impossible de lire les données : " + query.lastError().text());
        return;
    }

    bool hasData = false;

    while (query.next()) {
        hasData = true;

        html += "<tr>";
        html += "<td>" + query.value("id_projet").toString() + "</td>";
        html += "<td>" + query.value("type").toString() + "</td>";
        html += "<td>" + query.value("date_d").toDate().toString("dd/MM/yyyy") + "</td>";
        html += "<td>" + query.value("date_f").toDate().toString("dd/MM/yyyy") + "</td>";
        html += "<td>" + query.value("paiment").toString() + "</td>";
        html += "<td>" + query.value("montant").toString() + "</td>";
        html += "<td>" + query.value("matriel").toString() + "</td>";
        html += "</tr>";
    }

    if (!hasData) {
        QMessageBox::information(this, "Exportation", "Aucun projet trouvé dans la base.");
        return;
    }

    html += "</table></body></html>";

    QTextDocument doc;
    doc.setHtml(html);

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);

    doc.print(&printer);

    QMessageBox::information(this, "Succès",
                             "Les projets ont été exportés avec succès dans :\n" + filePath);
}

void MainWindow::refreshProjetsGrid()
{
    m_flashingRows.clear();
    m_flashOn = false;
    ui->tableWidget_7->setRowCount(0);

    QSqlQuery query;
    query.prepare("SELECT ID_PROJET, TYPE, TO_CHAR(DATE_D, 'YYYY-MM-DD') AS DATE_D, "
                  "TO_CHAR(DATE_F, 'YYYY-MM-DD') AS DATE_F, MONTANT, PAIMENT, MATRIEL FROM ABIR.PROJET");

    if (!query.exec()) {
        qDebug() << "Error refreshing projets grid:" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->tableWidget_7->insertRow(row);
        ui->tableWidget_7->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget_7->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget_7->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget_7->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        ui->tableWidget_7->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
        ui->tableWidget_7->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
        ui->tableWidget_7->setItem(row, 6, new QTableWidgetItem(query.value(6).toString()));

        QString dateFStr = query.value(3).toString();
        QDate dateF = QDate::fromString(dateFStr, "yyyy-MM-dd");
        QDate today = QDate::currentDate();
        if (dateF.isValid()) {
            QDate twoWeeksBefore = dateF.addDays(-14);
            QDate oneWeekBefore  = dateF.addDays(-7);

            if (dateF < today) {
                QBrush brush(QColor(255, 180, 180));
                for (int c = 0; c < 6; ++c) ui->tableWidget_7->item(row, c)->setBackground(brush);
            }
            else if (today >= oneWeekBefore && today <= dateF) {
                m_flashingRows.append(row);
                for (int c = 0; c < 6; ++c) ui->tableWidget_7->item(row, c)->setData(Qt::BackgroundRole, QVariant());
            }
            else if (today >= twoWeeksBefore && today < oneWeekBefore) {
                QBrush brush(QColor(255, 250, 180));
                for (int c = 0; c < 6; ++c) ui->tableWidget_7->item(row, c)->setBackground(brush);
            }
            else if (today < twoWeeksBefore) {
                QBrush brush(QColor(200, 255, 200));
                for (int c = 0; c < 6; ++c) ui->tableWidget_7->item(row, c)->setBackground(brush);
            }
        }

        row++;
    }
    updateProjetStatistics();
}

Projet MainWindow::readProjetForm() const
{
    Projet p;
    p.setId(ui->lineEdit_31->text().trimmed().toInt());
    p.setType(ui->comboBox_13->currentText());
    p.setDateDebut(ui->dateEdit_7->date());
    p.setDateFin(ui->dateEdit_8->date());
    p.setMontant(ui->lineEdit_32->text().trimmed().toDouble());
    p.setPaiment(ui->comboBox_14->currentText());

    const QString idClientStr = ui->lineEdit_38->text().trimmed();
    if (!idClientStr.isEmpty()) {
        bool ok;
        int idClient = idClientStr.toInt(&ok);
        if (ok && idClient > 0) {
            p.setIdClient(idClient);
        } else {
            p.setIdClient(0);
        }
    } else {
        p.setIdClient(0);
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
    ui->lineEdit_38->clear();
}

void MainWindow::populateProjetFormFromRow(int row)
{
    if (row < 0 || row >= ui->tableWidget_7->rowCount()) return;

    QTableWidgetItem* idItem = ui->tableWidget_7->item(row, 0);
    QTableWidgetItem* typeItem = ui->tableWidget_7->item(row, 1);
    QTableWidgetItem* dateDItem = ui->tableWidget_7->item(row, 2);
    QTableWidgetItem* dateFItem = ui->tableWidget_7->item(row, 3);
    QTableWidgetItem* montantItem = ui->tableWidget_7->item(row, 4);
    QTableWidgetItem* paimentItem = ui->tableWidget_7->item(row, 5);
    QTableWidgetItem* matrielItem = ui->tableWidget_7->item(row, 6);

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
    if (paimentItem && !paimentItem->text().isEmpty() && paimentItem->text() != "N/A") {
        int index = ui->comboBox_14->findText(paimentItem->text());
        if (index >= 0) ui->comboBox_14->setCurrentIndex(index);
    } else {
        ui->comboBox_14->setCurrentIndex(0);
    }

    ui->lineEdit_38->clear();
}

void MainWindow::setProjetFormMode(bool edit)
{
    m_projetEditMode = edit;
    if (edit) {
        ui->toolButton_52->setText("Modifier");
        ui->lineEdit_31->setEnabled(false);
    } else {
        ui->toolButton_52->setText("Ajouter");
        ui->lineEdit_31->setEnabled(true);
        clearProjetForm();
    }
}

void MainWindow::on_toolButton_52_clicked()
{
    const QString idT = ui->lineEdit_31->text().trimmed();
    const QString montantT = ui->lineEdit_32->text().trimmed();
    const QString idClientT = ui->lineEdit_38->text().trimmed();

    static const QRegularExpression reInt(R"(^\d+$)");
    static const QRegularExpression reDouble(R"(^\d+(\.\d+)?$)");

    if (idT.isEmpty() || montantT.isEmpty() || ui->comboBox_13->currentText().isEmpty()) {
        QMessageBox::warning(this, "Validation", "ID_PROJET, TYPE et  Montant sont obligatoires.");
        return;
    }

    if (!reInt.match(idT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "ID_PROJET doit être un nombre.");
        ui->lineEdit_31->setFocus();
        return;
    }

    if (idT.length() != 3) {
        QMessageBox::warning(this, "Validation", "ID_PROJET doit contenir exactement 3 chiffres (exemple: 123).");
        ui->lineEdit_31->setFocus();
        return;
    }

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
        if (p.AjouterProjet()) {
            QMessageBox::information(this, "Succès", "Projet ajouté avec succès.");
            clearProjetForm();
            refreshProjetsGrid();
        } else {
            QMessageBox::critical(this, "Erreur", "Projet existe déjà id doit etre unique.");
        }
    } else {
        if (p.ModifierProjet()) {
            QMessageBox::information(this, "Succès", "Projet modifié avec succès.");
            setProjetFormMode(false);
            refreshProjetsGrid();
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la modification du projet. Vérifiez les logs.");
        }
    }
}

void MainWindow::on_toolButton_56_clicked()
{
    refreshProjetsGrid();
}

void MainWindow::on_toolButton_57_clicked()
{
    int currentRow = ui->tableWidget_7->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Suppression", "Sélectionne une ligne dans le tableau pour supprimer un projet.");
        return;
    }

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

void MainWindow::on_toolButton_58_clicked()
{
    int currentRow = ui->tableWidget_7->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Édition", "Sélectionne une ligne dans le tableau pour éditer un projet.");
        return;
    }

    populateProjetFormFromRow(currentRow);
    setProjetFormMode(true);
}

void MainWindow::on_toolButton_53_clicked()
{
    setProjetFormMode(false);
}

void MainWindow::on_comboBox_12_currentTextChanged(const QString &text)
{
    if (text == "Par défaut") {
        refreshProjetsGrid();
    } else {
        Projet projet;
        QSqlQueryModel* model = projet.AfficherProjetsTriés(text);

        if (!model) return;

        ui->tableWidget_7->setRowCount(0);

        for (int i = 0; i < model->rowCount(); ++i) {
            ui->tableWidget_7->insertRow(i);
            ui->tableWidget_7->setItem(i, 0, new QTableWidgetItem(model->data(model->index(i, 0)).toString()));
            ui->tableWidget_7->setItem(i, 1, new QTableWidgetItem(model->data(model->index(i, 1)).toString()));
            ui->tableWidget_7->setItem(i, 2, new QTableWidgetItem(model->data(model->index(i, 2)).toString()));
            ui->tableWidget_7->setItem(i, 3, new QTableWidgetItem(model->data(model->index(i, 3)).toString()));
            ui->tableWidget_7->setItem(i, 4, new QTableWidgetItem(model->data(model->index(i, 4)).toString()));
            ui->tableWidget_7->setItem(i, 5, new QTableWidgetItem(model->data(model->index(i, 5)).toString()));
            ui->tableWidget_7->setItem(i, 6, new QTableWidgetItem(model->data(model->index(i, 6)).toString()));
        }

        delete model;
    }
}

void MainWindow::on_toolButton_54_clicked()
{
    QString searchText = ui->lineEdit_30->text().trimmed();

    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez entrer un ID de projet ou un TYPE (ex: podcast, live) à rechercher.");
        ui->lineEdit_30->setFocus();
        return;
    }

    bool ok;
    int id = searchText.toInt(&ok);
    QSqlQueryModel* model = nullptr;

    if (ok && id > 0) {
        model = Projet::ChercherProjetParIdStatique(id);
        if (!model) {
            QMessageBox::warning(this, "Recherche", "Erreur lors de la recherche par ID.");
            return;
        }
        if (model->rowCount() == 0) {
            QMessageBox::information(this, "Recherche", QString("Aucun projet trouvé avec l'ID %1.").arg(id));
            delete model;
            return;
        }
    } else {
        QString typeText = searchText;
        model = Projet::ChercherProjetParTypeStatique(typeText);
        if (!model) {
            QMessageBox::warning(this, "Recherche", "Erreur lors de la recherche par TYPE.");
            return;
        }
        if (model->rowCount() == 0) {
            QMessageBox::information(this, "Recherche", QString("Aucun projet trouvé avec le type '%1'.").arg(typeText));
            delete model;
            return;
        }
    }

    ui->tableWidget_7->setRowCount(0);
    for (int i = 0; i < model->rowCount(); ++i) {
        ui->tableWidget_7->insertRow(i);
        ui->tableWidget_7->setItem(i, 0, new QTableWidgetItem(model->data(model->index(i, 0)).toString()));
        ui->tableWidget_7->setItem(i, 1, new QTableWidgetItem(model->data(model->index(i, 1)).toString()));
        ui->tableWidget_7->setItem(i, 2, new QTableWidgetItem(model->data(model->index(i, 2)).toString()));
        ui->tableWidget_7->setItem(i, 3, new QTableWidgetItem(model->data(model->index(i, 3)).toString()));
        ui->tableWidget_7->setItem(i, 4, new QTableWidgetItem(model->data(model->index(i, 4)).toString()));
        ui->tableWidget_7->setItem(i, 5, new QTableWidgetItem(model->data(model->index(i, 5)).toString()));
        ui->tableWidget_7->setItem(i, 6, new QTableWidgetItem(model->data(model->index(i, 6)).toString()));
    }

    delete model;

    if (ok && id > 0) {
        QMessageBox::information(this, "Recherche", QString("Projet trouvé avec l'ID %1.").arg(id));
    } else {
        QMessageBox::information(this, "Recherche", QString("Projets trouvés avec le type '%1'.").arg(searchText));
    }
}

void MainWindow::updateProjetStatistics()
{
    if (m_projetChartView) {
        delete m_projetChartView;
        m_projetChartView = nullptr;
    }
    if (m_projetChartView2) {
        delete m_projetChartView2;
        m_projetChartView2 = nullptr;
    }

    QVector<QPair<QString,int>> counts = Projet::CountsByType();
    int total = 0;
    for (const auto &p : counts) total += p.second;

    QLabel *totalLabel = this->findChild<QLabel*>("label_total_count_3");
    if (totalLabel) {
        totalLabel->setText(QString::number(total));
    }

    QPieSeries *series = new QPieSeries();
    for (const auto &p : counts) {
        QString label = p.first.isEmpty() ? "(vide)" : p.first;
        series->append(label, p.second);
    }

    if (series->count() == 0) {
        series->append("Aucun projet", 1);
        QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible(true);
    } else {
        for (QPieSlice *slice : series->slices()) {
            slice->setLabelVisible(true);
            slice->setLabel(QString("%1 (%2)").arg(slice->label()).arg(QString::number(int(slice->percentage()*100))) );
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Répartition des projets par type");
    chart->legend()->setAlignment(Qt::AlignRight);

    QWidget *statsParent = this->findChild<QWidget*>("groupBox_statistics_3");
    if (!statsParent) {
        statsParent = this->findChild<QWidget*>("tab_14");
    }
    if (!statsParent && ui->tableWidget_7) {
        statsParent = ui->tableWidget_7->parentWidget();
    }
    if (!statsParent) {
        statsParent = this;
    }

    QChartView *chartView = new QChartView(chart, statsParent);
    chartView->setRenderHint(QPainter::Antialiasing);

    if (statsParent == this->findChild<QWidget*>("groupBox_statistics_3") || statsParent == this->findChild<QWidget*>("tab_14")) {
        chartView->setGeometry(30, 80, 360, 360);
    } else if (ui->tableWidget_7) {
        QRect r = ui->tableWidget_7->geometry();
        chartView->setGeometry(r.right() + 10, r.top(), 360, 360);
    } else {
        chartView->setGeometry(30, 80, 360, 360);
    }

    chartView->show();
    m_projetChartView = chartView;

    QVector<QPair<QString,int>> countsByPaiment = Projet::CountsByPaiment();
    QPieSeries *series2 = new QPieSeries();
    int totalByPaiment = 0;
    for (const auto &pr : countsByPaiment) {
        QString lab = pr.first.isEmpty() ? "(N/A)" : pr.first;
        series2->append(lab, pr.second);
        totalByPaiment += pr.second;
    }
    if (series2->count() == 0) {
        series2->append("Aucun projet", 1);
    }

    QChart *chart2 = new QChart();
    chart2->addSeries(series2);
    chart2->setTitle("Répartition par méthode de paiement");
    chart2->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView2 = new QChartView(chart2, statsParent);
    chartView2->setRenderHint(QPainter::Antialiasing);

    QRect r = chartView->geometry();
    chartView2->setGeometry(r.right() + 20, r.top(), r.width(), r.height());
    chartView2->show();
    m_projetChartView2 = chartView2;

    QLabel *montantLabel = this->findChild<QLabel*>("label_total_montant_3");
    if (montantLabel) {
        montantLabel->setText(QString::number(totalByPaiment));
    }
}

void MainWindow::onFlashTimer()
{
    if (m_flashingRows.empty()) return;
    m_flashOn = !m_flashOn;
    QBrush flashBrush(QColor(255, 120, 120));
    for (int row : m_flashingRows) {
        if (row < 0 || row >= ui->tableWidget_7->rowCount()) continue;
        for (int c = 0; c < ui->tableWidget_7->columnCount(); ++c) {
            QTableWidgetItem *it = ui->tableWidget_7->item(row, c);
            if (!it) continue;
            if (m_flashOn) it->setBackground(flashBrush);
            else it->setData(Qt::BackgroundRole, QVariant());
        }
    }
}

// ===================================================
//                  STAFF
// ===================================================
void MainWindow::setupTabStaff()
{
    ui->tableWidget_3->setColumnCount(9);
    QStringList headers{"","ID", "NOM", "PRENOM", "POSTE", "COMPETENCE", "TELEPHONE", "EMAIL", "MOT_DE_PASSE" };
    ui->tableWidget_3->setHorizontalHeaderLabels(headers);

    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_3->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_3->setColumnWidth(0, 56);

    connect(ui->staffCancelForm, &QToolButton::clicked, this, &MainWindow::on_staffCancelForm_clicked);
    connect(ui->comboBox, QOverload<const QString&>::of(&QComboBox::currentTextChanged),
            this, &MainWindow::on_comboBox_currentTextChanged);
    connect(ui->toolButton_27, &QToolButton::clicked, this, &MainWindow::rechercherStaff);

    initializeStaffSortComboBox();
    afficherStatistiquesDansGroupBox();
    afficherStatistiquesCompetencesDansGroupBox4();
}

void MainWindow::refreshStaffGrid()
{
    ui->tableWidget_3->setRowCount(0);

    Staff staff;
    QSqlQueryModel* model = staff.afficher();

    if (!model) return;

    for (int i = 0; i < model->rowCount(); ++i) {
        ui->tableWidget_3->insertRow(i);
        ui->tableWidget_3->setItem(i, 1, new QTableWidgetItem(model->data(model->index(i, 0)).toString()));
        ui->tableWidget_3->setItem(i, 2, new QTableWidgetItem(model->data(model->index(i, 1)).toString()));
        ui->tableWidget_3->setItem(i, 3, new QTableWidgetItem(model->data(model->index(i, 2)).toString()));
        ui->tableWidget_3->setItem(i, 4, new QTableWidgetItem(model->data(model->index(i, 3)).toString()));
        ui->tableWidget_3->setItem(i, 5, new QTableWidgetItem(model->data(model->index(i, 4)).toString()));
        ui->tableWidget_3->setItem(i, 6, new QTableWidgetItem(model->data(model->index(i, 5)).toString()));
        ui->tableWidget_3->setItem(i, 7, new QTableWidgetItem(model->data(model->index(i, 6)).toString()));
        ui->tableWidget_3->setItem(i, 8, new QTableWidgetItem(model->data(model->index(i, 7)).toString()));
        addStaffEditPenForRow(i);
    }

    delete model;
    mettreAJourStatistiques();
    mettreAJourStatistiquesCompetences();
}

Staff MainWindow::readStaffForm() const
{
    QString id = ui->lineEdit_13->text().trimmed();
    QString nom = ui->lineEdit_14->text().trimmed();
    QString prenom = ui->lineEdit_20->text().trimmed();
    QString poste = ui->comboBox_6->currentText();
    QString telephone = ui->lineEdit_19->text().trimmed();

    QString competence;
    if (ui->radioButton->isChecked()) {
        competence = "Débutant";
    } else if (ui->radioButton_2->isChecked()) {
        competence = "Intermédiaire";
    } else if (ui->radioButton_3->isChecked()) {
        competence = "Avancé";
    } else {
        competence = "";
    }

    QString email;
    QString motDePasse;

    QLineEdit* emailField = this->findChild<QLineEdit*>("staffEmailLineEdit");
    if (emailField) {
        email = emailField->text().trimmed();
    } else {
        email = nom.toLower() + "." + prenom.toLower() + "@company.com";
    }

    QLineEdit* passwordField = this->findChild<QLineEdit*>("staffMotDePasseLineEdit");
    if (passwordField) {
        motDePasse = passwordField->text().trimmed();
    } else {
        motDePasse = "";
    }

    return Staff(id, nom, prenom, poste, competence, telephone, email, motDePasse);
}

void MainWindow::clearStaffForm()
{
    ui->lineEdit_13->clear();
    ui->lineEdit_14->clear();
    ui->lineEdit_20->clear();
    ui->lineEdit_19->clear();
    ui->comboBox_6->setCurrentIndex(0);

    QLineEdit* emailField = this->findChild<QLineEdit*>("staffEmailLineEdit");
    if (emailField) {
        emailField->clear();
    }
    QLineEdit* passwordField = this->findChild<QLineEdit*>("staffMotDePasseLineEdit");
    if (passwordField) {
        passwordField->clear();
    }

    if (m_staffCompetenceGroup->checkedButton()) {
        m_staffCompetenceGroup->setExclusive(false);
        m_staffCompetenceGroup->checkedButton()->setChecked(false);
        m_staffCompetenceGroup->setExclusive(true);
    }
}

void MainWindow::populateStaffFormFromRow(int row)
{
    if (row < 0 || row >= ui->tableWidget_3->rowCount()) return;

    QTableWidgetItem* idItem = ui->tableWidget_3->item(row, 1);
    QTableWidgetItem* nomItem = ui->tableWidget_3->item(row, 2);
    QTableWidgetItem* prenomItem = ui->tableWidget_3->item(row, 3);
    QTableWidgetItem* posteItem = ui->tableWidget_3->item(row, 4);
    QTableWidgetItem* competenceItem = ui->tableWidget_3->item(row, 5);
    QTableWidgetItem* telephoneItem = ui->tableWidget_3->item(row, 6);
    QTableWidgetItem* emailItem = ui->tableWidget_3->item(row, 7);
    QTableWidgetItem* passwordItem = ui->tableWidget_3->item(row, 8);

    if (idItem) ui->lineEdit_13->setText(idItem->text());
    if (nomItem) ui->lineEdit_14->setText(nomItem->text());
    if (prenomItem) ui->lineEdit_20->setText(prenomItem->text());
    if (telephoneItem) ui->lineEdit_19->setText(telephoneItem->text());

    QLineEdit* emailField = this->findChild<QLineEdit*>("staffEmailLineEdit");
    if (emailItem && emailField) {
        emailField->setText(emailItem->text());
    }

    QLineEdit* passwordField = this->findChild<QLineEdit*>("staffMotDePasseLineEdit");
    if (passwordItem && passwordField) {
        passwordField->setText(passwordItem->text());
    }

    if (posteItem) {
        int index = ui->comboBox_6->findText(posteItem->text());
        if (index >= 0) ui->comboBox_6->setCurrentIndex(index);
    }

    if (competenceItem) {
        QString competence = competenceItem->text().toLower();
        ui->radioButton->setChecked(false);
        ui->radioButton_2->setChecked(false);
        ui->radioButton_3->setChecked(false);

        if (competence.contains("débutant") || competence.contains("debutant")) {
            ui->radioButton->setChecked(true);
        } else if (competence.contains("intermédiaire") || competence.contains("intermediaire")) {
            ui->radioButton_2->setChecked(true);
        } else if (competence.contains("avancé") || competence.contains("avance")) {
            ui->radioButton_3->setChecked(true);
        }
    }
}

void MainWindow::setStaffFormMode(bool edit)
{
    m_staffEditMode = edit;
    if (edit) {
        ui->toolButton_15->setText("Modifier");
        ui->lineEdit_13->setEnabled(false);
    } else {
        ui->toolButton_15->setText("Ajouter");
        ui->lineEdit_13->setEnabled(true);
    }
}

void MainWindow::addStaffEditPenForRow(int row)
{
    auto *editBtn = new QPushButton;
    editBtn->setToolTip("Edit");
    editBtn->setFlat(true);
    editBtn->setCursor(Qt::PointingHandCursor);
    const char* kPen = ":/image/ressource/edit.png";
    if (QFile::exists(kPen))
        editBtn->setIcon(QIcon(kPen));
    else editBtn->setText("✎");
    editBtn->setIconSize(QSize(18,18));
    editBtn->setStyleSheet("QPushButton{border:none;}");
    editBtn->setFixedSize(26,26);

    connect(editBtn, &QPushButton::clicked, this, [this, editBtn](){
        QWidget* cell = editBtn->parentWidget();
        QPoint p = cell->mapTo(ui->tableWidget_3->viewport(), QPoint(2,2));
        int row = ui->tableWidget_3->indexAt(p).row();
        if (row < 0) return;
        populateStaffFormFromRow(row);
        setStaffFormMode(true);
    });

    auto *cell = new QWidget;
    auto *lay  = new QHBoxLayout(cell);
    lay->setContentsMargins(2,0,2,0);
    lay->setAlignment(Qt::AlignCenter);
    lay->addWidget(editBtn);
    ui->tableWidget_3->setCellWidget(row, 0, cell);
}

void MainWindow::on_toolButton_15_clicked()
{
    const QString idT = ui->lineEdit_13->text().trimmed();
    const QString nomT = ui->lineEdit_14->text().trimmed();
    const QString prenomT = ui->lineEdit_20->text().trimmed();
    const QString telephoneT = ui->lineEdit_19->text().trimmed();

    bool competenceSelected = ui->radioButton->isChecked() ||
                              ui->radioButton_2->isChecked() ||
                              ui->radioButton_3->isChecked();

    static const QRegularExpression reInt(R"(^\d+$)");
    static const QRegularExpression reText(R"(^[a-zA-ZÀ-ÿ\s'-]+$)");

    if (idT.isEmpty() || nomT.isEmpty() || prenomT.isEmpty() ||
        telephoneT.isEmpty() || ui->comboBox_6->currentText().isEmpty() || !competenceSelected) {
        QMessageBox::warning(this, "Validation", "Tous les champs sont obligatoires.");
        return;
    }

    if (!reInt.match(idT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "ID_EMPLOYE doit être un nombre.");
        ui->lineEdit_13->setFocus();
        return;
    }

    if (idT.length() != 8) {
        QMessageBox::warning(this, "Validation", "ID_EMPLOYE doit contenir exactement 8 chiffres (exemple: 12345678).");
        ui->lineEdit_13->setFocus();
        return;
    }

    if (!reText.match(nomT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le nom doit contenir uniquement des lettres.");
        ui->lineEdit_14->setFocus();
        return;
    }

    if (!reText.match(prenomT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le prénom doit contenir uniquement des lettres.");
        ui->lineEdit_20->setFocus();
        return;
    }

    if (!reInt.match(telephoneT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le téléphone doit être un nombre.");
        ui->lineEdit_19->setFocus();
        return;
    }

    if (telephoneT.length() != 8) {
        QMessageBox::warning(this, "Validation", "Le téléphone doit contenir exactement 8 chiffres (exemple: 71234567).");
        ui->lineEdit_19->setFocus();
        return;
    }

    QLineEdit* emailField = this->findChild<QLineEdit*>("staffEmailLineEdit");
    if (emailField) {
        QString emailT = emailField->text().trimmed();
        if (!emailT.isEmpty() && !Staff::isValidEmail(emailT)) {
            QMessageBox::warning(this, "Validation", "Veuillez entrer une adresse email valide (exemple: nom@domaine.com).");
            emailField->setFocus();
            return;
        }
    }

    QLineEdit* passwordField = this->findChild<QLineEdit*>("staffMotDePasseLineEdit");
    if (passwordField) {
        QString motDePasseT = passwordField->text().trimmed();
        if (!motDePasseT.isEmpty() && motDePasseT.length() < 6) {
            QMessageBox::warning(this, "Validation", "Le mot de passe doit contenir au moins 6 caractères.");
            passwordField->setFocus();
            return;
        }
    }

    if (!m_staffEditMode) {
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT COUNT(1) FROM ABIR.EMPLOYE WHERE ID_EMPLOYE = :id");
        checkQuery.bindValue(":id", idT.toInt());

        if (checkQuery.exec() && checkQuery.next()) {
            if (checkQuery.value(0).toInt() > 0) {
                QMessageBox::warning(this, "Doublon", "ID_EMPLOYE existe déjà dans la base de données.");
                ui->lineEdit_13->setFocus();
                return;
            }
        }
    }

    Staff s = readStaffForm();

    if (!m_staffEditMode) {
        if (s.ajouter()) {
            QMessageBox::information(this, "Succès", "Employé ajouté avec succès.");
            clearStaffForm();
            refreshStaffGrid();
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout de l'employé. Vérifiez les logs.");
        }
    } else {
        if (s.modifier()) {
            QMessageBox::information(this, "Succès", "Employé modifié avec succès.");
            setStaffFormMode(false);
            refreshStaffGrid();
            mettreAJourStatistiques();
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la modification de l'employé. Vérifiez les logs.");
        }
    }
}

void MainWindow::on_toolButton_23_clicked()
{
    refreshStaffGrid();
    mettreAJourStatistiques();
}

void MainWindow::on_toolButton_25_clicked()
{
    int currentRow = ui->tableWidget_3->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Suppression", "Sélectionne une ligne dans le tableau pour supprimer un employé.");
        return;
    }

    QTableWidgetItem* idItem = ui->tableWidget_3->item(currentRow, 1);
    if (!idItem) {
        QMessageBox::warning(this, "Suppression", "Impossible de récupérer l'ID_EMPLOYE de la ligne sélectionnée.");
        return;
    }

    const QString id = idItem->text();

    if (QMessageBox::question(this, "Confirmer",
                              QString("Supprimer l'employé %1 ?").arg(id),
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    Staff staff;
    if (staff.supprimer(id)) {
        QMessageBox::information(this, "Succès", QString("Employé %1 supprimé avec succès.").arg(id));
        refreshStaffGrid();
        mettreAJourStatistiques();
    } else {
        QMessageBox::critical(this, "Erreur", QString("Erreur lors de la suppression de l'employé %1.\nL'employé n'existe peut-être pas.").arg(id));
    }
}

void MainWindow::on_toolButton_26_clicked()
{
    int currentRow = ui->tableWidget_3->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Édition", "Sélectionne une ligne dans le tableau pour éditer un employé.");
        return;
    }

    populateStaffFormFromRow(currentRow);
    setStaffFormMode(true);
}

void MainWindow::on_staffCancelForm_clicked()
{
    setStaffFormMode(false);
    clearStaffForm();
}

void MainWindow::rechercherStaff()
{
    QString recherche = ui->lineEdit_21->text().trimmed();

    if (recherche.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez entrer un ID ou un nom d'employé à rechercher.");
        ui->lineEdit_21->setFocus();
        return;
    }

    QSqlQueryModel* model = nullptr;
    bool rechercheParId = false;

    if (recherche.toInt() > 0 && recherche.length() == 8) {
        model = Staff::chercherParId(recherche);
        rechercheParId = true;
    } else {
        model = Staff::rechercherParNom(recherche);
        rechercheParId = false;
    }

    if (!model) {
        QMessageBox::warning(this, "Recherche", "Erreur lors de la recherche.");
        return;
    }

    if (model->rowCount() == 0) {
        if (rechercheParId) {
            QMessageBox::information(this, "Recherche",
                                     QString("Aucun employé trouvé avec l'ID \"%1\".").arg(recherche));
        } else {
            QMessageBox::information(this, "Recherche",
                                     QString("Aucun employé trouvé avec le nom \"%1\".").arg(recherche));
        }
        delete model;
        return;
    }

    ui->tableWidget_3->setRowCount(0);

    for (int i = 0; i < model->rowCount(); ++i) {
        ui->tableWidget_3->insertRow(i);
        ui->tableWidget_3->setItem(i, 1, new QTableWidgetItem(model->data(model->index(i, 0)).toString()));
        ui->tableWidget_3->setItem(i, 2, new QTableWidgetItem(model->data(model->index(i, 1)).toString()));
        ui->tableWidget_3->setItem(i, 3, new QTableWidgetItem(model->data(model->index(i, 2)).toString()));
        ui->tableWidget_3->setItem(i, 4, new QTableWidgetItem(model->data(model->index(i, 3)).toString()));
        ui->tableWidget_3->setItem(i, 5, new QTableWidgetItem(model->data(model->index(i, 4)).toString()));
        ui->tableWidget_3->setItem(i, 6, new QTableWidgetItem(model->data(model->index(i, 5)).toString()));
        ui->tableWidget_3->setItem(i, 7, new QTableWidgetItem(model->data(model->index(i, 6)).toString()));
        ui->tableWidget_3->setItem(i, 8, new QTableWidgetItem(model->data(model->index(i, 7)).toString()));
        addStaffEditPenForRow(i);
    }

    if (rechercheParId) {
        QMessageBox::information(this, "Recherche",
                                 QString("Employé trouvé avec l'ID \"%1\".").arg(recherche));
    } else {
        QMessageBox::information(this, "Recherche",
                                 QString("Employé trouvé avec le nom \"%1\".").arg(recherche));
    }

    delete model;
}

void MainWindow::initializeStaffSortComboBox()
{
    if (ui->comboBox) {
        ui->comboBox->clear();
        ui->comboBox->addItem("Par défaut");
        ui->comboBox->addItem("Nom");
        ui->comboBox->addItem("Prénom");
        ui->comboBox->addItem("Poste");
        ui->comboBox->addItem("Compétence");

        qDebug() << "[initializeStaffSortComboBox] Sort comboBox initialized with options";
    } else {
        qDebug() << "[initializeStaffSortComboBox] comboBox not found for staff sorting";
    }
}

void MainWindow::on_comboBox_currentTextChanged(const QString &text)
{
    if (text == "Par défaut" || text.isEmpty()) {
        refreshStaffGrid();
    } else {
        Staff staff;
        QSqlQueryModel* model = staff.afficherTrié(text);

        if (!model) return;

        ui->tableWidget_3->setRowCount(0);

        for (int i = 0; i < model->rowCount(); ++i) {
            ui->tableWidget_3->insertRow(i);
            ui->tableWidget_3->setItem(i, 1, new QTableWidgetItem(model->data(model->index(i, 0)).toString()));
            ui->tableWidget_3->setItem(i, 2, new QTableWidgetItem(model->data(model->index(i, 1)).toString()));
            ui->tableWidget_3->setItem(i, 3, new QTableWidgetItem(model->data(model->index(i, 2)).toString()));
            ui->tableWidget_3->setItem(i, 4, new QTableWidgetItem(model->data(model->index(i, 3)).toString()));
            ui->tableWidget_3->setItem(i, 5, new QTableWidgetItem(model->data(model->index(i, 4)).toString()));
            ui->tableWidget_3->setItem(i, 6, new QTableWidgetItem(model->data(model->index(i, 5)).toString()));
            ui->tableWidget_3->setItem(i, 7, new QTableWidgetItem(model->data(model->index(i, 6)).toString()));
            ui->tableWidget_3->setItem(i, 8, new QTableWidgetItem(model->data(model->index(i, 7)).toString()));
            addStaffEditPenForRow(i);
        }

        delete model;
    }
}

void MainWindow::on_pdf_clicked()
{
    ui->pdf->setEnabled(false);
    exporterTableWidgetVersPDF();
    QTimer::singleShot(500, this, [this]() {
        ui->pdf->setEnabled(true);
    });
}

void MainWindow::exporterTableWidgetVersPDF()
{
    Staff staff;
    QSqlQueryModel* model = staff.afficher();

    if (!model || model->rowCount() == 0) {
        QMessageBox::warning(this, "Aucune donnée", "Aucun employé trouvé dans la base de données !");
        if (model) delete model;
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Exporter les employés",
        QDir::homePath() + "/employes.pdf",
        "Fichiers PDF (*.pdf)"
        );

    if (fileName.isEmpty()) {
        delete model;
        return;
    }

    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive))
        fileName += ".pdf";

    QString dateExport = QDateTime::currentDateTime().toString("dd/MM/yyyy - HH:mm:ss");

    QString html;
    html += "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Employés</title><style>";

    html += "body{font-family:Arial; margin:20px; background:#F8D7E3;}";
    html += "h1{color:#5A3E7A;text-align:center;}";

    html += "table{border-collapse:collapse;width:100%; background:#FFFFFF; font-size:11px;}";

    html += "th{background:#DCC7F8;color:#5A3E7A;padding:6px; font-size:11px;}";
    html += "td{border:1px solid #ccc;padding:5px;color:#5A3E7A; font-size:10px;}";

    html += "tr:nth-child(even){background:#F2F2F2;}";
    html += "tr:nth-child(odd){background:#F8D7E3;}";

    html += "th:nth-child(1), td:nth-child(1){ width:40px;}";
    html += "th:nth-child(2), td:nth-child(2){ width:90px;}";
    html += "th:nth-child(3), td:nth-child(3){ width:90px;}";
    html += "th:nth-child(4), td:nth-child(4){ width:80px;}";
    html += "th:nth-child(5), td:nth-child(5){ width:100px;}";
    html += "th:nth-child(6), td:nth-child(6){ width:80px;}";
    html += "th:nth-child(7), td:nth-child(7){ width:130px;}";
    html += "th:nth-child(8), td:nth-child(8){ width:60px; text-align:center;}";

    html += "</style></head><body>";

    html += "<h1>LISTE DES EMPLOYÉS</h1>";
    html += "<h3>Généré le : " + dateExport + "</h3>";
    html += "<h4>Total des employés : " + QString::number(model->rowCount()) + "</h4>";

    html += "<table>";
    html += "<tr><th>ID</th><th>NOM</th><th>PRENOM</th><th>POSTE</th>";
    html += "<th>COMPÉTENCE</th><th>TÉLÉPHONE</th><th>EMAIL</th><th>MOT DE PASSE</th></tr>";

    for (int row = 0; row < model->rowCount(); ++row) {
        html += "<tr>";

        QString id = model->data(model->index(row, 0)).toString();
        html += "<td>" + id + "</td>";

        QString nom = model->data(model->index(row, 1)).toString();
        html += "<td>" + nom + "</td>";

        QString prenom = model->data(model->index(row, 2)).toString();
        html += "<td>" + prenom + "</td>";

        QString poste = model->data(model->index(row, 3)).toString();
        html += "<td>" + poste + "</td>";

        QString competence = model->data(model->index(row, 4)).toString();
        html += "<td>" + competence + "</td>";

        QString telephone = model->data(model->index(row, 5)).toString();
        html += "<td>" + telephone + "</td>";

        QString email = model->data(model->index(row, 6)).toString();
        html += "<td>" + email + "</td>";

        QString motDePasse = model->data(model->index(row, 7)).toString();
        html += "<td>" + (!motDePasse.isEmpty() ? QString("••••••••") : QString("")) + "</td>";

        html += "</tr>";
    }

    html += "</table></body></html>";

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(96);

    QPainter painter(&pdfWriter);

    QTextDocument doc;
    doc.setHtml(html);
    doc.drawContents(&painter);

    painter.end();

    delete model;

    QMessageBox::information(this, "Succès", "PDF généré avec succès depuis la base de données !");
}

QMap<QString, int> MainWindow::compterEmployesParPoste()
{
    QMap<QString, int> statistiques;

    for (int row = 0; row < ui->tableWidget_3->rowCount(); ++row) {
        QTableWidgetItem *posteItem = ui->tableWidget_3->item(row, 4);
        if (posteItem) {
            QString poste = posteItem->text().trimmed();
            if (!poste.isEmpty()) {
                statistiques[poste]++;
            }
        }
    }

    return statistiques;
}

void MainWindow::afficherStatistiquesDansGroupBox()
{
    QLayout *layout = ui->groupBox_3->layout();
    if (layout) {
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                delete item->widget();
            }
            delete item;
        }
    } else {
        layout = new QVBoxLayout(ui->groupBox_3);
        ui->groupBox_3->setLayout(layout);
    }

    if (ui->tableWidget_3->rowCount() == 0) {
        QLabel *emptyLabel = new QLabel("Aucun employé à afficher");
        emptyLabel->setAlignment(Qt::AlignCenter);
        emptyLabel->setStyleSheet("color: #7f8c8d; font-style: italic; padding: 20px;");
        layout->addWidget(emptyLabel);
        return;
    }

    QMap<QString, int> stats = compterEmployesParPoste();

    if (stats.isEmpty()) {
        QLabel *noDataLabel = new QLabel("Aucune donnée de poste");
        noDataLabel->setAlignment(Qt::AlignCenter);
        noDataLabel->setStyleSheet("color: #7f8c8d; font-style: italic; padding: 20px;");
        layout->addWidget(noDataLabel);
        return;
    }

    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(layout);
    if (!mainLayout) {
        mainLayout = new QVBoxLayout(ui->groupBox_3);
        ui->groupBox_3->setLayout(mainLayout);
    }

    QLabel *titleLabel = new QLabel("📊 Statistiques par Poste");
    titleLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #2c3e50; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    int totalEmployes = ui->tableWidget_3->rowCount();
    QLabel *infoLabel = new QLabel(QString("Total: %1 employés | %2 postes")
                                       .arg(totalEmployes)
                                       .arg(stats.size()));
    infoLabel->setStyleSheet("color: #7f8c8d; font-size: 11px; margin-bottom: 15px;");
    infoLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(infoLabel);

    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("color: #bdc3c7; margin: 5px 0px;");
    mainLayout->addWidget(line);

    QList<QPair<QString, int>> sortedStats;
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        sortedStats.append(qMakePair(it.key(), it.value()));
    }

    std::sort(sortedStats.begin(), sortedStats.end(),
              [](const QPair<QString, int> &a, const QPair<QString, int> &b) {
                  return a.second > b.second;
              });

    QStringList colors = {"#3498db", "#2ecc71", "#e74c3c", "#f39c12", "#9b59b6",
                          "#1abc9c", "#d35400", "#34495e", "#7f8c8d"};

    int colorIndex = 0;
    for (const auto &stat : sortedStats) {
        QString poste = stat.first;
        int count = stat.second;
        double percentage = (count * 100.0) / totalEmployes;

        QWidget *posteWidget = new QWidget();
        QHBoxLayout *posteLayout = new QHBoxLayout(posteWidget);
        posteLayout->setContentsMargins(5, 2, 5, 2);

        QLabel *posteLabel = new QLabel(poste);
        posteLabel->setStyleSheet("font-weight: bold; color: #2c3e50; min-width: 100px;");
        posteLayout->addWidget(posteLabel);

        QProgressBar *progressBar = new QProgressBar();
        progressBar->setValue(static_cast<int>(percentage));
        progressBar->setMaximumWidth(120);
        progressBar->setTextVisible(false);
        progressBar->setStyleSheet(QString(
                                       "QProgressBar {"
                                       "    border: 1px solid #bdc3c7;"
                                       "    border-radius: 3px;"
                                       "    background: #ecf0f1;"
                                       "    height: 12px;"
                                       "}"
                                       "QProgressBar::chunk {"
                                       "    background: %1;"
                                       "    border-radius: 2px;"
                                       "}"
                                       ).arg(colors[colorIndex % colors.size()]));
        posteLayout->addWidget(progressBar);

        QLabel *statsLabel = new QLabel(QString("%1 (%2%)").arg(count).arg(percentage, 0, 'f', 1));
        statsLabel->setStyleSheet("color: #7f8c8d; font-size: 10px; min-width: 45px;");
        statsLabel->setAlignment(Qt::AlignRight);
        posteLayout->addWidget(statsLabel);

        mainLayout->addWidget(posteWidget);
        colorIndex++;
    }

    mainLayout->addStretch();

    QPushButton *refreshButton = new QPushButton("🔄 Actualiser");
    refreshButton->setStyleSheet(
        "QPushButton {"
        "    background: #3498db;"
        "    color: white;"
        "    border: none;"
        "    padding: 6px;"
        "    border-radius: 4px;"
        "    font-size: 11px;"
        "}"
        "QPushButton:hover {"
        "    background: #2980b9;"
        "}"
        );
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::mettreAJourStatistiques);
    mainLayout->addWidget(refreshButton);
}

void MainWindow::mettreAJourStatistiques()
{
    afficherStatistiquesDansGroupBox();
}

QMap<QString, int> MainWindow::compterEmployesParCompetence()
{
    QMap<QString, int> statistiques;

    for (int row = 0; row < ui->tableWidget_3->rowCount(); ++row) {
        QTableWidgetItem *competenceItem = ui->tableWidget_3->item(row, 5);
        if (competenceItem) {
            QString competence = competenceItem->text().trimmed();
            if (!competence.isEmpty()) {
                if (competence.contains("Débutant", Qt::CaseInsensitive) ||
                    competence.contains("debutant", Qt::CaseInsensitive)) {
                    statistiques["Débutant"]++;
                } else if (competence.contains("Intermédiaire", Qt::CaseInsensitive) ||
                           competence.contains("intermediaire", Qt::CaseInsensitive)) {
                    statistiques["Intermédiaire"]++;
                } else if (competence.contains("Avancé", Qt::CaseInsensitive) ||
                           competence.contains("avance", Qt::CaseInsensitive)) {
                    statistiques["Avancé"]++;
                } else {
                    statistiques[competence]++;
                }
            }
        }
    }

    return statistiques;
}

void MainWindow::afficherStatistiquesCompetencesDansGroupBox4()
{
    qDebug() << "=== DÉBUT AFFICHAGE STATS COMPÉTENCES PROFESSIONNEL ===";

    if (ui->groupBox_4->layout()) {
        QLayout* layout = ui->groupBox_4->layout();
        while (QLayoutItem* item = layout->takeAt(0)) {
            if (QWidget* widget = item->widget()) {
                widget->hide();
                widget->deleteLater();
            }
            delete item;
        }
    } else {
        new QVBoxLayout(ui->groupBox_4);
    }

    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(ui->groupBox_4->layout());
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(15, 15, 15, 15);

    QLabel *mainTitleLabel = new QLabel("📊 Statistiques des Compétences");
    mainTitleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #9B59B6; margin-bottom: 5px;");
    mainTitleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(mainTitleLabel);

    QMap<QString, int> stats = compterEmployesParCompetence();
    int totalEmployes = ui->tableWidget_3->rowCount();

    if (stats.isEmpty() || totalEmployes == 0) {
        QLabel *emptyLabel = new QLabel("Aucune donnée disponible");
        emptyLabel->setStyleSheet("color: #BDC3C7; font-style: italic; padding: 40px;");
        emptyLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(emptyLabel);
        return;
    }

    QWidget *chartContainer = new QWidget();
    QHBoxLayout *chartLayout = new QHBoxLayout(chartContainer);
    chartLayout->setSpacing(20);

    PieChartWidget *pieChart = new PieChartWidget();
    pieChart->setData(stats, totalEmployes);
    pieChart->setFixedSize(220, 220);
    chartLayout->addWidget(pieChart, 0, Qt::AlignCenter);

    QWidget *legendWidget = new QWidget();
    QVBoxLayout *legendLayout = new QVBoxLayout(legendWidget);
    legendLayout->setSpacing(8);

    QMap<QString, QString> colors;
    colors["Débutant"] = "#3498db";       // bleu
    colors["Intermédiaire"] = "#f39c12";  // orange
    colors["Avancé"] = "#9b59b6";         // violet

    QStringList competencesOrder = {"Débutant", "Intermédiaire", "Avancé"};

    for (const QString &competence : competencesOrder) {
        if (stats.contains(competence)) {
            int count = stats[competence];
            double percentage = (count * 100.0) / totalEmployes;

            QWidget *legendItem = new QWidget();
            QHBoxLayout *itemLayout = new QHBoxLayout(legendItem);
            itemLayout->setContentsMargins(5, 2, 5, 2);

            QLabel *colorDot = new QLabel();
            colorDot->setFixedSize(14, 14);
            QString c = colors.value(competence, "#3498db");
            colorDot->setStyleSheet(QString(
                                        "background: %1;"
                                        "border-radius: 7px;"
                                        "border: 2px solid %1;"
                                        ).arg(c));

            QLabel *textLabel = new QLabel(
                QString("%1: %2 (%3%)").arg(competence).arg(count).arg(percentage, 0, 'f', 1)
                );
            textLabel->setStyleSheet("font-weight: 600; color: #2c3e50; font-size: 11px;");

            itemLayout->addWidget(colorDot);
            itemLayout->addWidget(textLabel);
            itemLayout->addStretch();

            legendLayout->addWidget(legendItem);
        }
    }

    chartLayout->addWidget(legendWidget);
    mainLayout->addWidget(chartContainer);

    mainLayout->addStretch();

    qDebug() << "=== FIN AFFICHAGE STATS COMPÉTENCES PROFESSIONNEL ===";
}

// ===================================================
//  PIE CHART WIDGET - IMPLÉMENTATION
// ===================================================
PieChartWidget::PieChartWidget(QWidget *parent)
    : QWidget(parent), m_total(0)
{
    // Palette harmonisée avec l'interface
    QStringList palette = {"#3498db", "#2ecc71", "#e74c3c", "#f39c12", "#9b59b6", "#1abc9c", "#d35400", "#34495e", "#7f8c8d"};

    // Assign common keys to friendly interface colors
    m_colors["fonctionnel"] = QColor(palette[1]);    // vert
    m_colors["en panne"] = QColor(palette[2]);       // rouge
    m_colors["en maintenance"] = QColor(palette[3]); // orange
    m_colors["hors service"] = QColor(palette[8]);   // gris
    m_colors["caméra"] = QColor(palette[0]);         // bleu
    m_colors["micro"] = QColor(palette[4]);          // violet
    m_colors["podcast"] = QColor(palette[5]);        // teal
    m_colors["casque"] = QColor(palette[6]);         // darker orange
    m_colors["webcam"] = QColor(palette[7]);         // dark blue-grey

    // For competences, prefer strong readable colors
    m_colors["Débutant"] = QColor(palette[0]);       // bleu
    m_colors["Intermédiaire"] = QColor(palette[3]);  // orange
    m_colors["Avancé"] = QColor(palette[4]);         // violet

    setMinimumSize(120, 120);
}

void PieChartWidget::setData(const QMap<QString, int> &data, int total)
{
    m_data = data;
    m_total = total;
    update();
}

void PieChartWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    // draw when no data
    if (m_data.isEmpty()) {
        QPainter painter(this);
        painter.drawText(rect(), Qt::AlignCenter, "No data");
        return;
    }

    // compute total from data to avoid mismatch
    int sum = 0;
    for (auto v : m_data) sum += v;
    if (sum <= 0) {
        QPainter painter(this);
        painter.drawText(rect(), Qt::AlignCenter, "No data");
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const int margin = 8;
    const int size = qMin(width(), height()) - 2 * margin;
    QRectF pieRect((width() - size) / 2.0, (height() - size) / 2.0, size, size);
    if (pieRect.width() <= 0 || pieRect.height() <= 0) return;

    const QPointF center = pieRect.center();
    const double radius = pieRect.width() / 2.0;

    double startAngle = 0.0; // degrees, 0 == 3 o'clock

    // ensure we iterate deterministically over keys
    QList<QString> keys = m_data.keys();
    for (const QString &key : keys) {
        int value = m_data.value(key);
        double angle = (value * 360.0) / sum;

        QColor color = m_colors.value(key);
        if (!color.isValid()) {
            QColor colorLower = m_colors.value(key.toLower());
            if (colorLower.isValid()) color = colorLower;
        }
        if (!color.isValid()) {
            // fallback: generate a distinct color
            int hue = qAbs(qHash(key)) % 360;
            color = QColor::fromHsl(hue, 180, 140);
            m_colors.insert(key, color);
        }

        painter.setBrush(color);
        painter.setPen(QPen(Qt::white, 1));
        painter.drawPie(pieRect, int(startAngle * 16), int(angle * 16));

        // draw percentage label on slice
        double midAngle = startAngle + angle / 2.0;
        double rad = midAngle * M_PI / 180.0;
        double labelRadius = radius * 0.60;
        double lx = center.x() + std::cos(rad) * labelRadius;
        double ly = center.y() - std::sin(rad) * labelRadius;

        // Use m_total if provided, otherwise fallback to computed sum
        double base = (m_total > 0) ? m_total : sum;
        double percent = (value * 100.0) / base;
        QString percentText = QString::number(percent, 'f', percent < 10.0 ? 1 : 0) + "%";

        // choose text color with enough contrast
        int brightness = (color.red() * 299 + color.green() * 587 + color.blue() * 114) / 1000;
        QColor textColor = (brightness < 125) ? QColor(Qt::white) : QColor(Qt::black);

        painter.setPen(QPen(textColor));
        QFont f = painter.font();
        f.setPointSizeF(qMax(8.0, radius * 0.06));
        f.setBold(true);
        painter.setFont(f);

        QRectF textRect(lx - 30, ly - 10, 60, 20);
        painter.drawText(textRect, Qt::AlignCenter, percentText);

        startAngle += angle;
    }

    // Draw center text (total)
    painter.setPen(QPen(QColor("#2C3E50")));
    QFont centerFont = painter.font();
    centerFont.setPointSizeF(qMax(10.0, radius * 0.10));
    centerFont.setBold(true);
    painter.setFont(centerFont);
    QString centerText = QString::number(sum);
    painter.drawText(pieRect, Qt::AlignCenter, centerText);
}

void MainWindow::mettreAJourStatistiquesCompetences()
{
    afficherStatistiquesCompetencesDansGroupBox4();
}

// ===================================================
//                  MATERIEL
// ===================================================
void MainWindow::onTableMaterielSelectionChanged()
{
    QList<QTableWidgetSelectionRange> ranges = ui->tableWidget_4->selectedRanges();
    if (!ranges.isEmpty()) {
        int row = ranges.first().topRow();
        if (row >= 0 && row < ui->tableWidget_4->rowCount()) {
            afficherQRCodePourLigne(row);
        }
    }
}

void MainWindow::afficherQRCodePourLigne(int row)
{
    if (m_qrCodeEnCours || row == m_derniereLigneQR) {
        qDebug() << "🚫 QR Code déjà en cours ou même ligne - Ignoré";
        return;
    }

    m_qrCodeEnCours = true;
    m_derniereLigneQR = row;

    qDebug() << "🔍 Affichage QR Code pour ligne:" << row;

    if (row < 0 || row >= ui->tableWidget_4->rowCount()) {
        m_qrCodeEnCours = false;
        return;
    }

    QString qrData = getInfoMaterielPourQR(row);

    QLayout *oldLayout = ui->groupBox_15->layout();
    if (oldLayout) {
        QList<QLayoutItem*> items;
        for (int i = 0; i < oldLayout->count(); ++i) {
            items.append(oldLayout->takeAt(i));
        }

        for (QLayoutItem *item : items) {
            if (item->widget()) {
                item->widget()->deleteLater();
            }
            delete item;
        }
        delete oldLayout;
    }

    genererQRCode(qrData);

    QTimer::singleShot(500, this, [this]() {
        m_qrCodeEnCours = false;
    });
}

void MainWindow::genererQRCode(const QString &data)
{
    qDebug() << "=== GÉNÉRATION QR CODE UNIQUE ===";

    if (!ui->groupBox_15) {
        qDebug() << "❌ ERREUR: groupBox_15 n'existe pas!";
        return;
    }

    QVBoxLayout *layout = new QVBoxLayout(ui->groupBox_15);
    layout->setSpacing(5);
    layout->setContentsMargins(10, 10, 10, 10);

    QLabel *titleLabel = new QLabel("QR CODE MATÉRIEL");
    titleLabel->setStyleSheet("font-weight: bold; color: #2C3E50; font-size: 12px; text-align: center;");
    layout->addWidget(titleLabel);

    QLabel *qrLabel = new QLabel();
    qrLabel->setFixedSize(250, 250);
    qrLabel->setAlignment(Qt::AlignCenter);
    qrLabel->setStyleSheet("background: white; border: 2px solid #3498DB; border-radius: 8px;");
    qrLabel->setText("Génération...");

    QHBoxLayout *centerLayout = new QHBoxLayout();
    centerLayout->addStretch();
    centerLayout->addWidget(qrLabel);
    centerLayout->addStretch();
    layout->addLayout(centerLayout);

    QLabel *instructionsLabel = new QLabel("📱 Scannez pour voir les détails");
    instructionsLabel->setStyleSheet("color: #7F8C8D; font-size: 10px; text-align: center; margin-top: 5px;");
    layout->addWidget(instructionsLabel);

    genererQRCodeImage(qrLabel, data);
}

void MainWindow::genererQRCodeImage(QLabel *qrLabel, const QString &data)
{
    QString textePourQR = data;

    qDebug() << "📝 Texte QR exact:" << textePourQR;

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QString urlQR = "https://api.qrserver.com/v1/create-qr-code/?size=250x250&data=" +
                    QUrl::toPercentEncoding(textePourQR) + "&format=png&ecc=H&charset-source=UTF-8";

    QNetworkRequest request(urlQR);
    QNetworkReply *reply = manager->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray imageData = reply->readAll();
            QPixmap pixmap;

            if (pixmap.loadFromData(imageData, "PNG")) {
                qrLabel->setPixmap(pixmap);
                qrLabel->setText("");
                qDebug() << "✅ QR Code généré - Format exact préservé";
            } else {
                qrLabel->setText("Erreur");
            }
        } else {
            qrLabel->setText("Erreur\nRéseau");
        }

        reply->deleteLater();
        manager->deleteLater();
    });
}

QString MainWindow::getProjetUtilisateurPourQR(const QString &idMateriel)
{
    Connection* conn = Connection::getInstance();
    QSqlDatabase db = conn->getDatabase();

    if (!db.isOpen()) {
        if (!conn->openConnection()) return "❌ Erreur connexion";
    }

    qDebug() << "=== DÉBUT RECHERCHE PROJET ===";
    qDebug() << "🔍 Matériel ID:" << idMateriel;

    QSqlQuery queryMateriel(db);
    queryMateriel.prepare("SELECT NOM, TYPE FROM ABIR.MATERIEL WHERE ID_MATERIEL = :id");
    queryMateriel.bindValue(":id", idMateriel.toInt());

    QString nomMateriel = "", typeMateriel = "";

    if (queryMateriel.exec() && queryMateriel.next()) {
        nomMateriel = queryMateriel.value(0).toString();
        typeMateriel = queryMateriel.value(1).toString();
        qDebug() << "📦 Matériel trouvé - Nom:" << nomMateriel << "Type:" << typeMateriel;
    } else {
        qDebug() << "❌ Matériel non trouvé avec ID:" << idMateriel;
        return "❌ Matériel non trouvé";
    }

    QSqlQuery queryProjets(db);
    queryProjets.prepare("SELECT ID_PROJET, TYPE, TO_CHAR(DATE_D, 'DD/MM/YYYY'), TO_CHAR(DATE_F, 'DD/MM/YYYY'), MATRIEL "
                         "FROM ABIR.PROJET "
                         "WHERE UPPER(MATRIEL) LIKE UPPER('%' || :type_materiel || '%') "
                         "ORDER BY DATE_D DESC");
    queryProjets.bindValue(":type_materiel", typeMateriel);

    QStringList projetsTrouves;
    int countProjets = 0;

    if (queryProjets.exec()) {
        while (queryProjets.next() && countProjets < 3) {
            QString idProjet = queryProjets.value(0).toString();
            QString typeProjet = queryProjets.value(1).toString();
            QString dateDebut = queryProjets.value(2).toString();
            QString dateFin = queryProjets.value(3).toString();
            QString matrielNote = queryProjets.value(4).toString();

            qDebug() << "✅ Projet trouvé! ID:" << idProjet << "Matériel:" << matrielNote;

            if (countProjets == 0) {
                projetsTrouves << QString("📂 Projet: %1 (%2)\n"
                                          "🎞️ Type: %3\n"
                                          "📅 Période: %4 - %5\n"
                                          "🎛️ Matériel noté: %6")
                                      .arg(idProjet)
                                      .arg(typeProjet)
                                      .arg(typeProjet)
                                      .arg(dateDebut)
                                      .arg(dateFin)
                                      .arg(matrielNote);
            } else {
                projetsTrouves << QString("📂 Projet %1: %2 (%3)\n"
                                          "   📅 Période: %4 - %5")
                                      .arg(countProjets + 1)
                                      .arg(idProjet)
                                      .arg(typeProjet)
                                      .arg(dateDebut)
                                      .arg(dateFin);
            }
            countProjets++;
        }
    } else {
        qDebug() << "❌ Erreur requête projets:" << queryProjets.lastError().text();
    }

    if (countProjets > 0) {
        return "🎬 PROJETS ASSOCIÉS: (" + QString::number(countProjets) + " projet(s))\n" +
               projetsTrouves.join("\n\n");
    } else {
        qDebug() << "📭 Aucun projet trouvé pour le type:" << typeMateriel;
        return "🎬 PROJET ASSOCIÉ:\n📭 Aucun projet utilisant ce type de matériel\n🔓 Matériel disponible";
    }
}

void MainWindow::afficherErreurQR(QLabel *qrLabel, QVBoxLayout *layout, const QString &message)
{
    qrLabel->setText("📱 Code Matériel\n\nScannez les\ndonnées ci-dessous");
    qrLabel->setStyleSheet(
        "background: white; border: 2px solid #E74C3C; border-radius: 10px;"
        "color: #2C3E50; font-size: 12px; padding: 20px;"
        );

    QLabel *erreurLabel = new QLabel(message);
    erreurLabel->setStyleSheet("color: #E74C3C; font-size: 10px; text-align: center;");
    layout->insertWidget(1, erreurLabel);
}

void MainWindow::afficherDonneesQR(QVBoxLayout *layout, const QString &data)
{
    QLabel *labelDonnees = new QLabel("Informations encodées:");
    labelDonnees->setStyleSheet("font-weight: bold; color: #2C3E50; font-size: 12px; margin-top: 10px;");
    layout->addWidget(labelDonnees);

    QLabel *affichageDonnees = new QLabel(data);
    affichageDonnees->setStyleSheet(
        "background: #F8F9F9; padding: 10px; border-radius: 5px;"
        "border: 1px solid #BDC3C7; font-size: 10px; font-family: monospace;"
        );
    affichageDonnees->setWordWrap(true);
    affichageDonnees->setTextInteractionFlags(Qt::TextSelectableByMouse);
    layout->addWidget(affichageDonnees);
}

QString MainWindow::getInfoMaterielPourQR(int row)
{
    if (row < 0 || row >= ui->tableWidget_4->rowCount()) {
        return "Ligne non valide";
    }

    QString idMateriel = ui->tableWidget_4->item(row, 1)->text();
    QString nom = ui->tableWidget_4->item(row, 2)->text();
    QString type = ui->tableWidget_4->item(row, 3)->text();
    QString etat = ui->tableWidget_4->item(row, 4)->text();
    QString localisation = ui->tableWidget_4->item(row, 5)->text();

    QString infoProjets = getProjetUtilisateurPourQR(idMateriel);

    QString texteQR =
        "🎯 FICHE MATÉRIEL COMPLÈTE\n"
        "────────────────────\n"
        "📷 MATÉRIEL: " + nom + "\n" +
        "🔢 ID: " + idMateriel + "\n" +
        "📋 TYPE: " + type + "\n" +
        "✅ ÉTAT: " + etat + "\n" +
        "📍 LOCALISATION: " + localisation + "\n" +
        "────────────────────\n" +
        infoProjets + "\n" +
        "────────────────────\n" +
        "📅 SCANNÉ LE: " + QDate::currentDate().toString("dd/MM/yyyy") + "\n" +
        "🏷️ STUDIO PRODUCTION";

    return texteQR;
}

void MainWindow::setupTabMateriel()
{
    ui->tableWidget_4->setColumnCount(6);
    QStringList headers{ "", "ID_MATERIEL", "NOM", "TYPE", "ETAT", "LOCALISATION" };
    ui->tableWidget_4->setHorizontalHeaderLabels(headers);
    ui->tableWidget_4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_4->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_4->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_4->setColumnWidth(0, 56);

    disconnect(ui->tableWidget_4, &QTableWidget::itemSelectionChanged, nullptr, nullptr);
    disconnect(ui->tableWidget_4, &QTableWidget::cellClicked, nullptr, nullptr);

    connect(ui->tableWidget_4, &QTableWidget::itemSelectionChanged, this, [this]() {
        QList<QTableWidgetSelectionRange> ranges = ui->tableWidget_4->selectedRanges();
        if (!ranges.isEmpty()) {
            int row = ranges.first().topRow();
            if (row >= 0 && row < ui->tableWidget_4->rowCount()) {
                populateMaterielFormFromRow(row);
                setMaterielFormMode(true);
                afficherQRCodePourLigne(row);
            }
        }
    });
}

Materiel MainWindow::readMaterielForm() const
{
    QString id = ui->lineEdit_15->text().trimmed();
    QString nom = ui->lineEdit_16->text().trimmed();
    QString type = ui->equipmentComboBox->currentText();
    QString localisation = ui->lineEdit_18->text().trimmed();

    QString etat;
    if (ui->radioButton_18->isChecked()) {
        etat = "fonctionnel";
    } else if (ui->radioButton_19->isChecked()) {
        etat = "en panne";
    } else if (ui->radioButton_20->isChecked()) {
        etat = "en maintenance";
    } else if (ui->radioButton_21->isChecked()) {
        etat = "hors service";
    } else {
        etat = "";
    }

    if (ui->radioButton_22->isChecked()) {
        localisation = "studio tournage";
    } else if (ui->radioButton_23->isChecked()) {
        localisation = "salle montage";
    } else if (ui->radioButton_24->isChecked()) {
        localisation = "salle podcast";
    }

    return Materiel(id, nom, type, etat, localisation);
}

void MainWindow::clearMaterielForm()
{
    ui->lineEdit_15->clear();
    ui->lineEdit_16->clear();
    ui->equipmentComboBox->setCurrentIndex(0);
    ui->lineEdit_18->clear();

    if (m_materielEtatGroup->checkedButton()) {
        m_materielEtatGroup->setExclusive(false);
        m_materielEtatGroup->checkedButton()->setChecked(false);
        m_materielEtatGroup->setExclusive(true);
    }

    if (m_materielLocationGroup->checkedButton()) {
        m_materielLocationGroup->setExclusive(false);
        m_materielLocationGroup->checkedButton()->setChecked(false);
        m_materielLocationGroup->setExclusive(true);
    }
}

void MainWindow::populateMaterielFormFromRow(int row)
{
    if (row < 0 || row >= ui->tableWidget_4->rowCount()) return;

    QTableWidgetItem* idItem = ui->tableWidget_4->item(row, 1);
    QTableWidgetItem* nomItem = ui->tableWidget_4->item(row, 2);
    QTableWidgetItem* typeItem = ui->tableWidget_4->item(row, 3);
    QTableWidgetItem* etatItem = ui->tableWidget_4->item(row, 4);
    QTableWidgetItem* localisationItem = ui->tableWidget_4->item(row, 5);

    if (idItem) ui->lineEdit_15->setText(idItem->text());
    if (nomItem) ui->lineEdit_16->setText(nomItem->text());
    if (typeItem) {
        QString typeText = typeItem->text();
        int index = ui->equipmentComboBox->findText(typeText);
        if (index >= 0) {
            ui->equipmentComboBox->setCurrentIndex(index);
        } else {
            ui->equipmentComboBox->setCurrentIndex(0);
        }
    }

    if (etatItem) {
        QString etat = etatItem->text().toLower();
        ui->radioButton_18->setChecked(false);
        ui->radioButton_19->setChecked(false);
        ui->radioButton_20->setChecked(false);
        ui->radioButton_21->setChecked(false);

        if (etat.contains("fonctionnel")) {
            ui->radioButton_18->setChecked(true);
        } else if (etat.contains("panne")) {
            ui->radioButton_19->setChecked(true);
        } else if (etat.contains("maintenance")) {
            ui->radioButton_20->setChecked(true);
        } else if (etat.contains("hors service")) {
            ui->radioButton_21->setChecked(true);
        }
    }

    if (localisationItem) {
        QString localisation = localisationItem->text().toLower();
        ui->radioButton_22->setChecked(false);
        ui->radioButton_23->setChecked(false);
        ui->radioButton_24->setChecked(false);

        if (localisation.contains("studio tournage")) {
            ui->radioButton_22->setChecked(true);
        } else if (localisation.contains("salle montage")) {
            ui->radioButton_23->setChecked(true);
        } else if (localisation.contains("salle podcast")) {
            ui->radioButton_24->setChecked(true);
        } else {
            ui->lineEdit_18->setText(localisationItem->text());
        }
    }
}

void MainWindow::setMaterielFormMode(bool edit)
{
    m_materielEditMode = edit;
    if (edit) {
        ui->toolButton_31->setText("Modifier");
        ui->lineEdit_15->setEnabled(false);
    } else {
        ui->toolButton_31->setText("Ajouter");
        ui->lineEdit_15->setEnabled(true);
        clearMaterielForm();
    }
}

void MainWindow::addMaterielEditPenForRow(int row)
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
        QPoint p = cell->mapTo(ui->tableWidget_4->viewport(), QPoint(2,2));
        int row = ui->tableWidget_4->indexAt(p).row();
        if (row < 0) return;
        populateMaterielFormFromRow(row);
        setMaterielFormMode(true);
    });

    auto *cell = new QWidget;
    auto *lay  = new QHBoxLayout(cell);
    lay->setContentsMargins(2,0,2,0);
    lay->setAlignment(Qt::AlignCenter);
    lay->addWidget(editBtn);
    ui->tableWidget_4->setCellWidget(row, 0, cell);
}

QMap<QString, int> MainWindow::compterMaterielParEtat()
{
    QMap<QString, int> statistiques;

    for (int row = 0; row < ui->tableWidget_4->rowCount(); ++row) {
        QTableWidgetItem *etatItem = ui->tableWidget_4->item(row, 4);
        if (etatItem) {
            QString etat = etatItem->text().trimmed().toLower();
            if (!etat.isEmpty()) {
                if (etat.contains("fonctionnel")) {
                    statistiques["Fonctionnel"]++;
                } else if (etat.contains("panne")) {
                    statistiques["En panne"]++;
                } else if (etat.contains("maintenance")) {
                    statistiques["En maintenance"]++;
                } else if (etat.contains("hors service")) {
                    statistiques["Hors service"]++;
                } else {
                    statistiques[etat]++;
                }
            }
        }
    }
    return statistiques;
}

QMap<QString, int> MainWindow::compterMaterielParType()
{
    QMap<QString, int> statistiques;

    for (int row = 0; row < ui->tableWidget_4->rowCount(); ++row) {
        QTableWidgetItem *typeItem = ui->tableWidget_4->item(row, 3);
        if (typeItem) {
            QString type = typeItem->text().trimmed().toLower();
            if (!type.isEmpty()) {
                if (type.contains("caméra") || type.contains("camera")) {
                    statistiques["Caméra"]++;
                } else if (type.contains("micro")) {
                    statistiques["Micro"]++;
                } else if (type.contains("podcast")) {
                    statistiques["Podcast"]++;
                } else if (type.contains("casque")) {
                    statistiques["Casque"]++;
                } else if (type.contains("webcam")) {
                    statistiques["Webcam"]++;
                } else {
                    statistiques[type]++;
                }
            }
        }
    }
    return statistiques;
}

void MainWindow::afficherStatistiquesMateriel()
{
    QMap<QString, int> statsEtat = compterMaterielParEtat();
    QMap<QString, int> statsType = compterMaterielParType();
    int totalMateriel = ui->tableWidget_4->rowCount();

    afficherPieChartDansGroupBox(ui->groupBox_11, statsType, totalMateriel, "TYPES DE MATÉRIEL");
    afficherPieChartDansGroupBox(ui->groupBox_14, statsEtat, totalMateriel, "ÉTAT DU MATÉRIEL");
}

void MainWindow::afficherPieChartDansGroupBox(QGroupBox *groupBox, const QMap<QString, int> &stats, int total, const QString &title)
{
    if (groupBox->layout()) {
        QLayout* layout = groupBox->layout();
        while (QLayoutItem* item = layout->takeAt(0)) {
            if (QWidget* widget = item->widget()) {
                widget->hide();
                widget->deleteLater();
            }
            delete item;
        }
    } else {
        new QVBoxLayout(groupBox);
    }

    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(groupBox->layout());
    layout->setSpacing(8);
    layout->setContentsMargins(8, 8, 8, 8);

    if (total == 0) {
        QLabel *emptyLabel = new QLabel("Aucune donnée");
        emptyLabel->setStyleSheet("color: #BDC3C7; font-style: italic; padding: 20px;");
        emptyLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(emptyLabel);
        return;
    }

    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("font-weight: bold; color: #2C3E50; font-size: 11px; text-align: center;");
    layout->addWidget(titleLabel);

    PieChartWidget *pieChart = new PieChartWidget();
    pieChart->setData(stats, total);
    pieChart->setFixedSize(160, 160);
    layout->addWidget(pieChart, 0, Qt::AlignCenter);

    ajouterLegendeSimple(layout, stats, total);

    layout->addStretch();
}

void MainWindow::ajouterLegendeSimple(QVBoxLayout *layout, const QMap<QString, int> &stats, int total)
{
    QMap<QString, QString> colors;
    colors["fonctionnel"] = "#2ecc71";      // vert
    colors["en panne"] = "#e74c3c";         // rouge
    colors["en maintenance"] = "#f39c12";   // orange
    colors["hors service"] = "#7f8c8d";     // gris
    colors["caméra"] = "#3498db";           // bleu
    colors["micro"] = "#9b59b6";            // violet
    colors["podcast"] = "#1abc9c";          // teal
    colors["casque"] = "#d35400";           // dark orange
    colors["webcam"] = "#34495e";           // dark blue-grey

    for (auto it = stats.begin(); it != stats.end(); ++it) {
        QString key = it.key();
        int count = it.value();
        double percentage = (count * 100.0) / total;

        QWidget *legendItem = new QWidget();
        QHBoxLayout *itemLayout = new QHBoxLayout(legendItem);
        itemLayout->setContentsMargins(2, 1, 2, 1);

        QLabel *colorDot = new QLabel();
        colorDot->setFixedSize(8, 8);
        QString color = colors.value(key.toLower(), "#3498DB");
        colorDot->setStyleSheet(QString("background: %1; border-radius: 4px;").arg(color));

        QLabel *textLabel = new QLabel(
            QString("%1: %2 (%3%)").arg(key).arg(count).arg(percentage, 0, 'f', 0)
            );
        textLabel->setStyleSheet("color: #2C3E50; font-size: 8px;");

        itemLayout->addWidget(colorDot);
        itemLayout->addWidget(textLabel);
        itemLayout->addStretch();

        layout->addWidget(legendItem);
    }
}

void MainWindow::ajouterLegendeMateriel(QHBoxLayout *mainLayout,
                                        const QMap<QString, int> &statsEtat,
                                        const QMap<QString, int> &statsType)
{
    QWidget *legendContainer = new QWidget();
    QVBoxLayout *legendLayout = new QVBoxLayout(legendContainer);
    legendLayout->setSpacing(15);

    QLabel *legendEtatTitle = new QLabel("📊 LÉGENDE - ÉTATS");
    legendEtatTitle->setStyleSheet("font-weight: bold; color: #2C3E50; font-size: 12px;");
    legendLayout->addWidget(legendEtatTitle);

    ajouterItemsLegende(legendLayout, statsEtat, ui->tableWidget_4->rowCount());

    QFrame *separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    separator->setStyleSheet("color: #BDC3C7;");
    legendLayout->addWidget(separator);

    QLabel *legendTypeTitle = new QLabel("🎛️ LÉGENDE - TYPES");
    legendTypeTitle->setStyleSheet("font-weight: bold; color: #2C3E50; font-size: 12px;");
    legendLayout->addWidget(legendTypeTitle);

    ajouterItemsLegende(legendLayout, statsType, ui->tableWidget_4->rowCount());

    mainLayout->addWidget(legendContainer);
}

void MainWindow::ajouterItemsLegende(QVBoxLayout *layout,
                                     const QMap<QString, int> &stats,
                                     int total)
{
    QMap<QString, QString> colors;
    colors["fonctionnel"] = "#2ecc71";      // vert
    colors["en panne"] = "#e74c3c";         // rouge
    colors["en maintenance"] = "#f39c12";   // orange
    colors["hors service"] = "#7f8c8d";     // gris
    colors["caméra"] = "#3498db";           // bleu
    colors["micro"] = "#9b59b6";            // violet
    colors["podcast"] = "#1abc9c";          // teal
    colors["casque"] = "#d35400";           // dark orange
    colors["webcam"] = "#34495e";           // dark blue-grey

    for (auto it = stats.begin(); it != stats.end(); ++it) {
        QString key = it.key();
        int count = it.value();
        double percentage = (count * 100.0) / total;

        QWidget *legendItem = new QWidget();
        QHBoxLayout *itemLayout = new QHBoxLayout(legendItem);
        itemLayout->setContentsMargins(5, 3, 5, 3);

        QLabel *colorDot = new QLabel();
        colorDot->setFixedSize(12, 12);
        QString color = colors.value(key.toLower(), "#3498DB");
        colorDot->setStyleSheet(QString(
                                    "background: %1;"
                                    "border-radius: 6px;"
                                    "border: 1px solid %1;"
                                    ).arg(color));

        QLabel *textLabel = new QLabel(
            QString("%1: %2 (%3%)").arg(key).arg(count).arg(percentage, 0, 'f', 1)
            );
        textLabel->setStyleSheet("font-weight: 600; color: #2C3E50; font-size: 10px;");

        itemLayout->addWidget(colorDot);
        itemLayout->addWidget(textLabel);
        itemLayout->addStretch();

        layout->addWidget(legendItem);
    }
}

void MainWindow::refreshMaterielGrid()
{
    ui->tableWidget_4->setRowCount(0);

    Materiel materiel;
    materiel.afficher(ui->tableWidget_4);

    for (int i = 0; i < ui->tableWidget_4->rowCount(); ++i) {
        addMaterielEditPenForRow(i);
    }

    afficherStatistiquesMateriel();

    if (ui->tableWidget_4->rowCount() > 0) {
        ui->tableWidget_4->selectRow(0);
        afficherQRCodePourLigne(0);
    }
}

void MainWindow::on_toolButton_31_clicked()
{
    const QString idT = ui->lineEdit_15->text().trimmed();
    const QString nomT = ui->lineEdit_16->text().trimmed();
    const QString typeT = ui->equipmentComboBox->currentText().trimmed();

    bool etatSelected = ui->radioButton_18->isChecked() ||
                        ui->radioButton_19->isChecked() ||
                        ui->radioButton_20->isChecked() ||
                        ui->radioButton_21->isChecked();

    bool localisationSelected = ui->radioButton_22->isChecked() ||
                                ui->radioButton_23->isChecked() ||
                                ui->radioButton_24->isChecked() ||
                                !ui->lineEdit_18->text().trimmed().isEmpty();

    static const QRegularExpression reInt(R"(^\d+$)");
    static const QRegularExpression reText(R"(^[a-zA-ZÀ-ÿ\s'-]+$)");

    if (idT.isEmpty() || nomT.isEmpty() || typeT.isEmpty() || !etatSelected || !localisationSelected) {
        QMessageBox::warning(this, "Validation", "Tous les champs sont obligatoires.");
        return;
    }

    if (!reInt.match(idT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "ID_MATERIEL doit être un nombre.");
        ui->lineEdit_15->setFocus();
        return;
    }

    if (idT.length() != 3) {
        QMessageBox::warning(this, "Validation", "ID_MATERIEL doit contenir exactement 3 chiffres (exemple: 123).");
        ui->lineEdit_15->setFocus();
        return;
    }

    if (!reText.match(nomT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le nom doit contenir uniquement des lettres.");
        ui->lineEdit_16->setFocus();
        return;
    }

    if (!reText.match(typeT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le type doit contenir uniquement des lettres.");
        ui->equipmentComboBox->setFocus();
        return;
    }

    if (!m_materielEditMode) {
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT COUNT(1) FROM ABIR.MATERIEL WHERE ID_MATERIEL = :id");
        checkQuery.bindValue(":id", idT.toInt());

        if (checkQuery.exec() && checkQuery.next()) {
            if (checkQuery.value(0).toInt() > 0) {
                QMessageBox::warning(this, "Doublon", "ID_MATERIEL existe déjà dans la base de données.");
                ui->lineEdit_15->setFocus();
                return;
            }
        }
    }

    Materiel m = readMaterielForm();

    if (!m_materielEditMode) {
        if (m.ajouter()) {
            clearMaterielForm();
            refreshMaterielGrid();
            afficherStatistiquesMateriel();
        }
    } else {
        if (m.modifier(m.getId(), m.getNom(), m.getType(), m.getEtat(), m.getLocalisation())) {
            setMaterielFormMode(false);
            refreshMaterielGrid();
            afficherStatistiquesMateriel();
        }
    }
}

void MainWindow::on_toolButton_33_clicked()
{
    refreshMaterielGrid();
    afficherStatistiquesMateriel();
}

void MainWindow::on_toolButton_35_clicked()
{
    int currentRow = ui->tableWidget_4->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Suppression", "Sélectionne une ligne dans le tableau pour supprimer un matériel.");
        return;
    }

    QTableWidgetItem* idItem = ui->tableWidget_4->item(currentRow, 1);
    if (!idItem) {
        QMessageBox::warning(this, "Suppression", "Impossible de récupérer l'ID_MATERIEL de la ligne sélectionnée.");
        return;
    }

    const QString id = idItem->text();

    if (QMessageBox::question(this, "Confirmer",
                              QString("Supprimer le matériel %1 ?").arg(id),
                              QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes) {
        return;
    }

    Materiel materiel;
    if (materiel.supprimer(id)) {
        refreshMaterielGrid();
        afficherStatistiquesMateriel();
    }
}

void MainWindow::on_toolButton_36_clicked()
{
    QString search = ui->lineEdit_18->text().trimmed();

    if (search.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez saisir un ID ou un Nom.");
        return;
    }

    Materiel materiel;

    bool isNumber = false;
    search.toInt(&isNumber);

    if (isNumber) {
        materiel.chercherParId(ui->tableWidget_4, search);
    } else {
        materiel.chercherParNom(ui->tableWidget_4, search);
    }
}

void MainWindow::on_comboBox_4_currentTextChanged(const QString &text)
{
    if (text.isEmpty()) return;

    Materiel materiel;
    materiel.afficherTrié(ui->tableWidget_4, text);
}

void MainWindow::on_toolButton_34_clicked()
{
    clearMaterielForm();
    setMaterielFormMode(false);
}

void MainWindow::on_toolButton_68_clicked()
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

    html += "<h2>Liste du matériel exportée</h2>";
    html += "<p>Date d'exportation : " + QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss") + "</p>";
    html += "<table><tr><th>ID</th><th>Nom</th><th>Type</th><th>État</th><th>Localisation</th></tr>";

    Connection* conn = Connection::getInstance();
    QSqlDatabase db = conn->getDatabase();

    if (!db.isOpen()) {
        if (!conn->openConnection()) return;
    }

    QSqlQuery query(db);
    QString queryStr = "SELECT id_materiel, nom, type, etat, localisation FROM materiel";

    if (!query.exec(queryStr)) {
        QMessageBox::warning(this, "Erreur", "Échec de lecture dans la base : " + query.lastError().text());
        return;
    }

    bool hasData = false;
    while (query.next()) {
        hasData = true;
        html += "<tr>";
        html += "<td>" + query.value(0).toString() + "</td>";
        html += "<td>" + query.value(1).toString() + "</td>";
        html += "<td>" + query.value(2).toString() + "</td>";
        html += "<td>" + query.value(3).toString() + "</td>";
        html += "<td>" + query.value(4).toString() + "</td>";
        html += "</tr>";
    }

    if (!hasData) {
        QMessageBox::information(this, "Exportation", "Aucun élément à exporter (la base est vide).");
        return;
    }

    html += "</table></body></html>";

    QTextDocument doc;
    doc.setHtml(html);

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    doc.print(&printer);

    QMessageBox::information(this, "Exportation réussie",
                             "Tous les matériels présents dans la base ont été exportés :\n" + filePath);
}

// ==============================================
// SPONSOR CRUD OPERATIONS
// sponsor;
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

    // ACTION 2 : APPLIQUER LE TRI
    if (ui->comboBox_tri) {
        QString triSelectionne = ui->comboBox_tri->currentText().toLower();

        if (triSelectionne == "nom") {
            Sponsor::trierParNom(ui->tableWidget_2);
            qDebug() << "✅ Tableau affiché ET trié par nom";
        }
        else if (triSelectionne == "id") {
            Sponsor::trierParId(ui->tableWidget_2);
            qDebug() << "✅ Tableau affiché ET trié par ID";
        }
        else {
            qDebug() << "🔶 Aucun tri appliqué";
        }
    }

    // ⭐⭐ ACTION 3 : SURlIGNER LE SPONSOR RENOUVELÉ ⭐⭐
    QString sponsorRenouvele = SponsorManager::getSponsorRenouvele();

    if (!sponsorRenouvele.isEmpty()) {
        qDebug() << "🎯 Recherche du sponsor à surligner:" << sponsorRenouvele;

        bool sponsorTrouve = false;

        // Parcourir toutes les lignes du tableau
        for (int row = 0; row < ui->tableWidget_2->rowCount(); ++row) {
            QTableWidgetItem* itemId = ui->tableWidget_2->item(row, 0);

            if (itemId && itemId->text() == sponsorRenouvele) {
                // 🔥 SURlIGNER TOUTE LA LIGNE EN ROSE
                for (int col = 0; col < ui->tableWidget_2->columnCount(); ++col) {
                    QTableWidgetItem* item = ui->tableWidget_2->item(row, col);
                    if (item) {
                        item->setBackground(QColor(255, 182, 193)); // Rose pastel
                    }
                }

                // Sélectionner la ligne
                ui->tableWidget_2->selectRow(row);

                // Faire défiler jusqu'à la ligne
                ui->tableWidget_2->scrollToItem(ui->tableWidget_2->item(row, 0));

                sponsorTrouve = true;
                qDebug() << "✅ Sponsor" << sponsorRenouvele << "surligné en rose";

                // Effacer après affichage
                SponsorManager::clearSponsorRenouvele(); // On va ajouter cette fonction
                break;
            }
        }

        if (!sponsorTrouve) {
            qDebug() << "⚠️ Sponsor" << sponsorRenouvele << "non trouvé dans le tableau";
        }
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
    QString recherche = ui->lineEdit_chercher->text().trimmed();

    if (recherche.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Entrez un ID ou un nom pour la recherche.");
        return;
    }

    // Réinitialiser les couleurs
    for (int row = 0; row < ui->tableWidget_2->rowCount(); ++row) {
        for (int col = 0; col < ui->tableWidget_2->columnCount(); ++col) {
            QTableWidgetItem* item = ui->tableWidget_2->item(row, col);
            if (item) item->setBackground(QBrush());
        }
    }

    // Si c'est un ID (8 chiffres)
    if (recherche.length() == 8 && recherche.toInt() != 0) {
        // ▼▼▼ RECHERCHE PAR ID (EXISTANT) ▼▼▼
        QString nom, contribution, email;
        QDate dateDebut, dateFin;

        if (Sponsor::rechercherParId(recherche, nom, contribution, dateDebut, dateFin, email)) {
            // REMPLIR les champs
            ui->lineEdit_id->setText(recherche);
            ui->lineEdit_nom->setText(nom);

            int index = ui->combobox_contribution->findText(contribution);
            if (index >= 0) ui->combobox_contribution->setCurrentIndex(index);

            ui->date_debut->setDate(dateDebut);
            ui->date_fin->setDate(dateFin);
            ui->lineEdit_email->setText(email);

            currentSponsorId = recherche;

            // Colorier la ligne en ROSE
            bool trouve = false;
            for (int row = 0; row < ui->tableWidget_2->rowCount(); ++row) {
                QTableWidgetItem* itemId = ui->tableWidget_2->item(row, 0);
                if (itemId && itemId->text() == recherche) {
                    trouve = true;
                    for (int col = 0; col < ui->tableWidget_2->columnCount(); ++col) {
                        QTableWidgetItem* item = ui->tableWidget_2->item(row, col);
                        if (item) item->setBackground(QColor(255, 182, 193)); // ROSE
                    }
                    break;
                }
            }

            if (trouve) {
                QMessageBox::information(this, "Recherche", "Sponsor trouvé par ID !\nLigne surlignée en ROSE.");
            } else {
                QMessageBox::information(this, "Recherche", "Sponsor trouvé par ID !\nCliquez sur 'Afficher' pour voir dans le tableau.");
            }
        } else {
            QMessageBox::information(this, "Recherche", "Aucun sponsor trouvé avec l'ID: " + recherche);
            on_AnnulerSponsor_clicked();
        }
    } else {
        // ▼▼▼ RECHERCHE PAR NOM (NOUVEAU) ▼▼▼
        Sponsor::rechercherParNom(ui->tableWidget_2, recherche);

        // Colorier les lignes en VERT
        int nbResultats = 0;
        for (int row = 0; row < ui->tableWidget_2->rowCount(); ++row) {
            QTableWidgetItem* itemNom = ui->tableWidget_2->item(row, 1);
            if (itemNom && itemNom->text().toLower().contains(recherche.toLower())) {
                nbResultats++;
                for (int col = 0; col < ui->tableWidget_2->columnCount(); ++col) {
                    QTableWidgetItem* item = ui->tableWidget_2->item(row, col);
                    if (item) item->setBackground(QColor(144, 238, 144)); // VERT CLAIR
                }
            }
        }

        if (nbResultats > 0) {
            QMessageBox::information(this, "Recherche",
                                     QString("%1 sponsor(s) trouvé(s) pour le nom: %2\nLignes surlignées en VERT.")
                                         .arg(nbResultats).arg(recherche));
        } else {
            QMessageBox::information(this, "Recherche", "Aucun sponsor trouvé pour le nom: " + recherche);
        }
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
// ▼▼▼▼▼ AJOUTEZ CETTE FONCTION POUR LE TRI AUTOMATIQUE ▼▼▼▼▼
void MainWindow::on_comboBox_tri_currentIndexChanged(int index)
{
    Q_UNUSED(index);

    // Appliquer le tri automatiquement si le tableau a des données
    if (ui->tableWidget_2->rowCount() > 0) {
        on_AfficherSponsor_clicked();
    }
}
// =====================
//  MISE À JOUR DU STYLE
// =====================
void MainWindow::updateNavigationStyle(int activeIndex)
{
    // Crée une liste de tes 6 boutons de navigation
    QList<QToolButton*> buttons;
    buttons << ui->btn_staff
            << ui->btn_client
            << ui->btn_materiel
            << ui->btn_projet
            << ui->btn_sponsor
            << ui->btn_createur;

    // Met à jour chaque bouton
    for (int i = 0; i < buttons.size(); ++i) {
        QToolButton* button = buttons[i];  // <-- IMPORTANT: créer une variable

        if (i == activeIndex) {
            // BOUTON ACTIF
            button->setStyleSheet(
                "QToolButton { "
                "    border: none; "
                "    border-radius: 10px; "
                "    color: white; "
                "    padding: 12px 15px; "
                "    margin: 6px 8px; "
                "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
                "                               stop:0 #9B59B6, stop:1 #BDC3C7); "
                "    border-left: 4px solid #F8C8DC; "
                "    font-weight: bold; "
                "    text-align: left; "
                "}"
                );
            button->setChecked(true);    // Bouton ACTIF
        } else {
            // BOUTON INACTIF
            button->setStyleSheet(
                "QToolButton { "
                "    border: none; "
                "    border-radius: 10px; "
                "    color: white; "
                "    padding: 12px 15px; "
                "    margin: 6px 8px; "
                "    background: rgba(255, 255, 255, 0.08); "  /* Remplace transparent */
                "    text-align: left; "
                "    transition: all 0.3s ease; "
                "}"
                "QToolButton:hover { "
                "    background: rgba(255, 255, 255, 0.15); "
                "    padding-left: 18px; "
                "}"
                );
            button->setChecked(false);   // Bouton INACTIF
        }
    }
}
void MainWindow::on_toolButton_11_clicked()
{
    // Implémentez cette fonction selon ce qu'elle doit faire
    // Par exemple, si c'est un bouton de recherche ou d'action :
    QMessageBox::information(this, "Info", "Bouton 11 cliqué - Fonction à implémenter");
}
// =====================
//  METTRE À JOUR LE STYLE DES BOUTONS
// =====================
// =====================
//  STYLISER LES FORMULAIRES SPÉCIFIQUES
// =====================
