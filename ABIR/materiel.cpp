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
    QSqlQuery query;

    query.prepare("INSERT INTO MATERIEL (ID_MATERIEL, NOM, TYPE, ETAT, LOCALISATION) "
                  "VALUES (:id_materiel, :nom, :type, :etat, :localisation)");

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
    QSqlQuery query;

    query.prepare("UPDATE MATERIEL SET NOM = :nom, TYPE = :type, ETAT = :etat, "
                  "LOCALISATION = :localisation "
                  "WHERE ID_MATERIEL = :id");

    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    query.bindValue(":localisation", localisation);
    query.bindValue(":id", id_materiel);

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
    QSqlQuery query;

    query.prepare("DELETE FROM MATERIEL WHERE ID_MATERIEL = :id");
    query.bindValue(":id", id_materiel);

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
    QSqlQuery query;

    query.prepare("SELECT ID_MATERIEL, NOM, TYPE, ETAT, LOCALISATION FROM MATERIEL");

    if (!query.exec()) {
        qDebug() << "Erreur de récupération des matériels :" << query.lastError().text();
        return;
    }

    table->setRowCount(0);
    int row = 0;
    while (query.next()) {
        table->insertRow(row);
        table->setItem(row, 1, new QTableWidgetItem(query.value(0).toString())); // ID_MATERIEL
        table->setItem(row, 2, new QTableWidgetItem(query.value(1).toString())); // NOM
        table->setItem(row, 3, new QTableWidgetItem(query.value(2).toString())); // TYPE
        table->setItem(row, 4, new QTableWidgetItem(query.value(3).toString())); // ETAT
        table->setItem(row, 5, new QTableWidgetItem(query.value(4).toString())); // LOCALISATION
        row++;
    }

    qDebug() << "✅ Tableau mis à jour avec" << row << "matériels.";
}

// Afficher les matériels triés
void Materiel::afficherTrié(QTableWidget* table, const QString &sortBy)
{
    QSqlQuery query;
    QString sql = "SELECT ID_MATERIEL, NOM, TYPE, ETAT, LOCALISATION FROM MATERIEL ";
    
    // Add ORDER BY clause based on sortBy parameter
    if (sortBy == "Etat" || sortBy == "etat") {
        sql += "ORDER BY ETAT";
    } else if (sortBy == "Type" || sortBy == "type") {
        sql += "ORDER BY TYPE";
    } else {
        sql += "ORDER BY ID_MATERIEL"; // Default sort by ID
    }
    
    query.prepare(sql);
    
    if (!query.exec()) {
        qDebug() << "Erreur de récupération des matériels triés :" << query.lastError().text();
        return;
    }

    table->setRowCount(0);
    int row = 0;
    while (query.next()) {
        table->insertRow(row);
        table->setItem(row, 1, new QTableWidgetItem(query.value(0).toString())); // ID_MATERIEL
        table->setItem(row, 2, new QTableWidgetItem(query.value(1).toString())); // NOM
        table->setItem(row, 3, new QTableWidgetItem(query.value(2).toString())); // TYPE
        table->setItem(row, 4, new QTableWidgetItem(query.value(3).toString())); // ETAT
        table->setItem(row, 5, new QTableWidgetItem(query.value(4).toString())); // LOCALISATION
        row++;
    }

    qDebug() << "✅ Tableau trié mis à jour avec" << row << "matériels. Sort by:" << sortBy;
}

// Chercher un matériel par ID
void Materiel::chercherParId(QTableWidget* table, const QString &id)
{
    QSqlQuery query;
    query.prepare("SELECT ID_MATERIEL, NOM, TYPE, ETAT, LOCALISATION FROM MATERIEL WHERE ID_MATERIEL = :id");
    query.bindValue(":id", id);
    
    if (!query.exec()) {
        qDebug() << "Erreur de recherche matériel :" << query.lastError().text();
        return;
    }

    table->setRowCount(0);
    int row = 0;
    while (query.next()) {
        table->insertRow(row);
        table->setItem(row, 1, new QTableWidgetItem(query.value(0).toString())); // ID_MATERIEL
        table->setItem(row, 2, new QTableWidgetItem(query.value(1).toString())); // NOM
        table->setItem(row, 3, new QTableWidgetItem(query.value(2).toString())); // TYPE
        table->setItem(row, 4, new QTableWidgetItem(query.value(3).toString())); // ETAT
        table->setItem(row, 5, new QTableWidgetItem(query.value(4).toString())); // LOCALISATION
        row++;
    }

    qDebug() << "✅ Recherche terminée. Trouvé" << row << "matériel(s) avec ID:" << id;
}
