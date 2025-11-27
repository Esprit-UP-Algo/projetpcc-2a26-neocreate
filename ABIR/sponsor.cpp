#include "sponsor.h"
#include <QRegularExpression>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QSqlDatabase>
#include <QSqlDriver>

// Constructeurs - COMME PROJET
Sponsor::Sponsor()
{
    id = "";
    nom = "";
    type = "";
    details = "";
    dateDebut = QDate::currentDate();
    dateFin = QDate::currentDate();
    contact = "";
}

Sponsor::Sponsor(QString id, QString nom, QString type, QString details, QDate dateDebut, QDate dateFin, QString contact)
{
    this->id = id;
    this->nom = nom;
    this->type = type;
    this->details = details;
    this->dateDebut = dateDebut;
    this->dateFin = dateFin;
    this->contact = contact;
}

// ----------------- AJOUTER - COMME PROJET -----------------
bool Sponsor::ajouter()
{
    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database();
    qDebug() << "[Sponsor::ajouter] DB open:" << db.isOpen() << ", driver:" << db.driverName();

    query.prepare("INSERT INTO ABIR.SPONSOR (ID_SPONSOR, NOM, TYPE, DETAILS, DATE_DEBUT, DATE_FIN, CONTACT) "
                  "VALUES (:id, :nom, :type, :details, :dateDebut, :dateFin, :contact)");

    qDebug() << "[Sponsor::ajouter] Parameters:" 
             << "id=" << id
             << "nom=" << nom
             << "type=" << type
             << "details=" << details
             << "dateDebut=" << dateDebut.toString("yyyy-MM-dd")
             << "dateFin=" << dateFin.toString("yyyy-MM-dd")
             << "contact=" << contact;

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":details", details);
    query.bindValue(":dateDebut", dateDebut);
    query.bindValue(":dateFin", dateFin);
    query.bindValue(":contact", contact);

    // Transaction - COMME PROJET
    bool startedTx = false;
    if (db.driver() && db.driver()->hasFeature(QSqlDriver::Transactions)) {
        startedTx = db.transaction();
        qDebug() << "[Sponsor::ajouter] Transaction started:" << startedTx;
    }

    bool ok = query.exec();
    if (!ok) {
        qWarning() << "[Sponsor::ajouter] Exec failed:" << query.lastError().text();
        if (startedTx) db.rollback();
        return false;
    }

    qDebug() << "[Sponsor::ajouter] Exec success, rowsAffected=" << query.numRowsAffected();

    if (startedTx) {
        if (!db.commit()) {
            qWarning() << "[Sponsor::ajouter] Commit failed:" << db.lastError().text();
            return false;
        }
        qDebug() << "[Sponsor::ajouter] Commit success";
    }

    return true;
}

// ----------------- MODIFIER - COMME PROJET -----------------
bool Sponsor::modifier()
{
    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database();
    qDebug() << "[Sponsor::modifier] DB open:" << db.isOpen() << ", ID:" << id;

    query.prepare("UPDATE ABIR.SPONSOR SET NOM = :nom, TYPE = :type, DETAILS = :details, "
                  "DATE_DEBUT = :dateDebut, DATE_FIN = :dateFin, CONTACT = :contact "
                  "WHERE ID_SPONSOR = :id");

    qDebug() << "[Sponsor::modifier] Parameters:"
             << "id=" << id
             << "nom=" << nom
             << "type=" << type
             << "details=" << details
             << "dateDebut=" << dateDebut.toString("yyyy-MM-dd")
             << "dateFin=" << dateFin.toString("yyyy-MM-dd")
             << "contact=" << contact;

    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":details", details);
    query.bindValue(":dateDebut", dateDebut);
    query.bindValue(":dateFin", dateFin);
    query.bindValue(":contact", contact);
    query.bindValue(":id", id);

    // Transaction - COMME PROJET
    bool startedTx = false;
    if (db.driver() && db.driver()->hasFeature(QSqlDriver::Transactions)) {
        startedTx = db.transaction();
        qDebug() << "[Sponsor::modifier] Transaction started:" << startedTx;
    }

    bool ok = query.exec();
    if (!ok) {
        qWarning() << "[Sponsor::modifier] Exec failed:" << query.lastError().text();
        if (startedTx) db.rollback();
        return false;
    }

    int rowsAffected = query.numRowsAffected();
    qDebug() << "[Sponsor::modifier] Exec success, rowsAffected=" << rowsAffected;

    if (rowsAffected == 0) {
        qWarning() << "[Sponsor::modifier] Aucune ligne modifiée";
        if (startedTx) db.rollback();
        return false;
    }

    if (startedTx) {
        if (!db.commit()) {
            qWarning() << "[Sponsor::modifier] Commit failed:" << db.lastError().text();
            return false;
        }
        qDebug() << "[Sponsor::modifier] Commit success";
    }

    return true;
}

// ----------------- SUPPRIMER - COMME PROJET -----------------
bool Sponsor::supprimer(QString id)
{
    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database();
    qDebug() << "[Sponsor::supprimer] DB open:" << db.isOpen() << ", ID:" << id;

    // Vérifier existence - COMME PROJET
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(1) FROM ABIR.SPONSOR WHERE ID_SPONSOR = :id");
    checkQuery.bindValue(":id", id);
    if (checkQuery.exec() && checkQuery.next()) {
        if (checkQuery.value(0).toInt() == 0) {
            qWarning() << "[Sponsor::supprimer] Sponsor avec ID" << id << "n'existe pas";
            return false;
        }
    }

    // Transaction - COMME PROJET
    bool startedTx = false;
    if (db.driver() && db.driver()->hasFeature(QSqlDriver::Transactions)) {
        startedTx = db.transaction();
        qDebug() << "[Sponsor::supprimer] Transaction started:" << startedTx;
    }

    query.prepare("DELETE FROM ABIR.SPONSOR WHERE ID_SPONSOR = :id");
    query.bindValue(":id", id);

    bool ok = query.exec();
    if (!ok) {
        qWarning() << "[Sponsor::supprimer] Exec failed:" << query.lastError().text();
        if (startedTx) db.rollback();
        return false;
    }

    int rowsAffected = query.numRowsAffected();
    qDebug() << "[Sponsor::supprimer] Exec success, rowsAffected=" << rowsAffected;

    if (rowsAffected == 0) {
        qWarning() << "[Sponsor::supprimer] Aucune ligne supprimée";
        if (startedTx) db.rollback();
        return false;
    }

    if (startedTx) {
        if (!db.commit()) {
            qWarning() << "[Sponsor::supprimer] Commit failed:" << db.lastError().text();
            return false;
        }
        qDebug() << "[Sponsor::supprimer] Commit success";
    }

    return true;
}

// ----------------- AFFICHER TABLEAU - COMME PROJET -----------------
void Sponsor::afficherDansTableau(QTableWidget* tableWidget)
{
    QSqlQuery query("SELECT ID_SPONSOR, NOM, TYPE, DATE_DEBUT, DATE_FIN, CONTACT FROM ABIR.SPONSOR ORDER BY ID_SPONSOR");

    tableWidget->clear();
    tableWidget->setRowCount(0);

    // Configuration des colonnes
    QStringList headers = {"ID", "Nom", "Type", "Date Début", "Date Fin", "Contact"};
    tableWidget->setColumnCount(headers.size());
    tableWidget->setHorizontalHeaderLabels(headers);

    // Remplissage des données
    int row = 0;
    while (query.next()) {
        tableWidget->insertRow(row);

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
            tableWidget->setItem(row, col, item);
        }
        row++;
    }


    tableWidget->setAlternatingRowColors(false); // ⬅️ TOUTES LES LIGNES BLANCHES

    qDebug() << "[Sponsor::afficherDansTableau] Tableau rafraîchi:" << row << "lignes";
}

// ----------------- RECHERCHER PAR ID - COMME PROJET -----------------
bool Sponsor::rechercherParId(QString id, QString& nom, QString& type,
                              QDate& dateDebut, QDate& dateFin, QString& contact)
{
    QSqlQuery query;
    query.prepare("SELECT NOM, TYPE, DATE_DEBUT, DATE_FIN, CONTACT FROM ABIR.SPONSOR WHERE ID_SPONSOR = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        nom = query.value(0).toString();
        type = query.value(1).toString();
        dateDebut = query.value(2).toDate();
        dateFin = query.value(3).toDate();
        contact = query.value(4).toString();

        qDebug() << "[Sponsor::rechercherParId] Sponsor trouvé - ID:" << id << "Nom:" << nom;
        return true;
    }

    qDebug() << "[Sponsor::rechercherParId] Aucun sponsor trouvé avec ID:" << id;
    return false;
}
