#include "materiel.h"
#include "connection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QTableWidget>

// Constructeurs
Materiel::Materiel() {}

Materiel::Materiel(QString id_materiel, QString nom, QString type,
                   QString etat, QString localisation)
    : id_materiel(id_materiel), nom(nom), type(type), etat(etat), localisation(localisation)
{}

// AJOUTER
bool Materiel::ajouter()
{
    if (!Connection::createconnect()) {
        qDebug() << "❌ Erreur connexion base !";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");
    QSqlQuery query(db);

    query.prepare("INSERT INTO materiel (id_materiel, nom, type, etat, localisation) "
                  "VALUES (:id_materiel, :nom, :type, :etat, :localisation)");

    query.bindValue(":id_materiel", id_materiel);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    query.bindValue(":localisation", localisation);

    if (!query.exec()) {
        qDebug() << "Erreur ajout:" << query.lastError().text();
        return false;
    }

    qDebug() << "✅ Ajout réussi:" << id_materiel;
    return true;
}

// MODIFIER
bool Materiel::modifier()
{
    if (!Connection::createconnect()) {
        qDebug() << "❌ Erreur connexion base !";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");
    QSqlQuery query(db);

    query.prepare("UPDATE materiel SET nom = :nom, type = :type, etat = :etat, "
                  "localisation = :localisation WHERE id_materiel = :id_materiel");

    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    query.bindValue(":localisation", localisation);
    query.bindValue(":id_materiel", id_materiel);

    if (!query.exec()) {
        qDebug() << "Erreur modification:" << query.lastError().text();
        return false;
    }

    qDebug() << "✅ Modification réussie:" << id_materiel;
    return true;
}

// SUPPRIMER
bool Materiel::supprimer()
{
    if (!Connection::createconnect()) {
        qDebug() << "❌ Erreur connexion base !";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");
    QSqlQuery query(db);

    query.prepare("DELETE FROM materiel WHERE id_materiel = :id_materiel");
    query.bindValue(":id_materiel", id_materiel);

    if (!query.exec()) {
        qDebug() << "Erreur suppression:" << query.lastError().text();
        return false;
    }

    qDebug() << "✅ Suppression réussie:" << id_materiel;
    return true;
}

// AFFICHER TABLEAU
void Materiel::afficherTableau(QTableWidget* table)
{
    if (!Connection::createconnect()) {
        qDebug() << "❌ Erreur connexion base !";
        return;
    }

    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");
    QSqlQuery query(db);

    if (!query.exec("SELECT id_materiel, nom, type, etat, localisation FROM materiel")) {
        qDebug() << "Erreur SELECT:" << query.lastError().text();
        return;
    }

    table->setRowCount(0);
    int row = 0;

    while (query.next()) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        table->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        table->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        table->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        table->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
        row++;
    }

    qDebug() << "✅ Tableau affiché:" << row << "lignes";
}

// CHERCHER
QList<Materiel> Materiel::chercher(QString id)
{
    QList<Materiel> resultats;

    if (!Connection::createconnect()) {
        return resultats;
    }

    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");
    QSqlQuery query(db);

    query.prepare("SELECT id_materiel, nom, type, etat, localisation FROM materiel WHERE id_materiel = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        while (query.next()) {
            Materiel m(query.value(0).toString(),
                       query.value(1).toString(),
                       query.value(2).toString(),
                       query.value(3).toString(),
                       query.value(4).toString());
            resultats.append(m);
        }
    }

    return resultats;
}

// TRIER
QList<Materiel> Materiel::trier(QString critere)
{
    QList<Materiel> resultats;

    if (!Connection::createconnect()) {
        return resultats;
    }

    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");
    QSqlQuery query(db);

    QString requete = "SELECT id_materiel, nom, type, etat, localisation FROM materiel ";

    if (critere == "Type") {
        requete += "ORDER BY type";
    } else if (critere == "État") {
        requete += "ORDER BY etat";
    } else {
        requete += "ORDER BY id_materiel";
    }

    if (query.exec(requete)) {
        while (query.next()) {
            Materiel m(query.value(0).toString(),
                       query.value(1).toString(),
                       query.value(2).toString(),
                       query.value(3).toString(),
                       query.value(4).toString());
            resultats.append(m);
        }
    }

    return resultats;
}

// VALIDATION ID
bool Materiel::validerId(QString id)
{
    bool ok;
    id.toInt(&ok);
    return ok && id.length() == 8;
}

// VALIDATION NOM
bool Materiel::validerNom(QString nom)
{
    return !nom.isEmpty() && nom.at(0).isUpper();
}

// VERIFIER SI ID EXISTE
bool Materiel::existeId(QString id)
{
    if (!Connection::createconnect()) {
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");
    QSqlQuery query(db);

    query.prepare("SELECT COUNT(*) FROM materiel WHERE id_materiel = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
}
