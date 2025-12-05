#ifndef PROJET_H
#define PROJET_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPair>
#include <QVector>

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
    QString note_materiel;

public:
    Projet();
    Projet(int id, const QString &type, const QDate &date_debut, const QDate &date_fin,
           float montant, const QString &paiment, const QString &note_materiel);

    int getId() const { return id; }
    QString getType() const { return type; }
    QDate getDateDebut() const { return date_debut; }
    QDate getDateFin() const { return date_fin; }
    float getMontant() const { return montant; }
    QString getPaiment() const { return paiment; }
    QString getNoteMateriel() const;
    int getIdClient() const { return id_client; }

    void setId(int id) { this->id = id; }
    void setType(const QString &type) { this->type = type; }
    void setDateDebut(const QDate &date) { date_debut = date; }
    void setDateFin(const QDate &date) { date_fin = date; }
    void setMontant(float montant) { this->montant = montant; }
    void setPaiment(const QString &paiment) { this->paiment = paiment; }
    void setNoteMateriel(const QString &newNote_materiel);
    void setIdClient(int id_client) { this->id_client = id_client; }

    bool AjouterProjet();
    QSqlQueryModel* AfficherProjets();
    QSqlQueryModel* AfficherProjetsTriés(const QString &sortBy);
    QSqlQueryModel* ChercherProjetParId(int id);
    static QSqlQueryModel* ChercherProjetParTypeStatique(const QString &type);
    bool ModifierProjet();
    bool SupprimerProjet(int id);

    static QSqlQueryModel* ChercherProjetParIdStatique(int id);
    // Statistics helpers
    static double TotalMontant();                    // SUM(MONTANT)
    static double AverageMontant();                  // AVG(MONTANT)
    static QVector<QPair<QString,int>> CountsByType(); // (TYPE, COUNT)
    static QVector<QPair<QString,double>> MontantByPaiment(); // (PAIMENT, SUM(MONTANT))
    static QVector<QPair<QString,int>> CountsByPaiment(); // (PAIMENT, COUNT)
};

#endif
