#include "materiel.h"
#include "connection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

// Constructeurs
Materiel::Materiel() {}

Materiel::Materiel(QString id_materiel, QString nom, QString type,
                   QString etat, QString localisation)
{
    this->id_materiel= id_materiel;
    this->nom = nom;
    this->type = type;
    this->etat = etat;
    this->localisation = localisation;
}

// Ajouter un matériel
bool Materiel::ajouter()
{
    if (!Connection::instance()->createconnect()) {
        qDebug() << "❌ Erreur : impossible d'ouvrir la connexion à la base !";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");
    QSqlQuery query(db);

    query.prepare("INSERT INTO MATERIEL (ID_MAT, NOM_MAT, TYPE_MAT, ETAT_MAT, LOCALISATION_MAT, RESPONSABLE_MAT) "
                  "VALUES (:id_materiel, :nom, :type, :etat, :localisation, :responsable)");

    query.bindValue(":id_materiel", id_materiel);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    query.bindValue(":localisation", localisation);

    if (!query.exec()) {
        qDebug() << "Erreur d'ajout matériel :" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur", "Impossible d'ajouter le matériel !");
        return false;
    }

    QMessageBox::information(nullptr, "Succès", "✅ Matériel ajouté avec succès !");
    return true;
}

// Modifier un matériel
bool Materiel::modifier(QString id_materiel, QString nom, QString type,
                        QString etat, QString localisation)
{
    if (!Connection::instance()->createconnect()) {
        qDebug() << "Erreur : impossible d'ouvrir la connexion !";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");
    QSqlQuery query(db);

    query.prepare("UPDATE MATERIEL SET NOM_MAT = :nom, TYPE_MAT = :type, ETAT_MAT = :etat, "
                  "LOCALISATION_MAT = :localisation, RESPONSABLE_MAT = :responsable "
                  "WHERE ID_MAT = :id");

    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    query.bindValue(":localisation", localisation);
    query.bindValue(":id_materiel", id_materiel);

    if (!query.exec()) {
        qDebug() << "Erreur de modification :" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur", "Échec de la modification !");
        return false;
    }

    QMessageBox::information(nullptr, "Succès", "✅ Matériel modifié avec succès !");
    return true;
}

// Supprimer un matériel
bool Materiel::supprimer(QString id_materiel)
{
    if (!Connection::instance()->createconnect()) {
        qDebug() << "Erreur : impossible d'ouvrir la connexion !";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");
    QSqlQuery query(db);

    query.prepare("DELETE FROM MATERIEL WHERE ID_MAT = :id");
    query.bindValue(":id_materiel", id_materiel);

    if (!query.exec()) {
        qDebug() << "Erreur de suppression :" << query.lastError().text();
        QMessageBox::critical(nullptr, "Erreur", "Impossible de supprimer le matériel !");
        return false;
    }

    QMessageBox::information(nullptr, "Succès", "🗑️ Matériel supprimé avec succès !");
    return true;
}

// Afficher tous les matériels dans un QTableWidget
void Materiel::afficher(QTableWidget* table)
{
    if (!Connection::instance()->createconnect()) {
        qDebug() << "Erreur : impossible d'ouvrir la connexion !";
        return;
    }

    QSqlDatabase db = QSqlDatabase::database("qt_oracle_connection");
    QSqlQuery query(db);

    query.prepare("SELECT ID_MAT, NOM_MAT, TYPE_MAT, ETAT_MAT, LOCALISATION_MAT, RESPONSABLE_MAT FROM MATERIEL");

    if (!query.exec()) {
        qDebug() << "Erreur de récupération des matériels :" << query.lastError().text();
        return;
    }

    table->setRowCount(0);
    int row = 0;
    while (query.next()) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // ID
        table->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // Nom
        table->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // Type
        table->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // État
        table->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // Localisation
        row++;
    }

    qDebug() << "✅ Tableau mis à jour avec" << row << "matériels.";
}
