#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug> // Pour le debug
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
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
// ... autres includes existants ...
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>  // Ajoutez cette ligne
#include <QDir>
#include <QScrollArea>
#include <QProgressBar>
#include <QFrame>

// =====================
//  CONSTRUCTEUR
// =====================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "🏁 Début initialisation MainWindow";
    // Connexion des boutons de navigation
    connect(ui->btn_staff,    &QToolButton::clicked, this, &MainWindow::showStaff);
    connect(ui->btn_client,  &QToolButton::clicked, this, &MainWindow::showClient);
    connect(ui->btn_materiel, &QToolButton::clicked, this, &MainWindow::showMateriel);
    connect(ui->btn_projet,   &QToolButton::clicked, this, &MainWindow::showProjet);
    connect(ui->btn_sponsor,  &QToolButton::clicked, this, &MainWindow::showSponsor);
    connect(ui->btn_createur, &QToolButton::clicked, this, &MainWindow::showCreateur);
    // Connexion pour le bouton quitter
    connect(ui->toolButton_3, &QToolButton::clicked, this, &MainWindow::close);

    // Clients
    setupTabClient();
    refreshClientsGrid();

    // Projets
    setupTabProjet();
    refreshProjetsGrid();

    // Staff
    setupTabStaff();
    refreshStaffGrid();

    //setupIntelligentCalendar();

    // Materiel
    setupTabMateriel();
    refreshMaterielGrid();

    // Sponsor
    setupTabSponsor();

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
    connect(ui->toolButton_11, &QToolButton::clicked, this, &MainWindow::on_toolButton_11_clicked);
    connect(ui->toolButton_12, &QToolButton::clicked, this, &MainWindow::on_toolButton_12_clicked);
    connect(ui->toolButton_59, &QToolButton::clicked, this, &MainWindow::on_toolButton_59_clicked);
    connect(ui->toolButton_62, &QToolButton::clicked, this, &MainWindow::on_toolButton_62_clicked);

    // Connexion pour recherche et tri SPONSOR
    connect(ui->toolButton_9, &QToolButton::clicked, this, &MainWindow::on_toolButton_9_clicked);
    connect(ui->toolButton_17, &QToolButton::clicked, this, &MainWindow::on_toolButton_17_clicked);
    connect(ui->comboBox_5, QOverload<const QString &>::of(&QComboBox::currentTextChanged),
            this, &MainWindow::on_comboBox_5_currentTextChanged);

    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow() { delete ui; }

// =====================
//  NAVIGATION (option)
// =====================
void MainWindow::showStaff()    { ui->stackedWidget->setCurrentIndex(0); }
void MainWindow::showClient()   { ui->stackedWidget->setCurrentIndex(1); }
void MainWindow::showMateriel() { ui->stackedWidget->setCurrentIndex(2); }
void MainWindow::showProjet()   { ui->stackedWidget->setCurrentIndex(3); }
void MainWindow::showSponsor()  { ui->stackedWidget->setCurrentIndex(4); }
void MainWindow::showCreateur() { ui->stackedWidget->setCurrentIndex(5); }

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
    ui->tab_Client->setColumnCount(7);
    QStringList headers{ "", "ID_CLIENT", "NOM", "PRENOM", "ENTREPRISE", "EMAIL", "TYPE" };
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

    // Gérer les radio buttons pour TYPE
    if (ui->entre->isChecked()) {
        c.TYPE = "entreprise";
    } else if (ui->insta->isChecked()) {
        c.TYPE = "instagrameur";
    } else if (ui->autr->isChecked()) {
        c.TYPE = "Autre";
    } else {
        c.TYPE = "";  // Aucun sélectionné
    }

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
        // Réinitialiser les radio buttons
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

    // Gérer les radio buttons pour TYPE
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
    // Contrôles de saisie AVANT conversion/SQL
    const QString idT  = ui->ID_CLIENT->text().trimmed();
    const QString nomT = ui->NOM->text().trimmed();
    const QString preT = ui->PRENOM->text().trimmed();
    const QString entT = ui->ENTREPRISE->text().trimmed();
    const QString mailT= ui->EMAIL->text().trimmed();

    // Vérifier qu'un type est sélectionné
    bool typeSelected = ui->entre->isChecked() || ui->insta->isChecked() || ui->autr->isChecked();

    // Expressions régulières pour validation
    static const QRegularExpression reInt(R"(^\d+$)");
    static const QRegularExpression reText(R"(^[a-zA-ZÀ-ÿ\s'-]+$)"); // Lettres, espaces, apostrophe, trait d'union
    static const QRegularExpression reEmail(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");

    // Vérification des champs obligatoires
    if (idT.isEmpty() || nomT.isEmpty() || preT.isEmpty() ||
        entT.isEmpty() || mailT.isEmpty() || !typeSelected) {
        QMessageBox::warning(this, "Validation", "Tous les champs sont obligatoires.");
        return;
    }

    // Validation ID_CLIENT: doit être un nombre de exactement 8 chiffres
    if (!reInt.match(idT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "ID_CLIENT doit être un nombre.");
        ui->ID_CLIENT->setFocus();
        return;
    }

    if (idT.length() != 8) {
        QMessageBox::warning(this, "Validation", "ID_CLIENT doit contenir exactement 8 chiffres (exemple: 12345678).");
        ui->ID_CLIENT->setFocus();
        return;
    }

    // Validation Nom: lettres seulement
    if (!reText.match(nomT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le nom doit contenir uniquement des lettres.");
        ui->NOM->setFocus();
        return;
    }

    // Validation Prénom: lettres seulement
    if (!reText.match(preT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le prénom doit contenir uniquement des lettres.");
        ui->PRENOM->setFocus();
        return;
    }

    // Validation Entreprise: lettres seulement
    if (!reText.match(entT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "L'entreprise doit contenir uniquement des lettres.");
        ui->ENTREPRISE->setFocus();
        return;
    }

    // Validation Email: format email valide
    if (!reEmail.match(mailT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "L'email doit avoir un format valide (exemple: nom@domaine.com).");
        ui->EMAIL->setFocus();
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

// ===================================================
//                  PROJETS
// ===================================================
void MainWindow::setupTabProjet()
{
    ui->tableWidget_7->setColumnCount(6);
    QStringList headers{ "ID_PROJET", "TYPE", "DATE_D", "DATE_F", "MONTANT", "PAIMENT" };
    ui->tableWidget_7->setHorizontalHeaderLabels(headers);

    ui->tableWidget_7->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_7->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_7->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_7->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Initialize sort comboBox with options
    ui->comboBox_12->clear();
    ui->comboBox_12->addItem("Par défaut"); // Default/no sort
    ui->comboBox_12->addItem("Date début");
    ui->comboBox_12->addItem("Date fin");
    ui->comboBox_12->addItem("Montant");
}

void MainWindow::refreshProjetsGrid()
{
    ui->tableWidget_7->setRowCount(0);

    // Create a custom query to get the data we need with the new schema
    QSqlQuery query;
    query.prepare("SELECT ID_PROJET, TYPE, TO_CHAR(DATE_D, 'YYYY-MM-DD') AS DATE_D, "
                  "TO_CHAR(DATE_F, 'YYYY-MM-DD') AS DATE_F, MONTANT, PAIMENT FROM ABIR.PROJET");

    if (!query.exec()) {
        qDebug() << "Error refreshing projets grid:" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->tableWidget_7->insertRow(row);
        ui->tableWidget_7->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // ID_PROJET
        ui->tableWidget_7->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // TYPE
        ui->tableWidget_7->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // DATE_D
        ui->tableWidget_7->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // DATE_F
        ui->tableWidget_7->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // MONTANT
        ui->tableWidget_7->setItem(row, 5, new QTableWidgetItem(query.value(5).toString())); // PAIMENT
        row++;
    }
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

    // Colonnes: 0=ID_PROJET, 1=TYPE, 2=DATE_D, 3=DATE_F, 4=MONTANT, 5=PAIMENT
    QTableWidgetItem* idItem = ui->tableWidget_7->item(row, 0);
    QTableWidgetItem* typeItem = ui->tableWidget_7->item(row, 1);
    QTableWidgetItem* dateDItem = ui->tableWidget_7->item(row, 2);
    QTableWidgetItem* dateFItem = ui->tableWidget_7->item(row, 3);
    QTableWidgetItem* montantItem = ui->tableWidget_7->item(row, 4);
    QTableWidgetItem* paimentItem = ui->tableWidget_7->item(row, 5);

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

    // ID_CLIENT is no longer displayed in table, but form still needs it
    // Clear it when populating from table
    ui->lineEdit_38->clear();
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

    // Validation spécifique pour ID_PROJET: exactement 3 chiffres
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
            QMessageBox::critical(this, "Erreur", "Projet existe déjà id doit etre unique.");
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
void MainWindow::on_toolButton_53_clicked()
{
    setProjetFormMode(false);
}

// ===============================
//  TRIER PROJETS (comboBox_12)
// ===============================
void MainWindow::on_comboBox_12_currentTextChanged(const QString &text)
{
    if (text == "Par défaut") {
        // Use the default display method
        refreshProjetsGrid();
    } else {
        // Use the sorted display method
        Projet projet;
        QSqlQueryModel* model = projet.AfficherProjetsTri\u00e9s(text);

        if (!model) return;

        // Clear and populate table with sorted data
        ui->tableWidget_7->setRowCount(0);

        for (int i = 0; i < model->rowCount(); ++i) {
            ui->tableWidget_7->insertRow(i);
            ui->tableWidget_7->setItem(i, 0, new QTableWidgetItem(model->data(model->index(i, 0)).toString())); // ID_PROJET
            ui->tableWidget_7->setItem(i, 1, new QTableWidgetItem(model->data(model->index(i, 1)).toString())); // TYPE
            ui->tableWidget_7->setItem(i, 2, new QTableWidgetItem(model->data(model->index(i, 2)).toString())); // DATE_D
            ui->tableWidget_7->setItem(i, 3, new QTableWidgetItem(model->data(model->index(i, 3)).toString())); // DATE_F
            ui->tableWidget_7->setItem(i, 4, new QTableWidgetItem(model->data(model->index(i, 4)).toString())); // MONTANT
            ui->tableWidget_7->setItem(i, 5, new QTableWidgetItem(model->data(model->index(i, 5)).toString())); // PAIMENT
        }

        delete model;
    }
}

// ===============================
//  RECHERCHER PROJET PAR ID (toolButton_54)
// ===============================
void MainWindow::on_toolButton_54_clicked()
{
    QString idText = ui->lineEdit_30->text().trimmed();

    if (idText.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez entrer un ID de projet à rechercher.");
        ui->lineEdit_30->setFocus();
        return;
    }

    // Validate that ID is a number
    bool ok;
    int id = idText.toInt(&ok);
    if (!ok || id <= 0) {
        QMessageBox::warning(this, "Recherche", "L'ID doit être un nombre entier positif.");
        ui->lineEdit_30->setFocus();
        return;
    }

    // Search for the project
    QSqlQueryModel* model = Projet::ChercherProjetParIdStatique(id);

    if (!model) {
        QMessageBox::warning(this, "Recherche", "Erreur lors de la recherche.");
        return;
    }

    if (model->rowCount() == 0) {
        QMessageBox::information(this, "Recherche", QString("Aucun projet trouvé avec l'ID %1.").arg(id));
        delete model;
        return;
    }

    // Clear and populate table with search results
    ui->tableWidget_7->setRowCount(0);

    for (int i = 0; i < model->rowCount(); ++i) {
        ui->tableWidget_7->insertRow(i);
        ui->tableWidget_7->setItem(i, 0, new QTableWidgetItem(model->data(model->index(i, 0)).toString())); // ID_PROJET
        ui->tableWidget_7->setItem(i, 1, new QTableWidgetItem(model->data(model->index(i, 1)).toString())); // TYPE
        ui->tableWidget_7->setItem(i, 2, new QTableWidgetItem(model->data(model->index(i, 2)).toString())); // DATE_D
        ui->tableWidget_7->setItem(i, 3, new QTableWidgetItem(model->data(model->index(i, 3)).toString())); // DATE_F
        ui->tableWidget_7->setItem(i, 4, new QTableWidgetItem(model->data(model->index(i, 4)).toString())); // MONTANT
        ui->tableWidget_7->setItem(i, 5, new QTableWidgetItem(model->data(model->index(i, 5)).toString())); // PAIMENT
    }

    delete model;

    QMessageBox::information(this, "Recherche", QString("Projet trouvé avec l'ID %1.").arg(id));
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

    // Connect cancel button
    connect(ui->staffCancelForm, &QToolButton::clicked, this, &MainWindow::on_staffCancelForm_clicked);

    // Connect sort comboBox
    connect(ui->comboBox, QOverload<const QString&>::of(&QComboBox::currentTextChanged),
            this, &MainWindow::on_comboBox_currentTextChanged);
    // Connect PDF export button
    //connect(ui->pdf, &QToolButton::clicked, this, &MainWindow::on_pdf_clicked);
    connect(ui->toolButton_27, &QToolButton::clicked, this, &MainWindow::rechercherStaff);

    /*// ==== CORRECTION : UTILISER LE BON NOM D'ONGLET ====
    // Chercher l'onglet qui contient le staff. Essayez ces noms possibles :
    QWidget *staffTab = nullptr;

    // Essayer différents noms d'onglets possibles
    staffTab = findChild<QWidget*>("tabStaff");
    if (!staffTab) staffTab = findChild<QWidget*>("tab_Staff");
    if (!staffTab) staffTab = findChild<QWidget*>("staffTab");
    if (!staffTab) staffTab = findChild<QWidget*>("tab_2"); // Souvent le 2ème onglet
    if (!staffTab) staffTab = findChild<QWidget*>("tabWidget_page2"); // Ou autre nom

    // Si on ne trouve pas d'onglet spécifique, utiliser le tabWidget courant
    if (!staffTab && ui->tabWidget) {
        staffTab = ui->tabWidget->currentWidget();
    }

    if (staffTab) {
        // Nettoyer l'onglet staff s'il y a déjà des widgets
        QLayout* existingLayout = staffTab->layout();
        if (existingLayout) {
            QLayoutItem* item;
            while ((item = existingLayout->takeAt(0)) != nullptr) {
                if (item->widget()) {
                    item->widget()->hide();
                    item->widget()->deleteLater();
                }
                delete item;
            }
        }

        // Créer un nouveau layout pour l'onglet staff
        QVBoxLayout *staffLayout = new QVBoxLayout(staffTab);
        staffLayout->setContentsMargins(5, 5, 5, 5);

        // Créer le CalendarWidget
        CalendarWidget *calendarWidget = new CalendarWidget(staffTab);
        staffLayout->addWidget(calendarWidget);

        // ⭐⭐ CONNEXION À GROUPBOX_5 ⭐⭐
        calendarWidget->connectToGroupBox5(ui->groupBox_5);


        // Connecter aussi aux autres éléments si nécessaire
        QCalendarWidget *mainCalendar = findChild<QCalendarWidget*>("mainCalendarWidget");
        if (mainCalendar) {
            calendarWidget->connectToCalendarWidget(mainCalendar);
        }

        QGroupBox *detailsGroupBox = findChild<QGroupBox*>("detailsGroupBox");
        if (detailsGroupBox) {
            calendarWidget->connectToDetailsGroupBox(detailsGroupBox);
        }

        qDebug() << "CalendarWidget ajouté à l'onglet Staff et connecté à groupBox_5";
    } else {
        qDebug() << "Impossible de trouver l'onglet staff pour ajouter CalendarWidget";
    }*/

    // Initialize staff sort comboBox
    initializeStaffSortComboBox();
    // Afficher les statistiques initiales
    afficherStatistiquesDansGroupBox();
    afficherStatistiquesCompetencesDansGroupBox4();

    // Remove automatic form population - user must click edit button explicitly
    // connect(ui->tableWidget_3, &QTableWidget::cellClicked, this, [this](int row, int col){
    //     if (row < 0 || col == 0) return;
    //     populateStaffFormFromRow(row);
    //     setStaffFormMode(true);
    // });
}

void MainWindow::refreshStaffGrid()
{
    ui->tableWidget_3->setRowCount(0);

    Staff staff;
    QSqlQueryModel* model = staff.afficher();

    if (!model) return;

    for (int i = 0; i < model->rowCount(); ++i) {
        ui->tableWidget_3->insertRow(i);
        ui->tableWidget_3->setItem(i, 1, new QTableWidgetItem(model->data(model->index(i, 0)).toString())); // ID_EMPLOYE
        ui->tableWidget_3->setItem(i, 2, new QTableWidgetItem(model->data(model->index(i, 1)).toString())); // NOM
        ui->tableWidget_3->setItem(i, 3, new QTableWidgetItem(model->data(model->index(i, 2)).toString())); // PRENOM
        ui->tableWidget_3->setItem(i, 4, new QTableWidgetItem(model->data(model->index(i, 3)).toString())); // POSTE
        ui->tableWidget_3->setItem(i, 5, new QTableWidgetItem(model->data(model->index(i, 4)).toString())); // COMPETENCE
        ui->tableWidget_3->setItem(i, 6, new QTableWidgetItem(model->data(model->index(i, 5)).toString())); // TELEPHONE
        ui->tableWidget_3->setItem(i, 7, new QTableWidgetItem(model->data(model->index(i, 6)).toString())); // EMAIL
        ui->tableWidget_3->setItem(i, 8, new QTableWidgetItem(model->data(model->index(i, 7)).toString())); // MOT_DE_PASSE
        addStaffEditPenForRow(i);
    }

    delete model;
    mettreAJourStatistiques();
    mettreAJourStatistiquesCompetences();
}

Staff MainWindow::readStaffForm() const
{
    Staff s;
    QString id = ui->lineEdit_13->text().trimmed();
    QString nom = ui->lineEdit_14->text().trimmed();
    QString prenom = ui->lineEdit_20->text().trimmed();
    QString poste = ui->comboBox_6->currentText();
    QString telephone = ui->lineEdit_19->text().trimmed();

    // Gérer les radio buttons pour compétence
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

    // Read email and password from form fields (assuming they exist in UI)
    // For now, using placeholder field names - these should be updated to match actual UI field names
    QString email;
    QString motDePasse;

    // Try to find email field (assuming it might be named differently)
    QLineEdit* emailField = this->findChild<QLineEdit*>("staffEmailLineEdit");
    if (emailField) {
        email = emailField->text().trimmed();
    } else {
        // Fallback to auto-generated email if field doesn't exist
        email = nom.toLower() + "." + prenom.toLower() + "@company.com";
    }

    // Try to find password field
    QLineEdit* passwordField = this->findChild<QLineEdit*>("staffMotDePasseLineEdit");
    if (passwordField) {
        motDePasse = passwordField->text().trimmed();
    } else {
        motDePasse = ""; // Default empty password
    }

    return Staff(id, nom, prenom, poste, competence, telephone, email, motDePasse);
}

void MainWindow::clearStaffForm()
{
    ui->lineEdit_13->clear();  // ID
    ui->lineEdit_14->clear();  // NOM
    ui->lineEdit_20->clear();  // PRENOM
    ui->lineEdit_19->clear();  // TELEPHONE
    ui->comboBox_6->setCurrentIndex(0);

    // Clear email and password fields if they exist
    QLineEdit* emailField = this->findChild<QLineEdit*>("staffEmailLineEdit");
    if (emailField) {
        emailField->clear();
    }
    QLineEdit* passwordField = this->findChild<QLineEdit*>("staffMotDePasseLineEdit");
    if (passwordField) {
        passwordField->clear();
    }

    // Réinitialiser le groupe de radio buttons pour compétence
    if (m_staffCompetenceGroup->checkedButton()) {
        m_staffCompetenceGroup->setExclusive(false);
        m_staffCompetenceGroup->checkedButton()->setChecked(false);
        m_staffCompetenceGroup->setExclusive(true);
    }
}

void MainWindow::populateStaffFormFromRow(int row)
{
    if (row < 0 || row >= ui->tableWidget_3->rowCount()) return;

    // Colonnes: 1=ID_EMPLOYE, 2=NOM, 3=PRENOM, 4=POSTE, 5=COMPETENCE, 6=TELEPHONE, 7=EMAIL, 8=MOT_DE_PASSE
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

    // Populate email field if it exists
    QLineEdit* emailField = this->findChild<QLineEdit*>("staffEmailLineEdit");
    if (emailItem && emailField) {
        emailField->setText(emailItem->text());
    }

    // Populate password field if it exists
    QLineEdit* passwordField = this->findChild<QLineEdit*>("staffMotDePasseLineEdit");
    if (passwordItem && passwordField) {
        passwordField->setText(passwordItem->text());
    }

    if (posteItem) {
        int index = ui->comboBox_6->findText(posteItem->text());
        if (index >= 0) ui->comboBox_6->setCurrentIndex(index);
    }

    // Gérer les radio buttons pour compétence
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
        ui->lineEdit_13->setEnabled(false); // ID_EMPLOYE ne peut pas être modifié en mode édition
    } else {
        ui->toolButton_15->setText("Ajouter");
        ui->lineEdit_13->setEnabled(true); // ID_EMPLOYE peut être saisi en mode ajout
        // Don't clear form here - let the caller decide when to clear
    }
}

void MainWindow::addStaffEditPenForRow(int row)
{
    auto *editBtn = new QPushButton;
    editBtn->setToolTip("Edit");
    editBtn->setFlat(true);
    editBtn->setCursor(Qt::PointingHandCursor);
    const char* kPen = ":/image/ressource/edit.png";

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

// ===============================
//  AJOUTER / MODIFIER STAFF
// ===============================
void MainWindow::on_toolButton_15_clicked()
{
    // Contrôles de saisie
    const QString idT = ui->lineEdit_13->text().trimmed();
    const QString nomT = ui->lineEdit_14->text().trimmed();
    const QString prenomT = ui->lineEdit_20->text().trimmed();
    const QString telephoneT = ui->lineEdit_19->text().trimmed();

    // Vérifier qu'une compétence est sélectionnée
    bool competenceSelected = ui->radioButton->isChecked() ||
                              ui->radioButton_2->isChecked() ||
                              ui->radioButton_3->isChecked();

    // Expressions régulières pour validation
    static const QRegularExpression reInt(R"(^\d+$)");
    static const QRegularExpression reText(R"(^[a-zA-ZÀ-ÿ\s'-]+$)"); // Lettres, espaces, apostrophe, trait d'union

    // Vérification des champs obligatoires
    if (idT.isEmpty() || nomT.isEmpty() || prenomT.isEmpty() ||
        telephoneT.isEmpty() || ui->comboBox_6->currentText().isEmpty() || !competenceSelected) {
        QMessageBox::warning(this, "Validation", "Tous les champs sont obligatoires.");
        return;
    }

    // Validation ID_EMPLOYE: doit être un nombre de exactement 8 chiffres
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

    // Validation Nom: lettres seulement
    if (!reText.match(nomT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le nom doit contenir uniquement des lettres.");
        ui->lineEdit_14->setFocus();
        return;
    }

    // Validation Prénom: lettres seulement
    if (!reText.match(prenomT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le prénom doit contenir uniquement des lettres.");
        ui->lineEdit_20->setFocus();
        return;
    }

    // Validation Téléphone: exactement 8 chiffres
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

    // Email validation if the field exists
    QLineEdit* emailField = this->findChild<QLineEdit*>("staffEmailLineEdit");
    if (emailField) {
        QString emailT = emailField->text().trimmed();
        if (!emailT.isEmpty() && !Staff::isValidEmail(emailT)) {
            QMessageBox::warning(this, "Validation", "Veuillez entrer une adresse email valide (exemple: nom@domaine.com).");
            emailField->setFocus();
            return;
        }
    }

    // Password validation if the field exists
    QLineEdit* passwordField = this->findChild<QLineEdit*>("staffMotDePasseLineEdit");
    if (passwordField) {
        QString motDePasseT = passwordField->text().trimmed();
        if (!motDePasseT.isEmpty() && motDePasseT.length() < 6) {
            QMessageBox::warning(this, "Validation", "Le mot de passe doit contenir au moins 6 caractères.");
            passwordField->setFocus();
            return;
        }
    }

    // Vérification de l'unicité de l'ID_EMPLOYE pour les nouveaux employés
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
        // Mode Ajout
        if (s.ajouter()) {
            QMessageBox::information(this, "Succès", "Employé ajouté avec succès.");
            clearStaffForm();
            refreshStaffGrid();
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout de l'employé. Vérifiez les logs.");
        }
    } else {
        // Mode Modification
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

// ===============================
//  AFFICHER STAFF
// ===============================
void MainWindow::on_toolButton_23_clicked()
{
    refreshStaffGrid();
    mettreAJourStatistiques();
}

// ===============================
//  SUPPRIMER STAFF
// ===============================
void MainWindow::on_toolButton_25_clicked()
{
    // Récupérer la ligne sélectionnée dans le tableau
    int currentRow = ui->tableWidget_3->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Suppression", "Sélectionne une ligne dans le tableau pour supprimer un employé.");
        return;
    }

    // Récupérer l'ID_EMPLOYE depuis la colonne 1 de la ligne sélectionnée
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

// ===============================
//  ÉDITER STAFF (remplit le formulaire)
// ===============================
void MainWindow::on_toolButton_26_clicked()
{
    // Récupérer la ligne sélectionnée dans le tableau
    int currentRow = ui->tableWidget_3->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Édition", "Sélectionne une ligne dans le tableau pour éditer un employé.");
        return;
    }

    // Remplir le formulaire avec les données de la ligne sélectionnée
    populateStaffFormFromRow(currentRow);
    setStaffFormMode(true);
}

// ===============================
//  ANNULER STAFF FORM
// ===============================
void MainWindow::on_staffCancelForm_clicked()
{
    // Clear the form and reset to add mode
    setStaffFormMode(false);
    clearStaffForm();
}

// ===============================
//  RECHERCHER STAFF (ID ou NOM) - Fonction unifiée
// ===============================
void MainWindow::rechercherStaff()
{
    QString recherche = ui->lineEdit_21->text().trimmed();

    if (recherche.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez entrer un ID ou un nom d'employé à rechercher.");
        ui->lineEdit_21->setFocus();
        return;
    }

    QSqlQueryModel* model = nullptr;
    bool rechercheParId = false; // ← DÉCLARATION DE LA VARIABLE ICI

    // Décider du type de recherche
    if (recherche.toInt() > 0 && recherche.length() == 8) {
        // Si c'est un nombre de 8 chiffres → recherche par ID
        model = Staff::chercherParId(recherche);
        rechercheParId = true;
    } else {
        // Sinon → recherche par nom
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

    // Clear and populate table with search results
    ui->tableWidget_3->setRowCount(0);

    for (int i = 0; i < model->rowCount(); ++i) {
        ui->tableWidget_3->insertRow(i);
        ui->tableWidget_3->setItem(i, 1, new QTableWidgetItem(model->data(model->index(i, 0)).toString())); // ID_EMPLOYE
        ui->tableWidget_3->setItem(i, 2, new QTableWidgetItem(model->data(model->index(i, 1)).toString())); // NOM
        ui->tableWidget_3->setItem(i, 3, new QTableWidgetItem(model->data(model->index(i, 2)).toString())); // PRENOM
        ui->tableWidget_3->setItem(i, 4, new QTableWidgetItem(model->data(model->index(i, 3)).toString())); // POSTE
        ui->tableWidget_3->setItem(i, 5, new QTableWidgetItem(model->data(model->index(i, 4)).toString())); // COMPETENCE
        ui->tableWidget_3->setItem(i, 6, new QTableWidgetItem(model->data(model->index(i, 5)).toString())); // TELEPHONE
        ui->tableWidget_3->setItem(i, 7, new QTableWidgetItem(model->data(model->index(i, 6)).toString())); // EMAIL
        ui->tableWidget_3->setItem(i, 8, new QTableWidgetItem(model->data(model->index(i, 7)).toString())); // MOT_DE_PASSE
        addStaffEditPenForRow(i);
    }

    // Message personnalisé selon le type de recherche
    if (rechercheParId) {
        QMessageBox::information(this, "Recherche",
                                 QString("Employé trouvé avec l'ID \"%1\".").arg(recherche));
    } else {
        QMessageBox::information(this, "Recherche",
                                 QString("Employé trouvé avec le nom \"%1\".").arg(recherche));
    }

    delete model;
}

// ===============================
//  INITIALISER COMBOBOX TRI STAFF
// ===============================
void MainWindow::initializeStaffSortComboBox()
{
    // Use the comboBox named "comboBox" for staff sorting
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

// ===============================
//  TRIER STAFF (comboBox)
// ===============================
void MainWindow::on_comboBox_currentTextChanged(const QString &text)
{
    // Using comboBox for staff sorting as specified

    if (text == "Par défaut" || text.isEmpty()) {
        // Use the default display method
        refreshStaffGrid();
    } else {
        // Use the sorted display method
        Staff staff;
        QSqlQueryModel* model = staff.afficherTrié(text);

        if (!model) return;

        // Clear and populate table with sorted data
        ui->tableWidget_3->setRowCount(0);

        for (int i = 0; i < model->rowCount(); ++i) {
            ui->tableWidget_3->insertRow(i);
            ui->tableWidget_3->setItem(i, 1, new QTableWidgetItem(model->data(model->index(i, 0)).toString())); // ID_EMPLOYE
            ui->tableWidget_3->setItem(i, 2, new QTableWidgetItem(model->data(model->index(i, 1)).toString())); // NOM
            ui->tableWidget_3->setItem(i, 3, new QTableWidgetItem(model->data(model->index(i, 2)).toString())); // PRENOM
            ui->tableWidget_3->setItem(i, 4, new QTableWidgetItem(model->data(model->index(i, 3)).toString())); // POSTE
            ui->tableWidget_3->setItem(i, 5, new QTableWidgetItem(model->data(model->index(i, 4)).toString())); // COMPETENCE
            ui->tableWidget_3->setItem(i, 6, new QTableWidgetItem(model->data(model->index(i, 5)).toString())); // TELEPHONE
            ui->tableWidget_3->setItem(i, 7, new QTableWidgetItem(model->data(model->index(i, 6)).toString())); // EMAIL
            ui->tableWidget_3->setItem(i, 8, new QTableWidgetItem(model->data(model->index(i, 7)).toString())); // MOT_DE_PASSE
            addStaffEditPenForRow(i);
        }

        delete model;
    }
}
void MainWindow::on_pdf_clicked()
{
    // Désactiver le bouton temporairement pour éviter le double-clic
    ui->pdf->setEnabled(false);

    exporterTableWidgetVersPDF();

    // Réactiver le bouton après un court délai
    QTimer::singleShot(500, this, [this]() {
        ui->pdf->setEnabled(true);
    });
}





void MainWindow::exporterTableWidgetVersPDF()
{
    if (ui->tableWidget_3->rowCount() == 0) {
        QMessageBox::warning(this, "Aucune donnée", "Le tableau est vide !");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Exporter les employés",
        QDir::homePath() + "/employes.pdf",
        "Fichiers PDF (*.pdf)"
        );

    if (fileName.isEmpty()) return;

    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive))
        fileName += ".pdf";
    // Récupérer la date & heure d’exportation
    QString dateExport = QDateTime::currentDateTime().toString("dd/MM/yyyy - HH:mm:ss");
    // Construire le HTML
    QString html;
    html += "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Employés</title><style>";

    html += "body{font-family:Arial; margin:20px; background:#F8D7E3;}";
    html += "h1{color:#5A3E7A;text-align:center;}";

    html += "table{border-collapse:collapse;width:100%; background:#FFFFFF; font-size:11px;}";

    html += "th{background:#DCC7F8;color:#5A3E7A;padding:6px; font-size:11px;}";
    html += "td{border:1px solid #ccc;padding:5px;color:#5A3E7A; font-size:10px;}";

    html += "tr:nth-child(even){background:#F2F2F2;}";
    html += "tr:nth-child(odd){background:#F8D7E3;}";

    /* Largeurs ajustées */
    html += "th:nth-child(1), td:nth-child(1){ width:40px;}";   // ID
    html += "th:nth-child(2), td:nth-child(2){ width:90px;}";   // NOM
    html += "th:nth-child(3), td:nth-child(3){ width:90px;}";   // PRENOM
    html += "th:nth-child(4), td:nth-child(4){ width:80px;}";   // POSTE
    html += "th:nth-child(5), td:nth-child(5){ width:100px;}";  // COMPÉTENCE
    html += "th:nth-child(6), td:nth-child(6){ width:80px;}";   // TELEPHONE
    html += "th:nth-child(7), td:nth-child(7){ width:130px;}";  // EMAIL
    html += "th:nth-child(8), td:nth-child(8){ width:60px; text-align:center;}";  // MOT DE PASSE
                   // Rose pastel léger

    html += "</style></head><body>";

    // :::::::::::::: TITRE ::::::::::::::
    html += "<h1>LISTE DES EMPLOYÉS</h1>";

    // :::::::::::::: DATE & HEURE ::::::::::::::
    html += "<h3>Généré le : " + dateExport + "</h3>";
    html += "<table>";

    // En-têtes
    html += "<tr><th>ID</th><th>NOM</th><th>PRENOM</th><th>POSTE</th>";
    html += "<th>COMPÉTENCE</th><th>TÉLÉPHONE</th><th>EMAIL</th><th>MOT DE PASSE</th></tr>";

    // Données
    for (int row = 0; row < ui->tableWidget_3->rowCount(); ++row) {
        html += "<tr>";
        for (int col = 1; col <= 8; ++col) {
            QTableWidgetItem *item = ui->tableWidget_3->item(row, col);
            QString text = item ? item->text() : "";
            if (col == 8 && !text.isEmpty()) text = "••••••••";
            html += "<td>" + text + "</td>";
        }
        html += "</tr>";
    }

    html += "</table></body></html>";

    // Génération PDF
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setResolution(96);

    QPainter painter(&pdfWriter);

    QTextDocument doc;
    doc.setHtml(html);
    doc.drawContents(&painter);

    painter.end();

    QMessageBox::information(this, "Succès", "PDF généré avec succès !");
}



// ===============================
//  STATISTIQUES DANS GROUPBOX_3 (Version corrigée)
// ===============================

QMap<QString, int> MainWindow::compterEmployesParPoste()
{
    QMap<QString, int> statistiques;

    for (int row = 0; row < ui->tableWidget_3->rowCount(); ++row) {
        QTableWidgetItem *posteItem = ui->tableWidget_3->item(row, 4); // Colonne 4 = POSTE
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
    // Vider le groupBox_3 d'abord
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
        // Créer un nouveau layout si nécessaire
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

    // Titre des statistiques
    QLabel *titleLabel = new QLabel("📊 Statistiques par Poste");
    titleLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #2c3e50; margin-bottom: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // Informations générales (garder seulement cette ligne au lieu du résumé)
    int totalEmployes = ui->tableWidget_3->rowCount();
    QLabel *infoLabel = new QLabel(QString("Total: %1 employés | %2 postes")
                                       .arg(totalEmployes)
                                       .arg(stats.size()));
    infoLabel->setStyleSheet("color: #7f8c8d; font-size: 11px; margin-bottom: 15px;");
    infoLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(infoLabel);

    // Séparateur
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("color: #bdc3c7; margin: 5px 0px;");
    mainLayout->addWidget(line);

    // Trier par nombre décroissant
    QList<QPair<QString, int>> sortedStats;
    for (auto it = stats.begin(); it != stats.end(); ++it) {
        sortedStats.append(qMakePair(it.key(), it.value()));
    }

    std::sort(sortedStats.begin(), sortedStats.end(),
              [](const QPair<QString, int> &a, const QPair<QString, int> &b) {
                  return a.second > b.second;
              });

    // Couleurs pour les barres
    QStringList colors = {"#3498db", "#2ecc71", "#e74c3c", "#f39c12", "#9b59b6",
                          "#1abc9c", "#d35400", "#34495e", "#7f8c8d"};

    int colorIndex = 0;
    for (const auto &stat : sortedStats) {
        QString poste = stat.first;
        int count = stat.second;
        double percentage = (count * 100.0) / totalEmployes;

        // Conteneur pour chaque poste
        QWidget *posteWidget = new QWidget();
        QHBoxLayout *posteLayout = new QHBoxLayout(posteWidget);
        posteLayout->setContentsMargins(5, 2, 5, 2);

        // Nom du poste
        QLabel *posteLabel = new QLabel(poste);
        posteLabel->setStyleSheet("font-weight: bold; color: #2c3e50; min-width: 100px;");
        posteLayout->addWidget(posteLabel);

        // Barre de progression
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

        // Statistiques
        QLabel *statsLabel = new QLabel(QString("%1 (%2%)").arg(count).arg(percentage, 0, 'f', 1));
        statsLabel->setStyleSheet("color: #7f8c8d; font-size: 10px; min-width: 45px;");
        statsLabel->setAlignment(Qt::AlignRight);
        posteLayout->addWidget(statsLabel);

        mainLayout->addWidget(posteWidget);
        colorIndex++;
    }

    // Espacement
    mainLayout->addStretch();

    // Bouton de rafraîchissement
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
// ===============================
//  STATISTIQUES COMPÉTENCES DANS GROUPBOX_4 (Camembert)
// ===============================

QMap<QString, int> MainWindow::compterEmployesParCompetence()
{
    QMap<QString, int> statistiques;

    for (int row = 0; row < ui->tableWidget_3->rowCount(); ++row) {
        QTableWidgetItem *competenceItem = ui->tableWidget_3->item(row, 5); // Colonne 5 = COMPETENCE
        if (competenceItem) {
            QString competence = competenceItem->text().trimmed();
            if (!competence.isEmpty()) {
                // Normaliser les noms de compétences
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

// ===============================
//  STATISTIQUES COMPÉTENCES DANS GROUPBOX_4 (Version alternative sans QtCharts)
// ===============================

void MainWindow::afficherStatistiquesCompetencesDansGroupBox4()
{
    qDebug() << "=== DÉBUT AFFICHAGE STATS COMPÉTENCES PROFESSIONNEL ===";

    // Vider le groupBox_4 de manière sécurisée
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

    // Titre principal
    QLabel *mainTitleLabel = new QLabel("📊 Statistiques des Compétences");
    mainTitleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #9B59B6; margin-bottom: 5px;");
    mainTitleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(mainTitleLabel);

    // Récupérer les stats
    QMap<QString, int> stats = compterEmployesParCompetence();
    int totalEmployes = ui->tableWidget_3->rowCount();

    if (stats.isEmpty() || totalEmployes == 0) {
        QLabel *emptyLabel = new QLabel("Aucune donnée disponible");
        emptyLabel->setStyleSheet("color: #BDC3C7; font-style: italic; padding: 40px;");
        emptyLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(emptyLabel);
        return;
    }

    // Conteneur pour graphique + légende
    QWidget *chartContainer = new QWidget();
    QHBoxLayout *chartLayout = new QHBoxLayout(chartContainer);
    chartLayout->setSpacing(20);

    // GRAPHIQUE CIRCULAIRE
    PieChartWidget *pieChart = new PieChartWidget();
    pieChart->setData(stats, totalEmployes);
    pieChart->setFixedSize(220, 220);
    chartLayout->addWidget(pieChart, 0, Qt::AlignCenter);

    // LÉGENDE
    QWidget *legendWidget = new QWidget();
    QVBoxLayout *legendLayout = new QVBoxLayout(legendWidget);
    legendLayout->setSpacing(8);

    // Couleurs pour la légende
    QMap<QString, QString> colors;
    colors["Débutant"] = "#F8C8DC";
    colors["Intermédiaire"] = "#BDC3C7";
    colors["Avancé"] = "#9B59B6";

    // Trier pour l'affichage
    QStringList competencesOrder = {"Débutant", "Intermédiaire", "Avancé"};

    for (const QString &competence : competencesOrder) {
        if (stats.contains(competence)) {
            int count = stats[competence];
            double percentage = (count * 100.0) / totalEmployes;

            QWidget *legendItem = new QWidget();
            QHBoxLayout *itemLayout = new QHBoxLayout(legendItem);
            itemLayout->setContentsMargins(5, 2, 5, 2);

            // Point de couleur
            QLabel *colorDot = new QLabel();
            colorDot->setFixedSize(14, 14);
            colorDot->setStyleSheet(QString(
                                        "background: %1;"
                                        "border-radius: 7px;"
                                        "border: 2px solid %1;"
                                        ).arg(colors[competence]));

            // Texte
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

    // SUPPRIMER LA LIGNE RÉSUMÉ - CETTE PARTIE A ÉTÉ RETIRÉE

    mainLayout->addStretch();

    qDebug() << "=== FIN AFFICHAGE STATS COMPÉTENCES PROFESSIONNEL ===";
}


// ===============================
//  PIE CHART WIDGET (Sécurisé)
// ===============================

PieChartWidget::PieChartWidget(QWidget *parent)
    : QWidget(parent), m_total(0)
{
    // Définir vos couleurs
    m_colors["Débutant"] = QColor("#F8C8DC");
    m_colors["Intermédiaire"] = QColor("#BDC3C7");
    m_colors["Avancé"] = QColor("#9B59B6");

    setMinimumSize(200, 200);
    setMaximumSize(300, 300);
}

void PieChartWidget::setData(const QMap<QString, int> &data, int total)
{
    m_data = data;
    m_total = total;
    update(); // Redessine le widget
}

void PieChartWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    if (m_data.isEmpty() || m_total <= 0) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Calculer la zone de dessin (avec marges)
    int margin = 10;
    int size = qMin(width(), height()) - 2 * margin;
    QRectF pieRect(margin, margin, size, size);

    // Vérifications de sécurité
    if (pieRect.width() <= 0 || pieRect.height() <= 0) {
        return;
    }

    // Dessiner le fond
    painter.setBrush(QColor("#FFFFFF"));
    painter.setPen(QPen(QColor("#BDC3C7"), 1));
    painter.drawEllipse(pieRect);

    // Dessiner les sections du camembert
    double startAngle = 0;
    int colorIndex = 0;

    // Trier les données pour un affichage cohérent
    QStringList competencesOrder = {"Débutant", "Intermédiaire", "Avancé"};
    QList<QPair<QString, int>> sortedData;

    for (const QString &competence : competencesOrder) {
        if (m_data.contains(competence)) {
            sortedData.append(qMakePair(competence, m_data[competence]));
        }
    }

    // Ajouter les autres compétences
    for (auto it = m_data.begin(); it != m_data.end(); ++it) {
        if (!competencesOrder.contains(it.key())) {
            sortedData.append(qMakePair(it.key(), it.value()));
        }
    }

    for (const auto &item : sortedData) {
        QString competence = item.first;
        int value = item.second;
        double angle = (value * 360.0) / m_total;

        QColor color = m_colors.contains(competence) ? m_colors[competence] : QColor("#3498db");

        // Dessiner la section
        painter.setBrush(color);
        painter.setPen(QPen(Qt::white, 2));
        painter.drawPie(pieRect, startAngle * 16, angle * 16);

        startAngle += angle;
    }

    // Dessiner le centre pour effet donut (optionnel)
    if (size > 60) {
        painter.setBrush(QColor("#FFFFFF"));
        painter.setPen(Qt::NoPen);
        QPointF center = pieRect.center();
        qreal innerRadius = size * 0.3;
        painter.drawEllipse(center, innerRadius, innerRadius);
    }

    // Dessiner le pourcentage au centre
    painter.setPen(QPen(QColor("#9B59B6")));
    painter.setFont(QFont("Arial", 10, QFont::Bold));

    QString centerText = QString("%1\nemployés").arg(m_total);
    QRectF textRect = pieRect;
    painter.drawText(textRect, Qt::AlignCenter, centerText);
}
void MainWindow::mettreAJourStatistiquesCompetences()
{
    afficherStatistiquesCompetencesDansGroupBox4();
}


// ===================================================
//                  MATERIEL
// ===================================================
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

    connect(ui->tableWidget_4, &QTableWidget::cellClicked, this, [this](int row, int col){
        if (row < 0 || col == 0) return;
        populateMaterielFormFromRow(row);
        setMaterielFormMode(true);
    });
}

void MainWindow::refreshMaterielGrid()
{
    ui->tableWidget_4->setRowCount(0);

    Materiel materiel;
    materiel.afficher(ui->tableWidget_4);

    // Ajouter les boutons d'édition pour chaque ligne
    for (int i = 0; i < ui->tableWidget_4->rowCount(); ++i) {
        addMaterielEditPenForRow(i);
    }
}

Materiel MainWindow::readMaterielForm() const
{
    QString id = ui->lineEdit_15->text().trimmed();        // ID
    QString nom = ui->lineEdit_16->text().trimmed();       // NOM
    QString type = ui->equipmentComboBox->currentText();   // TYPE
    QString localisation = ui->lineEdit_18->text().trimmed(); // LOCALISATION (free text)

    // Gérer les radio buttons pour état
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

    // Handle location radio buttons (override free text if radio button is selected)
    if (ui->radioButton_22->isChecked()) {
        localisation = "studio tournage";
    } else if (ui->radioButton_23->isChecked()) {
        localisation = "salle montage";
    } else if (ui->radioButton_24->isChecked()) {
        localisation = "salle podcast";
    }
    // If no radio button is checked, use the text from lineEdit_18

    return Materiel(id, nom, type, etat, localisation);
}

void MainWindow::clearMaterielForm()
{
    ui->lineEdit_15->clear();  // ID
    ui->lineEdit_16->clear();  // NOM
    ui->equipmentComboBox->setCurrentIndex(0);  // TYPE - reset to first item
    ui->lineEdit_18->clear();  // LOCALISATION

    // Réinitialiser les groupes de radio buttons
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

    // Colonnes: 1=ID_MATERIEL, 2=NOM, 3=TYPE, 4=ETAT, 5=LOCALISATION
    QTableWidgetItem* idItem = ui->tableWidget_4->item(row, 1);
    QTableWidgetItem* nomItem = ui->tableWidget_4->item(row, 2);
    QTableWidgetItem* typeItem = ui->tableWidget_4->item(row, 3);
    QTableWidgetItem* etatItem = ui->tableWidget_4->item(row, 4);
    QTableWidgetItem* localisationItem = ui->tableWidget_4->item(row, 5);

    if (idItem) ui->lineEdit_15->setText(idItem->text());
    if (nomItem) ui->lineEdit_16->setText(nomItem->text());
    if (typeItem) {
        // Set comboBox to match the type from database
        QString typeText = typeItem->text();
        int index = ui->equipmentComboBox->findText(typeText);
        if (index >= 0) {
            ui->equipmentComboBox->setCurrentIndex(index);
        } else {
            ui->equipmentComboBox->setCurrentIndex(0); // Default to first item if not found
        }
    }

    // Gérer les radio buttons pour état
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

    // Gérer les radio buttons pour localisation
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
            // Si c'est une localisation libre, l'afficher dans lineEdit_18
            ui->lineEdit_18->setText(localisationItem->text());
        }
    }
}

void MainWindow::setMaterielFormMode(bool edit)
{
    m_materielEditMode = edit;
    if (edit) {
        ui->toolButton_31->setText("Modifier");
        ui->lineEdit_15->setEnabled(false); // ID_MATERIEL ne peut pas être modifié
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

// ===============================
//  AJOUTER / MODIFIER MATERIEL
// ===============================
void MainWindow::on_toolButton_31_clicked()
{
    // Contrôles de saisie
    const QString idT = ui->lineEdit_15->text().trimmed();
    const QString nomT = ui->lineEdit_16->text().trimmed();
    const QString typeT = ui->equipmentComboBox->currentText().trimmed();

    // Vérifier qu'un état est sélectionné
    bool etatSelected = ui->radioButton_18->isChecked() ||
                        ui->radioButton_19->isChecked() ||
                        ui->radioButton_20->isChecked() ||
                        ui->radioButton_21->isChecked();

    // Vérifier qu'une localisation est sélectionnée ou saisie
    bool localisationSelected = ui->radioButton_22->isChecked() ||
                                ui->radioButton_23->isChecked() ||
                                ui->radioButton_24->isChecked() ||
                                !ui->lineEdit_18->text().trimmed().isEmpty();

    // Expressions régulières pour validation
    static const QRegularExpression reInt(R"(^\d+$)");
    static const QRegularExpression reText(R"(^[a-zA-ZÀ-ÿ\s'-]+$)"); // Lettres, espaces, apostrophe, trait d'union

    // Vérification des champs obligatoires
    if (idT.isEmpty() || nomT.isEmpty() || typeT.isEmpty() || !etatSelected || !localisationSelected) {
        QMessageBox::warning(this, "Validation", "Tous les champs sont obligatoires.");
        return;
    }

    // Validation ID_MATERIEL: doit être un nombre de exactement 3 chiffres
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

    // Validation Nom: lettres seulement
    if (!reText.match(nomT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le nom doit contenir uniquement des lettres.");
        ui->lineEdit_16->setFocus();
        return;
    }

    // Validation Type: lettres seulement
    if (!reText.match(typeT).hasMatch()) {
        QMessageBox::warning(this, "Validation", "Le type doit contenir uniquement des lettres.");
        ui->equipmentComboBox->setFocus();
        return;
    }

    // Vérification de l'unicité de l'ID_MATERIEL pour les nouveaux matériels
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
        // Mode Ajout
        if (m.ajouter()) {
            clearMaterielForm();
            refreshMaterielGrid();
        }
    } else {
        // Mode Modification
        if (m.modifier(m.getId(), m.getNom(), m.getType(), m.getEtat(), m.getLocalisation())) {
            setMaterielFormMode(false);
            refreshMaterielGrid();
        }
    }
}

// ===============================
//  AFFICHER MATERIEL
// ===============================
void MainWindow::on_toolButton_33_clicked()
{
    refreshMaterielGrid();
}

// ===============================
//  SUPPRIMER MATERIEL
// ===============================
void MainWindow::on_toolButton_35_clicked()
{
    // Récupérer la ligne sélectionnée dans le tableau
    int currentRow = ui->tableWidget_4->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Suppression", "Sélectionne une ligne dans le tableau pour supprimer un matériel.");
        return;
    }

    // Récupérer l'ID_MATERIEL depuis la colonne 1 de la ligne sélectionnée
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
    }
}

// ===============================
//  ÉDITER MATERIEL (remplit le formulaire)
// ===============================
void MainWindow::on_toolButton_36_clicked()
{
    // Rechercher matériel par ID
    QString searchId = ui->lineEdit_18->text().trimmed();

    if (searchId.isEmpty()) {
        QMessageBox::warning(this, "Recherche", "Veuillez saisir un ID à rechercher.");
        return;
    }

    // Créer une instance de Materiel pour utiliser la méthode de recherche
    Materiel materiel;
    materiel.chercherParId(ui->tableWidget_4, searchId);

    qDebug() << "[Materiel Search] Recherche effectuée pour ID:" << searchId;
}

// Trier les matériels par etat ou type
void MainWindow::on_comboBox_4_currentTextChanged(const QString &text)
{
    if (text.isEmpty()) return;

    qDebug() << "[Materiel Sort] Tri par:" << text;

    // Créer une instance de Materiel pour utiliser la méthode de tri
    Materiel materiel;
    materiel.afficherTrié(ui->tableWidget_4, text);
}

// Annuler le formulaire matériel
void MainWindow::on_toolButton_34_clicked()
{
    // Vider tous les champs du formulaire matériel
    clearMaterielForm();

    // Désactiver le mode édition
    setMaterielFormMode(false);

    qDebug() << "[Materiel Cancel] Formulaire annulé et vidé";
}

// ==============================================
// SPONSOR CRUD OPERATIONS
// ==============================================

// Validation helper prototypes (defined later)
static bool isValidEmail(const QString &email);
static bool isAlphaName(const QString &s);
static bool isValidId8Digits(const QString &s);

// Ajouter sponsor
void MainWindow::on_toolButton_11_clicked()
{
    // Read fields from form
    Sponsor sponsor = readSponsorForm();

    // Validation: id (8 digits), nom (letters only), contact (valid email)
    QString id = ui->lineEdit_6 ? ui->lineEdit_6->text().trimmed() : "";
    QString nom = ui->lineEdit_7 ? ui->lineEdit_7->text().trimmed() : "";
    QString contact = ui->lineEdit_2 ? ui->lineEdit_2->text().trimmed() : "";

    if (!isValidId8Digits(id)) {
        QMessageBox::warning(this, "Validation", "L'ID doit contenir exactement 8 chiffres.");
        if (ui->lineEdit_6) ui->lineEdit_6->setFocus();
        return;
    }
    if (!isAlphaName(nom)) {
        QMessageBox::warning(this, "Validation", "Le nom doit contenir uniquement des lettres et espaces.");
        if (ui->lineEdit_7) ui->lineEdit_7->setFocus();
        return;
    }
    if (!isValidEmail(contact)) {
        QMessageBox::warning(this, "Validation", "Le contact doit être une adresse email valide.");
        if (ui->lineEdit_2) ui->lineEdit_2->setFocus();
        return;
    }

    // Determine if we're in edit mode (row selected) or add mode
    int currentRow = ui->tableWidget_2->currentRow();
    bool isEditMode = (currentRow >= 0);
    QString originalId = "";

    if (isEditMode) {
        // Get original ID from selected row
        originalId = ui->tableWidget_2->item(currentRow, 0) ? ui->tableWidget_2->item(currentRow, 0)->text() : "";
    }

    // Check ID uniqueness (only if adding new or changing ID in edit mode)
    if (!isEditMode || (isEditMode && id != originalId)) {
        QString existingNom, existingType, existingContact;
        QDate existingDateDebut, existingDateFin;
        if (Sponsor::rechercherParId(id, existingNom, existingType, existingDateDebut, existingDateFin, existingContact)) {
            QMessageBox::warning(this, "Validation", QString("Un sponsor avec l'ID %1 existe déjà.").arg(id));
            if (ui->lineEdit_6) ui->lineEdit_6->setFocus();
            return;
        }
    }

    bool success;
    QString operation;

    if (isEditMode) {
        // Mode modification
        success = sponsor.modifier();
        operation = "modifié";
    } else {
        // Mode ajout
        success = sponsor.ajouter();
        operation = "ajouté";
    }

    if (success) {
        QMessageBox::information(this, "Succès", QString("Sponsor %1 avec succès !").arg(operation));
        refreshSponsorGrid();
        clearSponsorForm();

        // Clear selection after edit
        if (isEditMode) {
            ui->tableWidget_2->clearSelection();
        }
    } else {
        QMessageBox::critical(this, "Erreur", QString("Échec de l'opération. Vérifiez les données et la connexion à la base de données."));
    }
}



// Supprimer sponsor
void MainWindow::on_toolButton_62_clicked()
{
    int currentRow = ui->tableWidget_2->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Suppression", "Sélectionne une ligne dans le tableau pour supprimer un sponsor.");
        return;
    }

    // Récupérer l'ID du sponsor depuis la première colonne
    QTableWidgetItem* idItem = ui->tableWidget_2->item(currentRow, 0);
    if (!idItem || idItem->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer l'ID du sponsor.");
        return;
    }

    QString id = idItem->text();

    // Demander confirmation
    int reply = QMessageBox::question(this, "Confirmation",
                                      QString("Êtes-vous sûr de vouloir supprimer le sponsor avec l'ID %1 ?").arg(id),
                                      QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        Sponsor sponsor;
        if (sponsor.supprimer(id)) {
            QMessageBox::information(this, "Succès", "Sponsor supprimé avec succès !");
            refreshSponsorGrid();
            clearSponsorForm();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression du sponsor.");
        }
    }
}

// Modifier sponsor (après sélection d'une ligne)
void MainWindow::on_toolButton_59_clicked()
{
    int currentRow = ui->tableWidget_2->currentRow();

    if (currentRow < 0) {
        QMessageBox::warning(this, "Modification", "Sélectionnez une ligne dans le tableau pour modifier un sponsor.");
        return;
    }

    // Simply populate the form with data from the selected row
    // User can then make changes and click the Add/Save button (toolButton_11) to save
    populateSponsorFormFromRow(currentRow);

    // Disable ID field to prevent modification of primary key
    if (ui->lineEdit_6) {
        ui->lineEdit_6->setReadOnly(true);
        ui->lineEdit_6->setStyleSheet("QLineEdit { background-color: #f0f0f0; }");
    }

    // Change button text to indicate edit mode
    if (ui->toolButton_11) {
        ui->toolButton_11->setText("Modifier");
    }



    qDebug() << "[Sponsor Edit] Formulaire rempli pour modification, ID désactivé, bouton changé";
}

// Annuler formulaire sponsor (clear form)
void MainWindow::on_toolButton_12_clicked()
{
    // Vider tous les champs du formulaire sponsor
    clearSponsorForm();

    // Désactiver le mode édition
    setSponsorFormMode(false);

    qDebug() << "[Sponsor Cancel] Formulaire annulé et vidé";
}

// ==============================================
// SPONSOR HELPER METHODS
// ==============================================

void MainWindow::setupTabSponsor()
{
    // Configuration du tableau sponsor
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_2->setAlternatingRowColors(true);
    ui->tableWidget_2->setSortingEnabled(false);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Initialize sort comboBox
    if (ui->comboBox_5) {
        ui->comboBox_5->clear();
        ui->comboBox_5->addItem("Date Début ");
        ui->comboBox_5->addItem("Date Fin ");
        ui->comboBox_5->setCurrentIndex(0);
    }

    // Initialize table with data
    refreshSponsorGrid();

    qDebug() << "[SetupTabSponsor] Configuration terminée avec options de tri";
}

// ----------------- Sponsor validation helpers -----------------
static bool isValidEmail(const QString &email)
{
    if (email.trimmed().isEmpty()) return false;
    static const QRegularExpression re(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    return re.match(email.trimmed()).hasMatch();
}

static bool isAlphaName(const QString &s)
{
    if (s.trimmed().isEmpty()) return false;
    static const QRegularExpression re(QStringLiteral("^[\\p{L} '\\-]+$"));
    return re.match(s.trimmed()).hasMatch();
}

static bool isValidId8Digits(const QString &s)
{
    static const QRegularExpression re("^[0-9]{8}$");
    return re.match(s.trimmed()).hasMatch();
}

void MainWindow::refreshSponsorGrid()
{
    try {
        Sponsor::afficherDansTableau(ui->tableWidget_2);

        // Ensure proper column sizing
        ui->tableWidget_2->resizeColumnsToContents();
        ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);

        qDebug() << "[RefreshSponsorGrid] Tableau sponsor rafraîchi avec" << ui->tableWidget_2->rowCount() << "lignes";
    } catch (...) {
        QMessageBox::critical(this, "Erreur", "Erreur lors du rafraîchissement du tableau des sponsors.");
        qDebug() << "[RefreshSponsorGrid] Erreur lors du rafraîchissement";
    }
}

Sponsor MainWindow::readSponsorForm() const
{
    // Map sponsor form UI fields to Sponsor object
    QString id = ui->lineEdit_6 ? ui->lineEdit_6->text().trimmed() : "";
    QString nom = ui->lineEdit_7 ? ui->lineEdit_7->text().trimmed() : "";
    QString type = ui->comboBox_2 ? ui->comboBox_2->currentText() : "";
    // details field is not present separately in the form; leave empty for now
    QString details = "";
    QDate dateDebut = ui->dateEdit_3 ? ui->dateEdit_3->date() : QDate::currentDate();
    QDate dateFin = ui->dateEdit_4 ? ui->dateEdit_4->date() : QDate::currentDate();
    QString contact = ui->lineEdit_2 ? ui->lineEdit_2->text().trimmed() : "";

    return Sponsor(id, nom, type, details, dateDebut, dateFin, contact);
}

Sponsor MainWindow::readSponsorFormFromRow(int row) const
{
    if (row < 0 || row >= ui->tableWidget_2->rowCount()) {
        return Sponsor(); // Return empty sponsor if invalid row
    }

    // Récupérer les données depuis le tableau (columns: ID, Nom, Type, Date Debut, Date Fin, Contact)
    QString id = ui->tableWidget_2->item(row, 0) ? ui->tableWidget_2->item(row, 0)->text() : "";
    QString nom = ui->tableWidget_2->item(row, 1) ? ui->tableWidget_2->item(row, 1)->text() : "";
    QString type = ui->tableWidget_2->item(row, 2) ? ui->tableWidget_2->item(row, 2)->text() : "";
    // DETAILS column removed from table view; keep details empty
    QString details = "";

    QDate dateDebut = QDate::currentDate();
    if (ui->tableWidget_2->item(row, 3)) {
        dateDebut = QDate::fromString(ui->tableWidget_2->item(row, 3)->text(), "dd/MM/yyyy");
        if (!dateDebut.isValid()) dateDebut = QDate::currentDate();
    }
    QDate dateFin = QDate::currentDate();
    if (ui->tableWidget_2->item(row, 4)) {
        dateFin = QDate::fromString(ui->tableWidget_2->item(row, 4)->text(), "dd/MM/yyyy");
        if (!dateFin.isValid()) dateFin = QDate::currentDate();
    }

    QString contact = ui->tableWidget_2->item(row, 5) ? ui->tableWidget_2->item(row, 5)->text() : "";

    return Sponsor(id, nom, type, details, dateDebut, dateFin, contact);
}

void MainWindow::clearSponsorForm()
{
    if (ui->lineEdit_6) {
        ui->lineEdit_6->clear(); // id
        ui->lineEdit_6->setReadOnly(false); // Re-enable for new entries
        ui->lineEdit_6->setStyleSheet(""); // Remove disabled styling
    }
    if (ui->comboBox_2) ui->comboBox_2->setCurrentIndex(0); // type
    if (ui->lineEdit_7) ui->lineEdit_7->clear(); // nom
    if (ui->dateEdit_3) ui->dateEdit_3->setDate(QDate::currentDate()); // date debut
    if (ui->dateEdit_4) ui->dateEdit_4->setDate(QDate::currentDate()); // date fin
    if (ui->lineEdit_2) ui->lineEdit_2->clear(); // contact

    // Reset button text to 'Ajouter' for add mode
    if (ui->toolButton_11) {
        ui->toolButton_11->setText("Ajouter");
    }

    // Clear table selection
    if (ui->tableWidget_2) {
        ui->tableWidget_2->clearSelection();
    }

    qDebug() << "[ClearSponsorForm] Formulaire sponsor vidé, ID réactivé, mode ajout";
}

void MainWindow::populateSponsorFormFromRow(int row)
{
    if (row < 0 || row >= ui->tableWidget_2->rowCount()) return;
    // Récupérer les données de la ligne et remplir les champs UI
    QTableWidgetItem* idItem = ui->tableWidget_2->item(row, 0);
    QTableWidgetItem* nomItem = ui->tableWidget_2->item(row, 1);
    QTableWidgetItem* typeItem = ui->tableWidget_2->item(row, 2);
    QTableWidgetItem* dateDebutItem = ui->tableWidget_2->item(row, 3);
    QTableWidgetItem* dateFinItem = ui->tableWidget_2->item(row, 4);
    QTableWidgetItem* contactItem = ui->tableWidget_2->item(row, 5);

    if (idItem && ui->lineEdit_6) ui->lineEdit_6->setText(idItem->text());
    if (nomItem && ui->lineEdit_7) ui->lineEdit_7->setText(nomItem->text());
    if (typeItem && ui->comboBox_2) {
        int idx = ui->comboBox_2->findText(typeItem->text());
        if (idx >= 0) ui->comboBox_2->setCurrentIndex(idx);
    }
    if (dateDebutItem && ui->dateEdit_3) ui->dateEdit_3->setDate(QDate::fromString(dateDebutItem->text(), "dd/MM/yyyy"));
    if (dateFinItem && ui->dateEdit_4) ui->dateEdit_4->setDate(QDate::fromString(dateFinItem->text(), "dd/MM/yyyy"));
    if (contactItem && ui->lineEdit_2) ui->lineEdit_2->setText(contactItem->text());

    qDebug() << "[PopulateSponsorForm] Formulaire rempli depuis la ligne" << row;
}

void MainWindow::setSponsorFormMode(bool edit)
{
    m_sponsorEditMode = edit;

    // TODO: Update button text based on mode
    // if (edit) {
    //     ui->toolButton_60->setText("Modifier");
    // } else {
    //     ui->toolButton_60->setText("Ajouter");
    // }

    qDebug() << "[SetSponsorFormMode] Mode édition:" << edit;
}

// ===============================
//  RECHERCHE ET TRI SPONSOR
// ===============================
void MainWindow::searchSponsorById()
{
    if (!ui->lineEdit_8) return;

    QString searchId = ui->lineEdit_8->text().trimmed();

    if (searchId.isEmpty()) {
        // If search field is empty, show all sponsors
        refreshSponsorGrid();
        return;
    }

    // Search for sponsor by ID
    QString nom, type, contact;
    QDate dateDebut, dateFin;

    if (Sponsor::rechercherParId(searchId, nom, type, dateDebut, dateFin, contact)) {
        // Found - display only this sponsor
        ui->tableWidget_2->clear();
        ui->tableWidget_2->setRowCount(1);

        QStringList headers = {"ID", "Nom", "Type", "Date Début", "Date Fin", "Contact"};
        ui->tableWidget_2->setColumnCount(headers.size());
        ui->tableWidget_2->setHorizontalHeaderLabels(headers);

        // Fill the single row with found data
        ui->tableWidget_2->setItem(0, 0, new QTableWidgetItem(searchId));
        ui->tableWidget_2->setItem(0, 1, new QTableWidgetItem(nom));
        ui->tableWidget_2->setItem(0, 2, new QTableWidgetItem(type));
        ui->tableWidget_2->setItem(0, 3, new QTableWidgetItem(dateDebut.toString("dd/MM/yyyy")));
        ui->tableWidget_2->setItem(0, 4, new QTableWidgetItem(dateFin.toString("dd/MM/yyyy")));
        ui->tableWidget_2->setItem(0, 5, new QTableWidgetItem(contact));

        // Center align all cells
        for (int col = 0; col < headers.size(); ++col) {
            ui->tableWidget_2->item(0, col)->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->item(0, col)->setFlags(ui->tableWidget_2->item(0, col)->flags() & ~Qt::ItemIsEditable);
        }

        ui->tableWidget_2->resizeColumnsToContents();
        ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);

        QMessageBox::information(this, "Recherche", QString("Sponsor avec l'ID %1 trouvé.").arg(searchId));
    } else {
        QMessageBox::information(this, "Recherche", QString("Aucun sponsor trouvé avec l'ID %1.").arg(searchId));
        // Still show empty table with headers
        ui->tableWidget_2->clear();
        ui->tableWidget_2->setRowCount(0);
        QStringList headers = {"ID", "Nom", "Type", "Date Début", "Date Fin", "Contact"};
        ui->tableWidget_2->setColumnCount(headers.size());
        ui->tableWidget_2->setHorizontalHeaderLabels(headers);
    }
}

void MainWindow::sortSponsors()
{
    if (!ui->comboBox_5) return;

    QString sortOption = ui->comboBox_5->currentText();
    QString orderBy;

    if (sortOption.contains("Date Début")) {
        orderBy = "DATE_DEBUT";
    } else if (sortOption.contains("Date Fin")) {
        orderBy = "DATE_FIN";
    }

    // Determine if ascending or descending
    QString direction = "ASC";

    // Execute custom sorted query
    QSqlQuery query(QString("SELECT ID_SPONSOR, NOM, TYPE, DATE_DEBUT, DATE_FIN, CONTACT FROM ABIR.SPONSOR ORDER BY %1 %2").arg(orderBy, direction));

    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);

    // Configuration des colonnes
    QStringList headers = {"ID", "Nom", "Type", "Date Début", "Date Fin", "Contact"};
    ui->tableWidget_2->setColumnCount(headers.size());
    ui->tableWidget_2->setHorizontalHeaderLabels(headers);

    // Remplissage des données
    int row = 0;
    while (query.next()) {
        ui->tableWidget_2->insertRow(row);

        for (int col = 0; col < headers.size(); ++col) {
            QString text = query.value(col).toString();

            // Formater les dates (col 3 DATE_DEBUT, col 4 DATE_FIN)
            if (col == 3 || col == 4) {
                QDate date = query.value(col).toDate();
                text = date.isValid() ? date.toString("dd/MM/yyyy") : "";
            }

            QTableWidgetItem* item = new QTableWidgetItem(text);
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tableWidget_2->setItem(row, col, item);
        }
        row++;
    }

    ui->tableWidget_2->resizeColumnsToContents();
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);

    qDebug() << "[SortSponsors] Tableau trié par:" << orderBy << direction << "(" << row << "lignes)";
}

// ===============================
//  HANDLERS POUR RECHERCHE ET TRI
// ===============================
void MainWindow::on_toolButton_9_clicked()
{
    searchSponsorById();
}

void MainWindow::on_toolButton_17_clicked()
{
    // Display all sponsors (refresh grid)
    refreshSponsorGrid();

    // Clear search field
    if (ui->lineEdit_8) {
        ui->lineEdit_8->clear();
    }

    // Reset sort to default (ID ascending)
    if (ui->comboBox_5) {
        ui->comboBox_5->setCurrentIndex(0);
    }

    QMessageBox::information(this, "Affichage", "Tous les sponsors sont maintenant affichés.");
    qDebug() << "[DisplayAll] Tous les sponsors affichés";
}

void MainWindow::on_comboBox_5_currentTextChanged(const QString &text)
{
    Q_UNUSED(text);
    sortSponsors();
}

// Per-row edit buttons removed; editing uses selection + `toolButton_59`.
