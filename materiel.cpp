#include "materiel.h"
#include "connection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

// Constructeurs
Materiel::Materiel() {}

Materiel::Materiel(QString id_materiel, QString nom, QString type,
                   QString etat, QString localisation, QString couleur, int qte)
{
    this->id_materiel= id_materiel;
    this->nom = nom;
    this->type = type;
    this->etat = etat;
    this->localisation = localisation;
    this->couleur = couleur;
    this->qte = qte;
}

// Ajouter un matériel
bool Materiel::ajouter()
{
    QSqlQuery query;

    query.prepare("INSERT INTO abir.MATERIEL (ID_MATERIEL, NOM, TYPE, ETAT, LOCALISATION, QTE, COULEUR) "
                  "VALUES (:id_materiel, :nom, :type, :etat, :localisation, :qte, :couleur)");

    query.bindValue(":id_materiel", id_materiel);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    query.bindValue(":localisation", localisation);
    query.bindValue(":qte", qte);
    query.bindValue(":couleur", couleur);

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
                        QString etat, QString localisation, QString couleur, int qte)
{
    QSqlQuery query;

    query.prepare("UPDATE abir.MATERIEL SET NOM = :nom, TYPE = :type, ETAT = :etat, "
                  "LOCALISATION = :localisation, QTE = :qte, COULEUR = :couleur "
                  "WHERE ID_MATERIEL = :id");

    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    query.bindValue(":localisation", localisation);
    query.bindValue(":qte", qte);
    query.bindValue(":couleur", couleur);
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

    query.prepare("DELETE FROM abir.MATERIEL WHERE ID_MATERIEL = :id");
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

    query.prepare("SELECT ID_MATERIEL, NOM, TYPE, ETAT, LOCALISATION FROM abir.MATERIEL");

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
    QString sql = "SELECT ID_MATERIEL, NOM, TYPE, ETAT, LOCALISATION FROM abir.MATERIEL ";

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
    query.prepare("SELECT ID_MATERIEL, NOM, TYPE, ETAT, LOCALISATION FROM abir.MATERIEL WHERE ID_MATERIEL = :id");
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
void Materiel::chercherParNom(QTableWidget *table, const QString &nom)
{
    table->setRowCount(0);

    QSqlQuery query;
    query.prepare("SELECT ID_MATERIEL, NOM, TYPE, ETAT, LOCALISATION FROM abir.MATERIEL WHERE LOWER(NOM) LIKE LOWER(:nom)");
    query.bindValue(":nom", "%" + nom + "%");

    if (!query.exec()) return;

    int row = 0;
    while (query.next()) {
        table->insertRow(row);
        table->setItem(row, 1, new QTableWidgetItem(query.value(0).toString()));
        table->setItem(row, 2, new QTableWidgetItem(query.value(1).toString()));
        table->setItem(row, 3, new QTableWidgetItem(query.value(2).toString()));
        table->setItem(row, 4, new QTableWidgetItem(query.value(3).toString()));
        table->setItem(row, 5, new QTableWidgetItem(query.value(4).toString()));
        row++;
    }
}

// Chercher par couleur
void Materiel::chercherParCouleur(QTableWidget* table, const QString &couleur)
{
    table->setRowCount(0);
    QSqlQuery query;
    
    query.prepare("SELECT ID_MATERIEL, NOM, TYPE, ETAT, LOCALISATION, QTE, COULEUR FROM abir.MATERIEL WHERE LOWER(COULEUR) = LOWER(:couleur)");
    query.bindValue(":couleur", couleur);

    if (!query.exec()) return;

    int row = 0;
    while (query.next()) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        table->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        table->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        table->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
        table->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
        table->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
        table->setItem(row, 6, new QTableWidgetItem(query.value(6).toString()));
        row++;
    }
}

// Obtenir nom du matériel par couleur (statique pour utilisation facile)
QString Materiel::getMaterielNomByCouleur(const QString &couleur)
{
    QSqlQuery query;
    
    query.prepare("SELECT NOM FROM abir.MATERIEL WHERE LOWER(COULEUR) = LOWER(:couleur) AND ETAT = 'fonctionnel' AND ROWNUM <= 1");
    query.bindValue(":couleur", couleur);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    
    return "Équipement non trouvé";
}

