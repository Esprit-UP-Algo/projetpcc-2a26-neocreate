#ifndef STAFF_H
#define STAFF_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Staff
{
private:
    QString id;
    QString nom;
    QString prenom;
    QString poste;
    QString competence;
    QString telephone;
    QString email;


public:
    Staff(); // constructeur vide
    Staff(QString, QString, QString, QString, QString, QString, QString);

    // Méthodes CRUD
    bool ajouter();
    bool supprimer(QString);
    bool modifier();

    // Méthode optionnelle si tu veux afficher via QTableView plus tard
    QSqlQueryModel* afficher();
};

#endif // STAFF_H
