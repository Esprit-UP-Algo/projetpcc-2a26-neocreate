#include "staff.h"
#include "staffsql.h"  // CHANGÉ EN staffsql.h
#include <QMessageBox>
#include <QRegularExpression>
#include <QFileDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QHeaderView>
#include <QRadioButton>
#include <QPrinter>
#include <QPainter>
#include <QPageLayout>
#include <QTimer>
#include <QToolButton>
Staff::Staff()
{
    ui_id = nullptr;
    ui_nom = nullptr;
    ui_prenom = nullptr;
    ui_poste = nullptr;
    ui_tel = nullptr;
    ui_email = nullptr;
    ui_pass = nullptr;
    ui_radio1 = nullptr;
    ui_radio2 = nullptr;
    ui_radio3 = nullptr;
    ui_table_ajout_S = nullptr;
    ui_trier_e = nullptr;
    ui_taper_e = nullptr;
    currId = "";
    sqls = new StaffSQL(this);  // CHANGÉ EN StaffSQL
    validationActive = true;
    m_isProgrammaticChange = false;
}



// ---------- VALIDATION ----------
bool Staff::verifS(const QString& id, const QString& nom, const QString& prenom,
                   const QString& poste, const QString& tel, const QString& email,
                   const QString& pass, const QString& competence)
{
    if(!verifId(id)) {
        QMessageBox::warning(nullptr, "Erreur", "ID invalide");
        return false;
    }
    if(!verifNomPrenom(nom, prenom)) {
        QMessageBox::warning(nullptr, "Erreur", "Nom ou prénom invalide");
        return false;
    }
    if(!verifPoste(poste)) {
        QMessageBox::warning(nullptr, "Erreur",
                             "Poste invalide.");
        return false;
    }
    if(!verifTel(tel)) {
        QMessageBox::warning(nullptr, "Erreur", "Téléphone invalide");
        return false;
    }
    if(!verifEmail(email)) {
        return false;
    }
    if(!verifPass(pass)) {
        return false;
    }
    if(competence.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez sélectionner une compétence");
        return false;
    }
    return true;
}

bool Staff::verifId(const QString& id)
{
    if(id.isEmpty()) return false;
    static QRegularExpression pattern("^\\d+$");
    return pattern.match(id).hasMatch();
}

bool Staff::verifNomPrenom(const QString& nom, const QString& prenom)
{
    if(nom.isEmpty() || prenom.isEmpty()) return false;
    static QRegularExpression pattern("^[A-Za-z]+$");
    return pattern.match(nom).hasMatch() && pattern.match(prenom).hasMatch();
}

bool Staff::verifTel(const QString& tel)
{
    QString t = tel;
    t = t.trimmed();
    t.remove(" ");
    static QRegularExpression pattern("^[2579]\\d{7}$");
    return pattern.match(t).hasMatch();
}

bool Staff::verifPoste(const QString& poste)
{
    if(poste.isEmpty()) return false;

    QStringList postesAutorises = {
        "responsable de createur",
        "responsable de sponsor",
        "responsable d'employe",
        "responsable de projet",
        "responsable de client",
        "responsable de materiel"
    };

    for(const QString& posteAutorise : postesAutorises) {
        if(poste.trimmed().toLower() == posteAutorise.toLower()) {
            return true;
        }
    }
    return false;
}

bool Staff::verifPass(const QString& pass)
{
    if(pass.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Mot de passe vide");
        return false;
    }
    if(pass.length() < 4) {
        QMessageBox::warning(nullptr, "Erreur", "Le mot de passe doit contenir au moins 4 caractères");
        return false;
    }
    return true;
}

bool Staff::verifEmail(const QString& email)
{
    if(email.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Email vide");
        return false;
    }
    static QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if(!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(nullptr, "Erreur",
                             "Format d'email invalide.\n"
                             "Exemples valides:\n"
                             "- exemple@domain.com\n"
                             "- nom.prenom@entreprise.org\n"
                             "- user123@mail.co.uk");
        return false;
    }
    return true;
}
bool Staff::getCompetence(const QString& competence)
{
    QStringList competencesValides = {
        "Débutant", "Intermédiaire", "Avancé",
        "debutant", "intermediaire", "avance",
        "Debutant", "Intermediaire", "Avance"
    };

    bool isValid = competencesValides.contains(competence, Qt::CaseInsensitive);

    if (!isValid) {
        qDebug() << "❌ Compétence invalide:" << competence;
    }

    return isValid;
}

// ---------- INITIALISATION ----------
void Staff::initS(QLineEdit* id, QLineEdit* nom, QLineEdit* prenom, QComboBox* poste,
                  QLineEdit* tel, QLineEdit* email, QLineEdit* pass,
                  QRadioButton* radio1, QRadioButton* radio2, QRadioButton* radio3)
{
    ui_id = id;
    ui_nom = nom;
    ui_prenom = prenom;
    ui_poste = poste;
    ui_tel = tel;
    ui_email = email;
    ui_pass = pass;
    ui_radio1 = radio1;
    ui_radio2 = radio2;
    ui_radio3 = radio3;
ui_poste->clear(); // Vider d'abord
    // Remplir le comboBox avec les postes autorisés
    if(ui_poste->count() == 0) {
        ui_poste->addItem(""); // Premier élément vide
        ui_poste->addItem("responsable de createur");
        ui_poste->addItem("responsable de sponsor");
        ui_poste->addItem("responsable d'employe");
        ui_poste->addItem("responsable de projet");
        ui_poste->addItem("responsable de client");
        ui_poste->addItem("responsable de materiel");
    }
}

// ---------- TABLE ----------
void Staff::affTab(QTableWidget *table)
{
    this->table = table;

    QSqlQuery query("SELECT ID_STAFF, NOM_STAFF, PRENOM_STAFF, POSTE_STAFF, TEL_STAFF, EMAIL_STAFF, PASS_STAFF, COMPETENCE_STAFF FROM EMPLOYE");

    table->setColumnCount(8);
    table->setHorizontalHeaderLabels(QStringList()
                                     << "ID"
                                     << "Nom"
                                     << "Prénom"
                                     << "Poste"
                                     << "Téléphone"
                                     << "Email"
                                     << "Mot de passe"
                                     << "Compétence");

    table->setRowCount(0);

    int row = 0;
    while (query.next())
    {
        table->insertRow(row);

        for (int j = 0; j < 8; ++j)
        {
            QString cellValue = query.value(j).toString();
            QTableWidgetItem *item = new QTableWidgetItem(cellValue);
            item->setTextAlignment(Qt::AlignCenter);

            // Empêcher la modification de la colonne ID
            if (j == 0)
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);

            table->setItem(row, j, item);
        }
        row++;
    }

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::AllEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectItems);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(table, &QTableWidget::cellClicked, this, &Staff::tabClick);
    refTab();
}

void Staff::refTab()
{
    qDebug() << "Staff::refTab() appelé";

    if(sqls && table) {
        m_isProgrammaticChange = true;
        sqls->refTab(table);
        m_isProgrammaticChange = false;
    } else {
        qDebug() << "❌ Erreur: StaffSQL ou Table non initialisé";

    }
}

// ---------- ACTIONS ----------
void Staff::initTab(QTableWidget *tab_staff)
{
    this->ui_tab_staff= tab_staff;  // Si vous utilisez ce nom
    this->table = tab_staff;

    qDebug() << "Initialisation du tableau...";

    // Configuration des colonnes
    table->setColumnCount(8);
    table->setHorizontalHeaderLabels(QStringList()
                                     << "ID"
                                     << "Nom"
                                     << "Prénom"
                                     << "Poste"
                                     << "Téléphone"
                                     << "Email"
                                     << "Mot de passe"
                                     << "Compétence");

    // Configuration de l'apparence
    table->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    table->setItemDelegateForColumn(0, new ReadOnlyDelegate(this)); // Voir étape 2
    table->setSelectionBehavior(QAbstractItemView::SelectRows); // Sélection par ligne
    table->setSelectionMode(QAbstractItemView::SingleSelection); // Une seule sélection
    table->setFocusPolicy(Qt::NoFocus);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Redimensionnement automatique

    // Style optionnel pour mieux voir les données
    table->setAlternatingRowColors(false);
    //table->setStyleSheet("QTableWidget { alternate-background-color: #f0f0f0; }");

    // Connecter le clic sur une ligne
    connect(table, &QTableWidget::cellClicked, this, &Staff::tabClick);
    connect(table, &QTableWidget::cellChanged, this, &Staff::onCellChanged);

    qDebug() << "Configuration du tableau terminée";

    // CHARGEMENT IMMÉDIAT DES DONNÉES
    refTab();
}
void Staff::onCellChanged(int row, int column)
{
    // ✅ IGNORER LES MODIFICATIONS PROGRAMMATIQUES
    if (m_isProgrammaticChange) {
        return;
    }

    if (!table || row < 0 || row >= table->rowCount()) {
        return;
    }

    QTableWidgetItem* item = table->item(row, column);
    if (!item) {
        return;
    }

    QString newValue = item->text().trimmed();

    qDebug() << "=== Modification détectée ===";
    qDebug() << "Ligne:" << row << "Colonne:" << column << "Nouvelle valeur:" << newValue;

    // ✅ EMPÊCHER LA MODIFICATION DE L'ID (colonne 0)
    if (column == 0) {
        qDebug() << "❌ Modification ID interdite";

        // Restaurer immédiatement l'ancienne valeur
        m_isProgrammaticChange = true;
        if (!currId.isEmpty()) {
            item->setText(currId);
        }
        m_isProgrammaticChange = false;

        QMessageBox::warning(nullptr, "Modification interdite", "L'ID ne peut pas être modifié");
        return;
    }

    // ✅ VALIDATION DE LA NOUVELLE VALEUR
    bool isValid = true;
    QString errorMessage;
    QString columnName;

    switch(column) {
    case 1: // Nom
        isValid = verifNomPrenom(newValue, "dummy");
        columnName = "Nom";
        if (!isValid) errorMessage = "Le nom doit contenir seulement des lettres (a-z, A-Z)";
        break;

    case 2: // Prénom
        isValid = verifNomPrenom("dummy", newValue);
        columnName = "Prénom";
        if (!isValid) errorMessage = "Le prénom doit contenir seulement des lettres (a-z, A-Z)";
        break;

    case 3: // Poste
        isValid = verifPoste(newValue);
        columnName = "Poste";
        if (!isValid) errorMessage = "Poste invalide. Choisissez parmi la liste déroulante.";
        break;

    case 4: // Téléphone
        isValid = verifTel(newValue);
        columnName = "Téléphone";
        if (!isValid) errorMessage = "Le téléphone doit:\n- Commencer par 2, 5, 7 ou 9\n- Contenir 8 chiffres\n- Exemple: 50123456";
        break;

    case 5: // Email
        isValid = verifEmail(newValue);
        columnName = "Email";
        if (!isValid) errorMessage = "Format d'email invalide.\nExemple: exemple@domain.com";
        break;

    case 6: // Mot de passe
        isValid = verifPass(newValue);
        columnName = "Mot de passe";
        if (!isValid) errorMessage = "Le mot de passe doit contenir au moins 4 caractères";
        break;

    case 7: // Compétence
        isValid = getCompetence(newValue);
        columnName = "Compétence";
        if (!isValid) errorMessage = "Compétence invalide.\nChoisissez: Débutant, Intermédiaire ou Avancé";
        break;

    default:
        return;
    }

    // ✅ GESTION EN CAS D'ERREUR
    if (!isValid) {
        qDebug() << "❌ Validation échouée - Restauration de la valeur initiale";

        // Restaurer la valeur depuis la base de données
        restaurerValeurOriginale(row, column);

        // Afficher le message d'erreur
        QMessageBox::warning(nullptr, "Erreur de saisie",
                             "Erreur dans la colonne '" + columnName + "':\n" + errorMessage);

    } else {
        qDebug() << "✅ Validation réussie - Sauvegarde en cours";

        // ✅ SAUVEGARDER DANS LA BASE (seulement si valide)
        sauvegarderModification(row, column, newValue);
    }
}

// ✅ NOUVELLE MÉTHODE POUR RESTAURER LA VALEUR ORIGINALE
void Staff::restaurerValeurOriginale(int row, int column)
{
    if (!table || row < 0) return;

    QString id = table->item(row, 0)->text();
    if (id.isEmpty()) return;

    QString columnDB;
    switch(column) {
    case 1: columnDB = "NOM_STAFF"; break;
    case 2: columnDB = "PRENOM_STAFF"; break;
    case 3: columnDB = "POSTE_STAFF"; break;
    case 4: columnDB = "TEL_STAFF"; break;
    case 5: columnDB = "EMAIL_STAFF"; break;
    case 6: columnDB = "PASS_STAFF"; break;
    case 7: columnDB = "COMPETENCE_STAFF"; break;
    default: return;
    }

    // Désactiver les signaux pour éviter les boucles
    m_isProgrammaticChange = true;
    table->blockSignals(true);

    QSqlQuery query;
    query.prepare("SELECT " + columnDB + " FROM EMPLOYE WHERE ID_STAFF = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        QString originalValue = query.value(0).toString();
        QTableWidgetItem* item = table->item(row, column);
        if (item) {
            item->setText(originalValue);
            qDebug() << "🔄 Valeur restaurée:" << originalValue;
        }
    } else {
        // Si échec, recharger tout le tableau
        refTab();
    }

    // Réactiver les signaux
    table->blockSignals(false);
    m_isProgrammaticChange = false;
}
//✅ NOUVELLE MÉTHODE pour restaurer la valeur depuis la BD
void Staff::restaurerValeurDepuisBD(int row, int column)
{
    if (!table || row < 0) return;

    QString id = table->item(row, 0)->text();
    if (id.isEmpty()) return;

    QString columnDB;
    switch(column) {
    case 1: columnDB = "NOM_STAFF"; break;
    case 2: columnDB = "PRENOM_STAFF"; break;
    case 3: columnDB = "POSTE_STAFF"; break;
    case 4: columnDB = "TEL_STAFF"; break;
    case 5: columnDB = "EMAIL_STAFF"; break;
    case 6: columnDB = "PASS_STAFF"; break;
    case 7: columnDB = "COMPETENCE_STAFF"; break;
    default: return;
    }

    QSqlQuery query;
    query.prepare("SELECT " + columnDB + " FROM EMPLOYE WHERE ID_STAFF = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        QString originalValue = query.value(0).toString();
        QTableWidgetItem* item = table->item(row, column);
        if (item) {
            item->setText(originalValue);
        }
    } else {
        // Si échec, recharger tout le tableau
        refTab();
    }
}
QString Staff::getOriginalValueFromDB(int row, int column)
{
    if (!table || row < 0) return "";

    QString id = table->item(row, 0)->text();
    QString columnDB;

    switch(column) {
    case 1: columnDB = "NOM_STAFF"; break;
    case 2: columnDB = "PRENOM_STAFF"; break;
    case 3: columnDB = "POSTE_STAFF"; break;
    case 4: columnDB = "TEL_STAFF"; break;
    case 5: columnDB = "EMAIL_STAFF"; break;
    case 6: columnDB = "PASS_STAFF"; break;
    case 7: columnDB = "COMPETENCE_STAFF"; break;
    default: return "";
    }

    QSqlQuery query;
    query.prepare("SELECT " + columnDB + " FROM EMPLOYE WHERE ID_STAFF = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }

    return "";
}

void Staff::sauvegarderModification(int row, int column, const QString& newValue)
{
    // ✅ DÉSACTIVER LES SIGNAUX POUR ÉVITER LES BOUCLES
    m_isProgrammaticChange = true;
    table->blockSignals(true);

    if (!table || row < 0 || row >= table->rowCount()) {
        qDebug() << "❌ Erreur: Tableau non initialisé ou ligne invalide";
        table->blockSignals(false);
        m_isProgrammaticChange = false;
        return;
    }

    // Récupérer l'ID de la ligne modifiée
    QTableWidgetItem* idItem = table->item(row, 0);
    if (!idItem) {
        qDebug() << "❌ Erreur: Impossible de récupérer l'ID de la ligne" << row;
        table->blockSignals(false);
        m_isProgrammaticChange = false;
        return;
    }

    QString id = idItem->text();
    if (id.isEmpty()) {
        qDebug() << "❌ Erreur: ID vide pour la ligne" << row;
        table->blockSignals(false);
        m_isProgrammaticChange = false;
        return;
    }

    QString columnName;
    QString columnDB;

    // ✅ CORRESPONDANCE COLONNE TABLEAU → BASE DE DONNÉES
    switch(column) {
    case 1:
        columnName = "Nom";
        columnDB = "NOM_STAFF";
        break;
    case 2:
        columnName = "Prénom";
        columnDB = "PRENOM_STAFF";
        break;
    case 3:
        columnName = "Poste";
        columnDB = "POSTE_STAFF";
        break;
    case 4:
        columnName = "Téléphone";
        columnDB = "TEL_STAFF";
        break;
    case 5:
        columnName = "Email";
        columnDB = "EMAIL_STAFF";
        break;
    case 6:
        columnName = "Mot de passe";
        columnDB = "PASS_STAFF";
        break;
    case 7:
        columnName = "Compétence";
        columnDB = "COMPETENCE_STAFF";
        break;
    default:
        qDebug() << "❌ Colonne invalide:" << column;
        table->blockSignals(false);
        m_isProgrammaticChange = false;
        return;
    }

    qDebug() << "💾 Sauvegarde: ID" << id << "-" << columnDB << "=" << newValue;

    // ✅ VÉRIFICATIONS D'UNICITÉ
    bool validationSpecifique = true;
    QString erreurValidation;

    switch(column) {
    case 4: // Téléphone - vérifier unicité
    {
        QSqlQuery checkTel;
        checkTel.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE TEL_STAFF = :tel AND ID_STAFF != :id");
        checkTel.bindValue(":tel", newValue);
        checkTel.bindValue(":id", id);
        if (checkTel.exec() && checkTel.next() && checkTel.value(0).toInt() > 0) {
            validationSpecifique = false;
            erreurValidation = "Ce numéro de téléphone est déjà utilisé par un autre staff";
        }
    }
    break;

    case 5: // Email - vérifier unicité
    {
        QSqlQuery checkEmail;
        checkEmail.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE EMAIL_STAFF = :email AND ID_STAFF != :id");
        checkEmail.bindValue(":email", newValue);
        checkEmail.bindValue(":id", id);
        if (checkEmail.exec() && checkEmail.next() && checkEmail.value(0).toInt() > 0) {
            validationSpecifique = false;
            erreurValidation = "Cet email est déjà utilisé par un autre staff";
        }
    }
    break;

    case 6: // Mot de passe - vérifier unicité
    {
        QSqlQuery checkPass;
        checkPass.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE PASS_STAFF = :pass AND ID_STAFF != :id");
        checkPass.bindValue(":pass", newValue);
        checkPass.bindValue(":id", id);
        if (checkPass.exec() && checkPass.next() && checkPass.value(0).toInt() > 0) {
            validationSpecifique = false;
            erreurValidation = "Ce mot de passe est déjà utilisé par un autre staff";
        }
    }
    break;

        // ❌ SUPPRIMER le case 0 - L'ID ne devrait jamais être modifié ici
    }

    if (!validationSpecifique) {
        qDebug() << "❌ Validation spécifique échouée:" << erreurValidation;

        // Récupérer l'ancienne valeur depuis la base
        QSqlQuery getOldValue;
        getOldValue.prepare("SELECT " + columnDB + " FROM EMPLOYE WHERE ID_STAFF = :id");
        getOldValue.bindValue(":id", id);

        if (getOldValue.exec() && getOldValue.next()) {
            QString oldValue = getOldValue.value(0).toString();
            table->item(row, column)->setText(oldValue);
        } else {
            // Si échec, recharger tout le tableau
            refTab();
        }

        // ✅ RÉACTIVER LES SIGNAUX AVANT LE MESSAGE
        table->blockSignals(false);
        m_isProgrammaticChange = false;

        QMessageBox::warning(nullptr, "Erreur de sauvegarde", erreurValidation);
        return;
    }

    // ✅ MISE À JOUR DANS LA BASE DE DONNÉES
    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET " + columnDB + " = :value WHERE ID_STAFF = :id");
    query.bindValue(":value", newValue);
    query.bindValue(":id", id);

    if (query.exec()) {
        qDebug() << "✅ Sauvegarde réussie:" << columnDB << "mis à jour pour ID" << id;

        // ✅ METTRE À JOUR LES CHAMPS UI SI CETTE LIGNE EST SÉLECTIONNÉE
        if (table->currentRow() == row) {
            // Recharger les données dans les champs de saisie
            m_isProgrammaticChange = true; // Éviter les boucles
            tabClick(row, 0);
            m_isProgrammaticChange = false;
        }

    } else {
        qDebug() << "❌ Erreur sauvegarde:" << query.lastError().text();

        // Restaurer la valeur précédente dans le tableau
        QSqlQuery getOldValue;
        getOldValue.prepare("SELECT " + columnDB + " FROM EMPLOYE WHERE ID_STAFF = :id");
        getOldValue.bindValue(":id", id);

        if (getOldValue.exec() && getOldValue.next()) {
            QString oldValue = getOldValue.value(0).toString();
            table->item(row, column)->setText(oldValue);
        } else {
            refTab();
        }

        // ✅ RÉACTIVER LES SIGNAUX AVANT LE MESSAGE D'ERREUR
        table->blockSignals(false);
        m_isProgrammaticChange = false;

        QMessageBox::critical(nullptr, "Erreur de base de données",
                              "Erreur lors de la sauvegarde:\n" + query.lastError().text());
        return;
    }

    // ✅ RÉACTIVER LES SIGNAUX EN CAS DE SUCCÈS
    table->blockSignals(false);
    m_isProgrammaticChange = false;
}


void Staff::ConfS()
{
    qDebug() << "=== ConfS() appelé ===";

    if (!ui_id || !ui_nom || !ui_prenom || !ui_poste || !ui_tel ||
        !ui_email || !ui_pass || !table) {
        qDebug() << "❌ Erreur: Champs UI non initialisés";
        return;
    }

    QString id = ui_id->text().trimmed();
    QString nom = ui_nom->text().trimmed();
    QString prenom = ui_prenom->text().trimmed();
    QString poste = ui_poste->currentText().trimmed();
    QString tel = ui_tel->text().trimmed();
    QString email = ui_email->text().trimmed();
    QString pass = ui_pass->text().trimmed();
    QString competence;

    // Récupération de la compétence
    if (ui_radio1 && ui_radio1->isChecked()) {
        competence = ui_radio1->text();
    } else if (ui_radio2 && ui_radio2->isChecked()) {
        competence = ui_radio2->text();
    } else if (ui_radio3 && ui_radio3->isChecked()) {
        competence = ui_radio3->text();
    }

    qDebug() << "Données à ajouter:";
    qDebug() << "ID:" << id;
    qDebug() << "Nom:" << nom;
    qDebug() << "Prénom:" << prenom;
    qDebug() << "Poste:" << poste;
    qDebug() << "Téléphone:" << tel;
    qDebug() << "Email:" << email;
    qDebug() << "Mot de passe:" << pass;
    qDebug() << "Compétence:" << competence;

    // ✅ VALIDATION AVEC MESSAGES POUR DÉBOGUAGE
    if (id.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "ID vide");
        return;
    }
    if (nom.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Nom vide");
        return;
    }
    if (prenom.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Prénom vide");
        return;
    }
    if (competence.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Compétence non sélectionnée");
        return;
    }

    // Vérification ID existant
    QSqlQuery checkIdQuery;
    checkIdQuery.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE ID_STAFF = :id");
    checkIdQuery.bindValue(":id", id);
    if (checkIdQuery.exec() && checkIdQuery.next() && checkIdQuery.value(0).toInt() > 0) {
        QMessageBox::warning(nullptr, "Erreur", "Cet ID existe déjà");
        return;
    }

    // Validation complète
    if (!verifS(id, nom, prenom, poste, tel, email, pass, competence)) {
        qDebug() << "❌ Validation échouée";
        return;
    }

    // Insertion dans la base
    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE "
                  "(ID_STAFF, NOM_STAFF, PRENOM_STAFF, POSTE_STAFF, TEL_STAFF, EMAIL_STAFF, PASS_STAFF, COMPETENCE_STAFF) "
                  "VALUES (:id, :nom, :prenom, :poste, :tel, :email, :pass, :competence)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":tel", tel);
    query.bindValue(":email", email);
    query.bindValue(":pass", pass);
    query.bindValue(":competence", competence);

    if (query.exec()) {
        qDebug() << "✅ Insertion réussie dans la base de données";

        // Ajout dans le tableau
        int row = table->rowCount();
        table->insertRow(row);

        QStringList values = {id, nom, prenom, poste, tel, email, pass, competence};
        for(int i = 0; i < 8; i++) {
            QTableWidgetItem *item = new QTableWidgetItem(values[i]);
            item->setTextAlignment(Qt::AlignCenter);
            if (i == 0) item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            table->setItem(row, i, item);
        }

        QMessageBox::information(nullptr, "Succès", "Staff ajouté avec succès !");
        reinitS();

    } else {
        qDebug() << "❌ Erreur SQL:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur SQL",
                              "Erreur lors de l'ajout:\n" + query.lastError().text());
    }
}

void Staff::modifS()
{
    if (!table) {
        QMessageBox::warning(nullptr, "Erreur", "Tableau non initialisé");
        return;
    }

    int row = table->currentRow();
    if (row < 0) {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez sélectionner un staff à modifier.");
        return;
    }

    // Vérifier que les champs UI sont initialisés
    if (!ui_id || !ui_nom || !ui_prenom || !ui_poste || !ui_tel || !ui_email || !ui_pass) {
        QMessageBox::warning(nullptr, "Erreur", "Champs non initialisés");
        return;
    }

    // ✅ CORRECTION : Récupérer les données DEPUIS LES CHAMPS DE SAISIE (pas depuis le tableau)
    QString id = ui_id->text().trimmed();
    QString nom = ui_nom->text().trimmed();
    QString prenom = ui_prenom->text().trimmed();
    QString poste = ui_poste->currentText().trimmed();
    QString tel = ui_tel->text().trimmed();
    QString email = ui_email->text().trimmed();
    QString pass = ui_pass->text().trimmed();
    QString competence;
    if (ui_radio1 && ui_radio1->isChecked()) {
        competence = ui_radio1->text();
    } else if (ui_radio2 && ui_radio2->isChecked()) {
        competence = ui_radio2->text();
    } else if (ui_radio3 && ui_radio3->isChecked()) {
        competence = ui_radio3->text();
    }

    // Récupérer l'ancien ID depuis le tableau pour la clause WHERE
    QString oldId = table->item(row, 0)->text();

    qDebug() << "Modification - Ancien ID:" << oldId;
    qDebug() << "Nouvelles valeurs - ID:" << id << "Nom:" << nom << "Prénom:" << prenom;

    // ✅ CORRECTION : Valider les nouvelles données
    if (!verifS(id, nom, prenom, poste, tel, email, pass, competence)) {
        return;
    }

    // Vérifier si le nouveau mot de passe existe déjà pour un autre staff
    QSqlQuery checkPassQuery;
    checkPassQuery.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE PASS_STAFF = :pass AND ID_STAFF != :oldId");
    checkPassQuery.bindValue(":pass", pass);
    checkPassQuery.bindValue(":oldId", oldId);
    if (checkPassQuery.exec() && checkPassQuery.next() && checkPassQuery.value(0).toInt() > 0) {
        QMessageBox::warning(nullptr, "Erreur", "Ce mot de passe est déjà utilisé par un autre staff");
        return;
    }

    // Vérifier si le nouvel ID existe déjà pour un autre staff (si l'ID a changé)
    if (id != oldId) {
        QSqlQuery checkIdQuery;
        checkIdQuery.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE ID_STAFF = :newId");
        checkIdQuery.bindValue(":newId", id);
        if (checkIdQuery.exec() && checkIdQuery.next() && checkIdQuery.value(0).toInt() > 0) {
            QMessageBox::warning(nullptr, "Erreur", "Cet ID existe déjà pour un autre staff");
            return;
        }
    }

    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET "
                  "ID_STAFF = :newId, "
                  "NOM_STAFF = :nom, "
                  "PRENOM_STAFF = :prenom, "
                  "POSTE_STAFF = :poste, "
                  "TEL_STAFF = :tel, "
                  "EMAIL_STAFF = :email, "
                  "PASS_STAFF = :pass, "
                  "COMPETENCE_STAFF = :competence "
                  "WHERE ID_STAFF = :oldId");

    query.bindValue(":newId", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":tel", tel);
    query.bindValue(":email", email);
    query.bindValue(":pass", pass);
    query.bindValue(":competence", competence);
    query.bindValue(":oldId", oldId);

    if (query.exec()) {
        // ✅ CORRECTION : Mettre à jour le tableau avec les nouvelles valeurs
        table->item(row, 0)->setText(id);
        table->item(row, 1)->setText(nom);
        table->item(row, 2)->setText(prenom);
        table->item(row, 3)->setText(poste);
        table->item(row, 4)->setText(tel);
        table->item(row, 5)->setText(email);
        table->item(row, 6)->setText(pass);
        table->item(row, 7)->setText(competence);

        QMessageBox::information(nullptr, "Succès", "Modification réussie !");

        // Rafraîchir le tableau
        refTab();

        // Réinitialiser les champs
        reinitS();
    } else {
        QMessageBox::critical(nullptr, "Erreur SQL",
                              "Échec mise à jour : " + query.lastError().text());
    }
}

void Staff::tabClick(int row, int column)
{
    Q_UNUSED(column);
m_isProgrammaticChange = true;
    qDebug() << "=== tabClick appelé ===";
    qDebug() << "Ligne sélectionnée:" << row;

    // Vérifications de base
    if(!table) {
        qDebug() << "❌ Erreur: Table non initialisée";
        return;
    }

    if(row < 0 || row >= table->rowCount()) {
        qDebug() << "❌ Erreur: Ligne invalide - row:" << row << ", rowCount:" << table->rowCount();
        return;
    }

    // Vérifier si les pointeurs UI sont initialisés
    if(!ui_id || !ui_nom || !ui_prenom || !ui_poste || !ui_tel || !ui_email || !ui_pass) {
        qDebug() << "❌ Erreur: Pointeurs UI non initialisés";
        qDebug() << "ui_id:" << ui_id << "ui_nom:" << ui_nom << "ui_poste:" << ui_poste;
        return;
    }

    // Vérifier que tous les items existent dans la ligne
    for(int i = 0; i < table->columnCount(); i++) {
        if(!table->item(row, i)) {
            qDebug() << "❌ Erreur: Item manquant à la ligne" << row << "colonne" << i;
            // Créer un item vide pour éviter le crash
            table->setItem(row, i, new QTableWidgetItem(""));
        }
    }

    // Afficher le contenu de la ligne pour debug
    qDebug() << "Contenu de la ligne" << row << ":";
    for(int i = 0; i < table->columnCount(); i++) {
        QTableWidgetItem* item = table->item(row, i);
        if(item) {
            qDebug() << "  Colonne" << i << ":" << item->text();
        }
    }

    // Récupérer et afficher les valeurs
    QString id = table->item(row, 0)->text();
    QString nom = table->item(row, 1)->text();
    QString prenom = table->item(row, 2)->text();
    QString poste = table->item(row, 3)->text();
    QString tel = table->item(row, 4)->text();
    QString email = table->item(row, 5)->text();
    QString pass = table->item(row, 6)->text();
    QString competence = table->item(row, 7)->text();

    qDebug() << "Valeurs à charger:";
    qDebug() << "  ID:" << id;
    qDebug() << "  Nom:" << nom;
    qDebug() << "  Prénom:" << prenom;
    qDebug() << "  Poste:" << poste;

    // Charger les valeurs dans les champs UI
    currId = id;

    ui_id->setText(id);
    ui_nom->setText(nom);
    ui_prenom->setText(prenom);

    // Pour QComboBox, utiliser setCurrentText ou trouver l'index
    int posteIndex = ui_poste->findText(poste);
    if(posteIndex >= 0) {
        ui_poste->setCurrentIndex(posteIndex);
    } else {
        ui_poste->setCurrentText(poste);
    }

    ui_tel->setText(tel);
    ui_email->setText(email);
    ui_pass->setText(pass);
    if(ui_radio1 && ui_radio2 && ui_radio3) {
        // Désactiver temporairement l'auto-exclusive pour éviter les conflits
        ui_radio1->setAutoExclusive(false);
        ui_radio2->setAutoExclusive(false);
        ui_radio3->setAutoExclusive(false);

        // Décocher tous d'abord
        ui_radio1->setChecked(false);
        ui_radio2->setChecked(false);
        ui_radio3->setChecked(false);
    // Gérer les radio buttons pour la compétence
    qDebug() << "Compétence à charger:" << competence;
    qDebug() << "Radio buttons - 1:" << (ui_radio1 ? ui_radio1->text() : "null")
             << "2:" << (ui_radio2 ? ui_radio2->text() : "null")
             << "3:" << (ui_radio3 ? ui_radio3->text() : "null");
    }
    if(ui_radio1 && ui_radio1->text() == competence) {
        ui_radio1->setChecked(true);
        qDebug() << "Radio 1 sélectionné";
    }
    else if(ui_radio2 && ui_radio2->text() == competence) {
        ui_radio2->setChecked(true);
        qDebug() << "Radio 2 sélectionné";
    }
    else if(ui_radio3 && ui_radio3->text() == competence) {
        ui_radio3->setChecked(true);
        qDebug() << "Radio 3 sélectionné";
    }
    else {
        qDebug() << "❌ Aucun radio button ne correspond à la compétence:" << competence;
        // Désélectionner tous les radio buttons
        if(ui_radio1) ui_radio1->setChecked(false);
        if(ui_radio2) ui_radio2->setChecked(false);
        if(ui_radio3) ui_radio3->setChecked(false);
    }

    qDebug() << "=== tabClick terminé avec succès ===";

    // Forcer la mise à jour de l'interface
    ui_id->update();
    ui_nom->update();
    ui_prenom->update();
    m_isProgrammaticChange = false;

}
void Staff::reinitS()
{
    if(ui_id) ui_id->clear();
    if(ui_nom) ui_nom->clear();
    if(ui_prenom) ui_prenom->clear();
    if(ui_poste && ui_poste->count() > 0) ui_poste->setCurrentIndex(0);
    if(ui_tel) ui_tel->clear();
    if(ui_email) ui_email->clear();
    if(ui_pass) ui_pass->clear();
    if(ui_radio1) ui_radio1->setAutoExclusive(false);
    if(ui_radio1) ui_radio1->setChecked(false);
    if(ui_radio2) ui_radio2->setChecked(false);
    if(ui_radio3) ui_radio3->setChecked(false);
    if(ui_radio1) ui_radio1->setAutoExclusive(true);
    currId = "";
}

void Staff::suppS()
{
    if (!table) return;

    int row = table->currentRow();
    if (row < 0) {
        QMessageBox::warning(nullptr, "Erreur", "Veuillez sélectionner un staff à supprimer.");
        return;
    }

    QString id = table->item(row, 0)->text();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, "Supprimer",
                                  "Voulez-vous vraiment supprimer ce staff ?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM EMPLOYE WHERE ID_STAFF=:id");
        query.bindValue(":id", id);

        if (!query.exec()) {
            QMessageBox::critical(nullptr, "Erreur SQL", "Échec suppression : " + query.lastError().text());
            return;
        }

        table->removeRow(row);
        QMessageBox::information(nullptr, "Succès", "Staff supprimé avec succès !");
    }
}

void Staff::trierS()
{
    if(!ui_trier_e || !ui_table_ajout_S) return;
    QString critere = ui_trier_e->currentText();
    if(critere == "Trier par") { refTab(); return; }
    sqls->trierTab(ui_table_ajout_S, critere);
}

void Staff::initRechercheID(QLineEdit* lineEditD, QToolButton* toolButtonR)
{
    this->lineEditD = lineEditD;
    this->toolButtonR = toolButtonR;

    // ✅ CONNEXION DU BOUTON
    connect(toolButtonR, &QToolButton::clicked, this, &Staff::onToolButtonRClicked);

    qDebug() << "Bouton recherche ID initialisé et connecté";
}

void Staff::onToolButtonRClicked()
{
    if (!lineEditD || !table) return;

    QString idRecherche = lineEditD->text().trimmed();

    if (idRecherche.isEmpty()) {
        // ❌ PAS DE MESSAGE - On recharge tout simplement
        refTab();
        return;
    }

    // ✅ RECHERCHE DIRECTE
    QSqlQuery query;
    query.prepare("SELECT ID_STAFF, NOM_STAFF, PRENOM_STAFF, POSTE_STAFF, TEL_STAFF, EMAIL_STAFF, PASS_STAFF, COMPETENCE_STAFF "
                  "FROM EMPLOYE WHERE ID_STAFF = :id");
    query.bindValue(":id", idRecherche);

    if (query.exec()) {
        // ✅ AFFICHAGE DIRECT DANS LE TABLEAU
        table->setRowCount(0);

        int row = 0;
        while (query.next()) {
            table->insertRow(row);
            for (int j = 0; j < 8; ++j) {
                QString cellValue = query.value(j).toString();
                QTableWidgetItem *item = new QTableWidgetItem(cellValue);
                item->setTextAlignment(Qt::AlignCenter);
                if (j == 0) item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                table->setItem(row, j, item);
            }
            row++;
        }

        // ✅ SELECTION AUTOMATIQUE SI TROUVÉ
        if (row > 0) {
            table->setCurrentCell(0, 0);
            tabClick(0, 0);
        }
            // ❌ PAS DE MESSAGE "NON TROUVÉ" - On laisse le tableau vide

    }
    // ❌ PAS DE MESSAGE D'ERREUR SQL
}

void Staff::expoS()
{
    if(!ui_table_ajout_S || ui_table_ajout_S->rowCount() == 0) {
        QMessageBox::warning(nullptr, "Erreur", "Aucune donnée à exporter");
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Exporter en PDF", "", "PDF Files (*.pdf)");
    if(fileName.isEmpty()) return;

    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageOrientation(QPageLayout::Landscape);
    printer.setOutputFileName(fileName);

    QPainter painter;
    painter.begin(&printer);
    QFont font = painter.font();
    font.setPointSize(7);
    painter.setFont(font);
    int colPositions[8] = {30, 70, 130, 190, 250, 310, 370, 430};
    int y = 50;
    QStringList headers = {"ID", "Nom", "Prenom", "Poste", "Tel", "Email", "Pass", "Competence"};
    for(int col = 0; col < headers.size(); col++) painter.drawText(colPositions[col], y, headers[col]);
    y += 20;
    painter.drawLine(30, y, 520, y);
    y += 15;

    for(int row = 0; row < ui_table_ajout_S->rowCount(); ++row) {
        for(int col = 0; col < ui_table_ajout_S->columnCount(); ++col) {
            QTableWidgetItem* item = ui_table_ajout_S->item(row, col);
            if(item) painter.drawText(colPositions[col], y, item->text());
        }
        y += 15;
        if(y > 250) { printer.newPage(); y = 50; }
    }
    painter.end();
    QMessageBox::information(nullptr, "Succès", "PDF exporté avec succès");
}

void Staff::initTrier(QComboBox* trier_e)
{
    this->ui_trier_e = trier_e;
    ui_trier_e->clear();
    ui_trier_e->addItem("Trier par");
    ui_trier_e->addItem("Nom croissant");
    ui_trier_e->addItem("Nom décroissant");
    ui_trier_e->addItem("Poste croissant");
    ui_trier_e->addItem("Poste décroissant");
    connect(ui_trier_e, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &Staff::trierS);
}
void Staff::initAfficherTout(QToolButton* toolButtonAff)
{
    this->toolButtonAff = toolButtonAff;

    // Connexion du bouton
    connect(toolButtonAff, &QToolButton::clicked, this, &Staff::onToolButtonAffClicked);

    qDebug() << "Bouton afficher tout initialisé et connecté";
}

void Staff::onToolButtonAffClicked()
{
    qDebug() << "=== Bouton Afficher Tout cliqué ===";

    if (!table) {
        QMessageBox::warning(nullptr, "Erreur", "Tableau non initialisé");
        return;
    }

    // Rafraîchir tout le tableau
    refTab();

    QMessageBox::information(nullptr, "Succès", "Tous les staffs sont affichés");

    qDebug() << "Tableau rafraîchi -" << table->rowCount() << "lignes affichées";
}
void Staff::initAjouterButton(QToolButton* toolButtonAjouter)
{
    this->toolButtonAjouter = toolButtonAjouter;

    // Connexion du bouton à la méthode ConfS()
    connect(toolButtonAjouter, &QToolButton::clicked, this, &Staff::ConfS);

    qDebug() << "Bouton Ajouter initialisé et connecté";
}
