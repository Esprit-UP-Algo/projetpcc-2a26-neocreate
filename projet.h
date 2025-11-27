#ifndef PROJET_H
#define PROJET_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Projet
{
private:
    int id;
    QString type;
    QDate date_debut;
    QDate date_fin;
    float montant;
    QString paiment;
    int id_client;

public:
    // Constructeurs
    Projet();
    Projet(int id, const QString &type, const QDate &date_debut, const QDate &date_fin,
           float montant, const QString &paiment);

    // Getters
    int getId() const { return id; }
    QString getType() const { return type; }
    QDate getDateDebut() const { return date_debut; }
    QDate getDateFin() const { return date_fin; }
    float getMontant() const { return montant; }
    QString getPaiment() const { return paiment; }
    int getIdClient() const { return id_client; }

    // Setters
    void setId(int id) { this->id = id; }
    void setType(const QString &type) { this->type = type; }
    void setDateDebut(const QDate &date) { date_debut = date; }
    void setDateFin(const QDate &date) { date_fin = date; }
    void setMontant(float montant) { this->montant = montant; }
    void setPaiment(const QString &paiment) { this->paiment = paiment; }
    void setIdClient(int id_client) { this->id_client = id_client; }

    // CRUD
    bool AjouterProjet();
    QSqlQueryModel* AfficherProjets();
    QSqlQueryModel* AfficherProjetsTriés(const QString &sortBy);
    QSqlQueryModel* ChercherProjetParId(int id);
    bool ModifierProjet();
    bool SupprimerProjet(int id);
    
    // Static method for searching
    static QSqlQueryModel* ChercherProjetParIdStatique(int id);
};

#endif // PROJET_H
