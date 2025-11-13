#include "staffsql.h"
#include "connection.h"
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QSqlError>
#include <QLineEdit>
#include <QComboBox>
#include <QSqlQuery>
#include <QTimer>
StaffSQL::StaffSQL(QObject* parent) : QObject(parent) {}

void StaffSQL::ConfS(QLineEdit* ui_id, QLineEdit* ui_nom, QLineEdit* ui_prenom,
                     QComboBox* ui_poste, QLineEdit* ui_tel, QLineEdit* ui_email,
                     QLineEdit* ui_pass, const QString& competence, QString& currID)
{
    QString id = ui_id->text();
    QString nom = ui_nom->text();
    QString prenom = ui_prenom->text();
    QString poste = ui_poste->currentText();
    QString tel = ui_tel->text();
    QString email = ui_email->text();
    QString pass = ui_pass->text();

    // CORRECTION : Utiliser Connection::createconnect() au lieu de QSqlDatabase::database()
    if(!Connection::createconnect()) {
        QMessageBox::warning(nullptr, "Erreur", "Connexion à la base de données échouée");
        return;
    }

    if(chercheID(id)) {
        QMessageBox::warning(nullptr, "Erreur", "ID existe déjà");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO EMPLOYE (ID_STAFF, NOM_STAFF, PRENOM_STAFF, POSTE_STAFF, TEL_STAFF, EMAIL_STAFF, PASS_STAFF, COMPETENCE_STAFF) "
                  "VALUES (:id, :nom, :prenom, :poste, :tel, :email, :pass, :competence)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":tel", tel);
    query.bindValue(":email", email);
    query.bindValue(":pass", pass);
    query.bindValue(":competence", competence);

    if(query.exec()) {
        QMessageBox::information(nullptr, "Succès", "Staff créé avec succès");
        currID = "";
        ui_id->clear(); ui_nom->clear(); ui_prenom->clear();
        ui_tel->clear(); ui_email->clear(); ui_pass->clear();
        ui_poste->setCurrentIndex(0);
    } else {
        QMessageBox::warning(nullptr, "Erreur", "Erreur insertion: " + query.lastError().text());
    }
}

void StaffSQL::modifS(QLineEdit* ui_id, QLineEdit* ui_nom, QLineEdit* ui_prenom,
                      QComboBox* ui_poste, QLineEdit* ui_tel, QLineEdit* ui_email,
                      QLineEdit* ui_pass, const QString& competence, QString& currID)
{
    QString id = ui_id->text();
    QString nom = ui_nom->text();
    QString prenom = ui_prenom->text();
    QString poste = ui_poste->currentText();
    QString tel = ui_tel->text();
    QString email = ui_email->text();
    QString pass = ui_pass->text();

    if(id != currID) {
        QMessageBox::warning(nullptr, "Erreur", "L'ID ne peut pas être modifié");
        return;
    }

    // CORRECTION : Utiliser Connection::createconnect()
    if(!Connection::createconnect()) {
        QMessageBox::warning(nullptr, "Erreur", "Connexion à la base de données échouée");
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE EMPLOYE SET NOM_STAFF=:nom, PRENOM_STAFF=:prenom, POSTE_STAFF=:poste, "
                  "TEL_STAFF=:tel, EMAIL_STAFF=:email, PASS_STAFF=:pass, COMPETENCE_STAFF=:competence "
                  "WHERE ID_STAFF=:id");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":tel", tel);
    query.bindValue(":email", email);
    query.bindValue(":pass", pass);
    query.bindValue(":competence", competence);

    if(!query.exec()) {
        QMessageBox::warning(nullptr, "Erreur", "Erreur modification: " + query.lastError().text());
        return;
    }

    currID = "";
    QMessageBox::information(nullptr, "Succès", "Staff modifié avec succès");
}

void StaffSQL::suppS(QString& currID, QTableWidget* table)
{
    if(currID.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur", "Sélectionnez un staff à supprimer");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(nullptr, "Confirmation",
                                                              "Voulez-vous supprimer " + currID + "?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes) {
        // CORRECTION : Utiliser Connection::createconnect()
        if(!Connection::createconnect()) {
            QMessageBox::warning(nullptr, "Erreur", "Connexion échouée");
            return;
        }

        QSqlQuery query;
        query.prepare("DELETE FROM EMPLOYE WHERE ID_STAFF=:id");
        query.bindValue(":id", currID);

        if(query.exec()) {
            QMessageBox::information(nullptr, "Succès", "Staff supprimé avec succès");
            currID = "";

            // Rafraîchir le tableau
            if(table) {
                refTab(table);
            }
        } else {
            QMessageBox::warning(nullptr, "Erreur", "Erreur suppression: " + query.lastError().text());
        }
    }
}

QString StaffSQL::tabClick(const QModelIndex &index, QLineEdit* ui_id, QLineEdit* ui_nom, QLineEdit* ui_prenom,
                           QComboBox* ui_poste, QLineEdit* ui_tel, QLineEdit* ui_email,
                           QLineEdit* ui_pass, QString& competence, QTableWidget* table)
{
    if(!table) return "";

    int row = index.row();
    if(row < 0 || row >= table->rowCount()) return "";

    QString id = table->item(row, 0)->text();

    // CORRECTION : Utiliser Connection::createconnect()
    if(!Connection::createconnect()) {
        return "";
    }

    QSqlQuery query;
    query.prepare("SELECT ID_STAFF, NOM_STAFF, PRENOM_STAFF, POSTE_STAFF, TEL_STAFF, EMAIL_STAFF, PASS_STAFF, COMPETENCE_STAFF FROM EMPOYE WHERE ID_STAFF=:id");
    query.bindValue(":id", id);

    if(query.exec() && query.next()) {
        ui_id->setText(query.value(0).toString());
        ui_nom->setText(query.value(1).toString());
        ui_prenom->setText(query.value(2).toString());
        ui_poste->setCurrentText(query.value(3).toString());
        ui_tel->setText(query.value(4).toString());
        ui_email->setText(query.value(5).toString());
        ui_pass->setText(query.value(6).toString());
        competence = query.value(7).toString();
    }

    return id;
}


void StaffSQL::refTab(QTableWidget* table)
{
    if(!table) {
        qDebug() << "Erreur: Table widget null";
        return;
    }

    qDebug() << "=== DÉBUT CHARGEMENT TABLEAU ===";

    // Connexion à la base
    if(!Connection::createconnect()) {
        qDebug() << "❌ Connexion à la base échouée";
        QMessageBox::warning(nullptr, "Erreur", "Impossible de se connecter à la base de données");
        return;
    }
    qDebug() << "✅ Connexion à la base réussie";

    // Préparer la requête
    QSqlQuery query;
    QString requete = "SELECT ID_STAFF, NOM_STAFF, PRENOM_STAFF, POSTE_STAFF, TEL_STAFF, EMAIL_STAFF, PASS_STAFF, COMPETENCE_STAFF FROM EMPLOYE";

    qDebug() << "Exécution de la requête:" << requete;

    if(!query.exec(requete)) {
        QString erreur = query.lastError().text();
        qDebug() << "❌ Erreur requête SQL:" << erreur;
        QMessageBox::critical(nullptr, "Erreur SQL", "Impossible de charger les données:\n" + erreur);
        return;
    }

    qDebug() << "✅ Requête exécutée avec succès";

    // Préparer le tableau
    table->setUpdatesEnabled(false); // Désactiver les updates pour plus de rapidité
    table->setRowCount(0); // Vider le tableau
    qDebug() << "Tableau vidé";

    // Charger les données
    int row = 0;
    while(query.next()) {
        table->insertRow(row);

        // Récupérer chaque colonne
        QString id = query.value(0).toString();
        QString nom = query.value(1).toString();
        QString prenom = query.value(2).toString();
        QString poste = query.value(3).toString();
        QString tel = query.value(4).toString();
        QString email = query.value(5).toString();
        QString pass = query.value(6).toString();
        QString competence = query.value(7).toString();

        qDebug() << "Ligne" << row << ":" << id << nom << prenom;

        // Ajouter les données au tableau
        table->setItem(row, 0, new QTableWidgetItem(id));
        table->setItem(row, 1, new QTableWidgetItem(nom));
        table->setItem(row, 2, new QTableWidgetItem(prenom));
        table->setItem(row, 3, new QTableWidgetItem(poste));
        table->setItem(row, 4, new QTableWidgetItem(tel));
        table->setItem(row, 5, new QTableWidgetItem(email));
        table->setItem(row, 6, new QTableWidgetItem(pass));
        table->setItem(row, 7, new QTableWidgetItem(competence));

        // Centrer le texte dans toutes les cellules
        for(int col = 0; col < 8; col++) {
            QTableWidgetItem* item = table->item(row, col);
            if(item) {
                item->setTextAlignment(Qt::AlignCenter);
            }
        }

        row++;
    }

    // Réactiver les updates
    table->setUpdatesEnabled(true);

    qDebug() << "=== CHARGEMENT TERMINÉ ===";
    qDebug() << "✅" << row << "lignes chargées dans le tableau";

    if(row == 0) {
        qDebug() << "ℹ️ Aucune donnée trouvée dans la table EMPLOYE";
        QMessageBox::information(nullptr, "Information", "Aucun employé trouvé dans la base de données");
    }
}

bool StaffSQL::chercheID(const QString& id, const QString& suppID)
{
    // CORRECTION : Utiliser Connection::createconnect()
    if(!Connection::createconnect()) {
        return false;
    }

    QSqlQuery checkQuery;
    if(suppID.isEmpty()) {
        checkQuery.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE ID_STAFF=:id");
        checkQuery.bindValue(":id", id);
    } else {
        checkQuery.prepare("SELECT COUNT(*) FROM EMPLOYE WHERE ID_STAFF=:id AND ID_STAFF!=:old_id");
        checkQuery.bindValue(":id", id);
        checkQuery.bindValue(":old_id", suppID);
    }

    if(checkQuery.exec() && checkQuery.next())
        return checkQuery.value(0).toInt() > 0;

    return false;
}

void StaffSQL::trierTab(QTableWidget* table, const QString& critere)
{
    if(!table) return;

    QString orderBy;
    if(critere == "Nom croissant") orderBy = "NOM_STAFF ASC";
    else if(critere == "Nom décroissant") orderBy = "NOM_STAFF DESC";
    else if(critere == "Poste croissant") orderBy = "POSTE_STAFF ASC";
    else if(critere == "Poste décroissant") orderBy = "POSTE_STAFF DESC";
    else return;

    // CORRECTION : Utiliser Connection::createconnect()
    if(!Connection::createconnect()) {
        return;
    }

    table->setRowCount(0);
    QSqlQuery query("SELECT ID_STAFF, NOM_STAFF, PRENOM_STAFF, POSTE_STAFF, TEL_STAFF, EMAIL_STAFF, PASS_STAFF, COMPETENCE_STAFF FROM EMPLOYE ORDER BY " + orderBy);

    int row = 0;
    while(query.next()) {
        table->insertRow(row);
        for(int col = 0; col < 8; ++col)
            table->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        row++;
    }
}

void StaffSQL::rech(QTableWidget* table, const QString& nom)
{
    for(int i=0; i<table->rowCount(); i++) {
        bool match = table->item(i, 1)->text().contains(nom, Qt::CaseInsensitive);
        table->setRowHidden(i, !match);
    }
}
