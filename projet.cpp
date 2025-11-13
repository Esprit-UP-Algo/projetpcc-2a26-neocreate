#include "projet.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlDriver>

Projet::Projet()
{
    id = 0;
    type = "";
    date_debut = QDate::currentDate();
    date_fin = QDate::currentDate();
    montant = 0.0;
    paiment = "";
    id_client = 0;
}

Projet::Projet(int id, const QString &type, const QDate &date_debut,
               const QDate &date_fin, float montant, const QString &paiment)
{
    this->id = id;
    this->type = type;
    this->date_debut = date_debut;
    this->date_fin = date_fin;
    this->montant = montant;
    this->paiment = paiment;
}

// Ajouter un projet
bool Projet::AjouterProjet()
{
    QSqlQuery query;
    // Diagnostics: connection info
    QSqlDatabase db = QSqlDatabase::database();
    qDebug() << "[AjouterProjet] DB open:" << db.isOpen()
             << ", driver:" << db.driverName()
             << ", name:" << db.databaseName();

    // Try to log current Oracle user if possible (Oracle only)
    {
        QSqlQuery whoami;
        if (whoami.exec("SELECT USER FROM dual")) {
            if (whoami.next()) qDebug() << "[AjouterProjet] Current USER:" << whoami.value(0).toString();
        }
    }
    // Construire la requête SQL dynamiquement selon si ID_CLIENT est fourni
    QString sql;
    if (id_client > 0) {
        sql = "INSERT INTO ABIR.PROJET (ID_PROJET, TYPE, DATE_D, DATE_F, PAIMENT, ID_CLIENT) "
              "VALUES (:id, :type, :date_d, :date_f, :paiment, :id_client)";
    } else {
        sql = "INSERT INTO ABIR.PROJET (ID_PROJET, TYPE, DATE_D, DATE_F, PAIMENT) "
              "VALUES (:id, :type, :date_d, :date_f, :paiment)";
    }
    query.prepare(sql);

    qDebug() << "[AjouterProjet] Parameters:"
             << "id=" << id
             << ", type=" << type
             << ", date_debut=" << date_debut.toString("yyyy-MM-dd")
             << ", date_fin=" << date_fin.toString("yyyy-MM-dd")
             << ", montant=" << montant
             << ", paiment=" << paiment
             << ", id_client=" << (id_client > 0 ? QString::number(id_client) : "NULL");

    query.bindValue(":id", id);
    query.bindValue(":type", type);
    query.bindValue(":date_d", date_debut);
    query.bindValue(":date_f", date_fin);
    query.bindValue(":paiment", QVariant::fromValue(static_cast<double>(montant)));
    // ID_CLIENT est optionnel : ne l'inclure que s'il est > 0
    if (id_client > 0) {
        query.bindValue(":id_client", id_client);
    }

    // Start an explicit transaction if supported
    bool startedTx = false;
    if (db.driver() && db.driver()->hasFeature(QSqlDriver::Transactions)) {
        startedTx = db.transaction();
        qDebug() << "[AjouterProjet] transaction started:" << startedTx;
    }

    const bool ok = query.exec();
    if (!ok) {
        qWarning() << "[AjouterProjet] Exec failed:" << query.lastError().text() << "| SQL:" << query.lastQuery();
        // Rollback transaction if it was started
        if (startedTx && db.driver() && db.driver()->hasFeature(QSqlDriver::Transactions)) {
            db.rollback();
            qDebug() << "[AjouterProjet] Transaction rolled back due to error.";
        }
        return false;
    }
    qDebug() << "[AjouterProjet] Exec success, rowsAffected=" << query.numRowsAffected();

    if (startedTx && db.driver() && db.driver()->hasFeature(QSqlDriver::Transactions)) {
        qDebug() << "[AjouterProjet] Driver supports transactions. Committing...";
        if (!db.commit()) {
            qWarning() << "[AjouterProjet] Commit failed:" << db.lastError().text();
            return false;
        } else {
            qDebug() << "[AjouterProjet] Commit success.";
        }
    }

    // Verify persistence immediately via SELECT
    QSqlQuery verify;
    verify.prepare("SELECT COUNT(1) FROM ABIR.PROJET WHERE ID_PROJET = :id");
    verify.bindValue(":id", id);
    if (verify.exec() && verify.next()) {
        qDebug() << "[AjouterProjet] Verify count for ID=" << id << ":" << verify.value(0).toInt();
    } else {
        qWarning() << "[AjouterProjet] Verify SELECT failed:" << verify.lastError().text();
    }
    return true;
}

// Afficher la liste des projets
QSqlQueryModel* Projet::AfficherProjets()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    // Format dates as ISO text for consistent UI rendering
    model->setQuery(
        "SELECT ID_PROJET, TYPE, TO_CHAR(DATE_D, 'YYYY-MM-DD') AS DATE_D, "
        "TO_CHAR(DATE_F, 'YYYY-MM-DD') AS DATE_F, PAIMENT, ID_CLIENT FROM ABIR.PROJET"
        );

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_PROJET"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date début"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date fin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Paiement"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("ID_CLIENT"));

    if (model->lastError().isValid()) {
        qWarning() << "[AfficherProjets] Query error:" << model->lastError().text();
    } else {
        qDebug() << "[AfficherProjets] Query set successfully.";
    }

    return model;
}

// Modifier un projet
bool Projet::ModifierProjet()
{
    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database();
    qDebug() << "[ModifierProjet] DB open:" << db.isOpen() << ", driver:" << db.driverName();

    // Construire la requête SQL dynamiquement selon si ID_CLIENT est fourni
    QString sql;
    if (id_client > 0) {
        sql = "UPDATE ABIR.PROJET SET TYPE = :type, DATE_D = :date_d, DATE_F = :date_f, PAIMENT = :paiment, ID_CLIENT = :id_client WHERE ID_PROJET = :id";
    } else {
        sql = "UPDATE ABIR.PROJET SET TYPE = :type, DATE_D = :date_d, DATE_F = :date_f, PAIMENT = :paiment, ID_CLIENT = NULL WHERE ID_PROJET = :id";
    }
    query.prepare(sql);

    qDebug() << "[ModifierProjet] Parameters: id=" << id
             << ", type=" << type
             << ", date_debut=" << date_debut.toString("yyyy-MM-dd")
             << ", date_fin=" << date_fin.toString("yyyy-MM-dd")
             << ", montant=" << montant
             << ", paiment=" << paiment
             << ", id_client=" << (id_client > 0 ? QString::number(id_client) : "NULL");

    query.bindValue(":type", type);
    query.bindValue(":date_d", date_debut);
    query.bindValue(":date_f", date_fin);
    query.bindValue(":paiment", QVariant::fromValue(static_cast<double>(montant)));
    if (id_client > 0) {
        query.bindValue(":id_client", id_client);
    }
    query.bindValue(":id", id);

    // Start an explicit transaction if supported
    bool startedTx = false;
    if (db.driver() && db.driver()->hasFeature(QSqlDriver::Transactions)) {
        startedTx = db.transaction();
        qDebug() << "[ModifierProjet] transaction started:" << startedTx;
    }

    const bool ok = query.exec();
    if (!ok) {
        qWarning() << "[ModifierProjet] Exec failed:" << query.lastError().text() << "| SQL:" << query.lastQuery();
        // Rollback transaction if it was started
        if (startedTx && db.driver() && db.driver()->hasFeature(QSqlDriver::Transactions)) {
            db.rollback();
            qDebug() << "[ModifierProjet] Transaction rolled back due to error.";
        }
        return false;
    }

    const int rowsAffected = query.numRowsAffected();
    qDebug() << "[ModifierProjet] Exec success, rowsAffected=" << rowsAffected;

    if (rowsAffected == 0) {
        qWarning() << "[ModifierProjet] Aucune ligne modifiée. Le projet avec ID" << id << "n'existe peut-être pas.";
        // Rollback transaction if it was started
        if (startedTx && db.driver() && db.driver()->hasFeature(QSqlDriver::Transactions)) {
            db.rollback();
            qDebug() << "[ModifierProjet] Transaction rolled back - no rows affected.";
        }
        return false;
    }

    if (startedTx && db.driver() && db.driver()->hasFeature(QSqlDriver::Transactions)) {
        qDebug() << "[ModifierProjet] Driver supports transactions. Committing...";
        if (!db.commit()) {
            qWarning() << "[ModifierProjet] Commit failed:" << db.lastError().text();
            return false;
        } else {
            qDebug() << "[ModifierProjet] Commit success.";
        }
    }

    return true;
}

// Supprimer un projet
bool Projet::SupprimerProjet(int id)
{
    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database();
    qDebug() << "[SupprimerProjet] DB open:" << db.isOpen() << ", driver:" << db.driverName() << ", id=" << id;

    // Vérifier que le projet existe d'abord
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(1) FROM ABIR.PROJET WHERE ID_PROJET = :id");
    checkQuery.bindValue(":id", id);
    if (checkQuery.exec() && checkQuery.next()) {
        if (checkQuery.value(0).toInt() == 0) {
            qWarning() << "[SupprimerProjet] Projet avec ID" << id << "n'existe pas.";
            return false;
        }
    }

    // Start an explicit transaction if supported
    bool startedTx = false;
    if (db.driver() && db.driver()->hasFeature(QSqlDriver::Transactions)) {
        startedTx = db.transaction();
        qDebug() << "[SupprimerProjet] transaction started:" << startedTx;
    }

    query.prepare("DELETE FROM ABIR.PROJET WHERE ID_PROJET = :id");
    query.bindValue(":id", id);
    const bool ok = query.exec();
    if (!ok) {
        qWarning() << "[SupprimerProjet] Exec failed:" << query.lastError().text() << "| SQL:" << query.lastQuery();
        // Rollback transaction if it was started
        if (startedTx && db.driver() && db.driver()->hasFeature(QSqlDriver::Transactions)) {
            db.rollback();
            qDebug() << "[SupprimerProjet] Transaction rolled back due to error.";
        }
        return false;
    }

    const int rowsAffected = query.numRowsAffected();
    qDebug() << "[SupprimerProjet] Exec success, rowsAffected=" << rowsAffected;

    if (rowsAffected == 0) {
        qWarning() << "[SupprimerProjet] Aucune ligne supprimée. Le projet avec ID" << id << "n'existe peut-être pas.";
        // Rollback transaction if it was started
        if (startedTx && db.driver() && db.driver()->hasFeature(QSqlDriver::Transactions)) {
            db.rollback();
            qDebug() << "[SupprimerProjet] Transaction rolled back - no rows affected.";
        }
        return false;
    }

    if (startedTx && db.driver() && db.driver()->hasFeature(QSqlDriver::Transactions)) {
        qDebug() << "[SupprimerProjet] Driver supports transactions. Committing...";
        if (!db.commit()) {
            qWarning() << "[SupprimerProjet] Commit failed:" << db.lastError().text();
            return false;
        } else {
            qDebug() << "[SupprimerProjet] Commit success.";
        }
    }

    return true;
}
