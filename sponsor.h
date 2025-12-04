#ifndef SPONSOR_H
#define SPONSOR_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QWidget>
#include <QTableWidget>

class Sponsor
{
private:
    QString id;
    QString nom;
    QString type;
    QString details;
    QDate dateDebut;
    QDate dateFin;
    QString contact;

public:
    // Constructeurs - COMME PROJET
    Sponsor();
    Sponsor(QString id, QString nom, QString type, QString details, QDate dateDebut, QDate dateFin, QString contact);

    // Getters - COMME PROJET
    QString getId() const { return id; }
    QString getNom() const { return nom; }
    QString getType() const { return type; }
    QString getDetails() const { return details; }
    QDate getDateDebut() const { return dateDebut; }
    QDate getDateFin() const { return dateFin; }
    QString getContact() const { return contact; }

    // Setters - COMME PROJET
    void setId(QString id) { this->id = id; }
    void setNom(QString nom) { this->nom = nom; }
    void setType(QString type) { this->type = type; }
    void setDetails(QString details) { this->details = details; }
    void setDateDebut(QDate dateDebut) { this->dateDebut = dateDebut; }
    void setDateFin(QDate dateFin) { this->dateFin = dateFin; }
    void setContact(QString contact) { this->contact = contact; }

    // CRUD - COMME PROJET
    bool ajouter();
    bool modifier();
    bool supprimer(QString id);

    // Affichage - COMME PROJET
    static void afficherDansTableau(QTableWidget* tableWidget);

    // Recherche - NOUVELLE MÉTHODE COMME PROJET
    static bool rechercherParId(QString id, QString& nom, QString& type,
                                QDate& dateDebut, QDate& dateFin, QString& contact);
};

#endif // SPONSOR_H
