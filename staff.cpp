#include "staff.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QRegularExpression>

Staff::Staff() {}

Staff::Staff(QString id, QString nom, QString prenom, QString poste,QString competence,
             QString telephone, QString email, QString mot_de_passe)
{
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->poste = poste;
    this->competence = competence;
    this->telephone = telephone;
    this->email = email;
    this->mot_de_passe = mot_de_passe;
}

// ➕ Ajouter un employé
bool Staff::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO ABIR.EMPLOYE (id_employe, nom, prenom, poste, competence, telephone, email, mot_de_passe) "
                  "VALUES (:id, :nom, :prenom, :poste, :competence, :telephone, :email, :mot_de_passe)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":competence", competence);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);
    query.bindValue(":mot_de_passe", mot_de_passe);


    if (!query.exec()) {
        qDebug() << "Erreur insertion Employe:" << query.lastError().text();
        return false;
    }
    return true;
}

// ❌ Supprimer un employé
bool Staff::supprimer(QString id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM ABIR.EMPLOYE WHERE id_employe = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur suppression Employe:" << query.lastError().text();
        return false;
    }
    return true;
}

// ✏️ Modifier un employé
bool Staff::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE ABIR.EMPLOYE SET nom = :nom, prenom = :prenom, poste = :poste, "
                  "competence = :competence, telephone = :telephone, email = :email, mot_de_passe = :mot_de_passe "
                  "WHERE id_employe = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":competence", competence);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);
    query.bindValue(":mot_de_passe", mot_de_passe);

    if (!query.exec()) {
        qDebug() << "Erreur modification Employe:" << query.lastError().text();
        return false;
    }
    return true;
}

// 📋 Afficher (utile pour QSqlTableModel)
QSqlQueryModel* Staff::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT id_employe, nom, prenom, poste, competence, telephone, email, mot_de_passe FROM ABIR.EMPLOYE");
    return model;
}

// Email validation method
bool Staff::isValidEmail(const QString &email)
{
    if (email.isEmpty()) {
        return false;
    }
    
    // Basic email validation using regex
    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return emailRegex.match(email).hasMatch();
}

// Afficher la liste des employés triés
QSqlQueryModel* Staff::afficherTrié(const QString &sortBy)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString query = "SELECT id_employe, nom, prenom, poste, competence, telephone, email, mot_de_passe FROM ABIR.EMPLOYE ";
    
    // Add ORDER BY clause based on sortBy parameter
    if (sortBy == "Nom" || sortBy == "nom") {
        query += "ORDER BY nom";
    } else if (sortBy == "Prénom" || sortBy == "prenom") {
        query += "ORDER BY prenom";
    } else if (sortBy == "Poste" || sortBy == "poste") {
        query += "ORDER BY poste";
    } else if (sortBy == "Compétence" || sortBy == "competence") {
        query += "ORDER BY competence";
    } else {
        query += "ORDER BY id_employe"; // Default sort by ID
    }
    
    model->setQuery(query);
    
    if (model->lastError().isValid()) {
        qWarning() << "[AfficherStaffTrié] Query error:" << model->lastError().text();
    } else {
        qDebug() << "[AfficherStaffTrié] Query set successfully with sort:" << sortBy;
    }
    
    return model;
}

// Chercher un employé par ID
QSqlQueryModel* Staff::chercherParId(const QString &id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString query = "SELECT id_employe, nom, prenom, poste, competence, telephone, email, mot_de_passe FROM ABIR.EMPLOYE ";
    query += "WHERE id_employe = '" + id + "'";
    
    model->setQuery(query);
    
    if (model->lastError().isValid()) {
        qWarning() << "[ChercherStaffParId] Query error:" << model->lastError().text();
    } else {
        qDebug() << "[ChercherStaffParId] Query set successfully for ID:" << id;
    }
    
    return model;
}
