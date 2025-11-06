#include "staff.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include"connection.h"
Staff::Staff() {}

Staff::Staff(QString id, QString nom, QString prenom, QString poste,QString competence,
             QString telephone, QString email)
{
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->poste = poste;
    this->competence = competence;
    this->telephone = telephone;
    this->email = email;

}

// ➕ Ajouter un employé
bool Staff::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO Employe (id_employe, nom, prenom, poste,competence, telephone, email) "
                  "VALUES (:id, :nom, :prenom, :poste,:competence, :telephone, :email)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":competence", competence);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);


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
    query.prepare("DELETE FROM Employe WHERE id_employe = :id");
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
    query.prepare("UPDATE Employe SET nom = :nom, prenom = :prenom, poste = :poste, "
                  "competence = :competence,telephone = :telephone, email = :email "
                  "WHERE id_employe = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":competence", competence);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);

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
    model->setQuery("SELECT id_employe, nom, prenom, poste, competence,telephone, email FROM Employe");
    return model;
}
