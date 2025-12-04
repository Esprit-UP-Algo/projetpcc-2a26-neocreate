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
    QString contribution;
    QDate dateDebut;
    QDate dateFin;
    QString email;

public:
    // Constructeurs - COMME PROJET
    Sponsor();
    Sponsor(QString id, QString nom, QString contribution, QDate dateDebut, QDate dateFin, QString email);

    // Getters - COMME PROJET
    QString getId() const { return id; }
    QString getNom() const { return nom; }
    QString getContribution() const { return contribution; }
    QDate getDateDebut() const { return dateDebut; }
    QDate getDateFin() const { return dateFin; }
    QString getEmail() const { return email; }

    // Setters - COMME PROJET
    void setId(QString id) { this->id = id; }
    void setNom(QString nom) { this->nom = nom; }
    void setContribution(QString contribution) { this->contribution = contribution; }
    void setDateDebut(QDate dateDebut) { this->dateDebut = dateDebut; }
    void setDateFin(QDate dateFin) { this->dateFin = dateFin; }
    void setEmail(QString email) { this->email = email; }

    // CRUD - COMME PROJET
    bool ajouter();
    bool modifier();
    bool supprimer(QString id);
    static void trierParNom(QTableWidget* tableWidget);
    // Affichage - COMME PROJET
    static void afficherDansTableau(QTableWidget* tableWidget);

    // Recherche - NOUVELLE MÉTHODE COMME PROJET
    static bool rechercherParId(QString id, QString& nom, QString& contribution,
                                QDate& dateDebut, QDate& dateFin, QString& email);
    // RECHERCHE PAR NOM
    static void rechercherParNom(QTableWidget* tableWidget, const QString& nom);

    // TRI PAR ID CROISSANT
    static void trierParId(QTableWidget* tableWidget);
};

#endif // SPONSOR_H
