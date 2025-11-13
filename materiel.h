#ifndef MATERIEL_H
#define MATERIEL_H

#include <QString>
#include <QList>

// Forward declaration pour éviter les inclusions circulaires
class QTableWidget;

class Materiel
{
private:
    QString id_materiel;
    QString nom;
    QString type;
    QString etat;
    QString localisation;

public:
    // Constructeurs
    Materiel();
    Materiel(QString id_materiel, QString nom, QString type, QString etat, QString localisation);

    // Getters
    QString getId() const { return id_materiel; }
    QString getNom() const { return nom; }
    QString getType() const { return type; }
    QString getEtat() const { return etat; }
    QString getLocalisation() const { return localisation; }

    // Setters
    void setId(QString id) { id_materiel = id; }
    void setNom(QString n) { nom = n; }
    void setType(QString t) { type = t; }
    void setEtat(QString e) { etat = e; }
    void setLocalisation(QString l) { localisation = l; }

    // Méthodes CRUD principales
    bool ajouter();
    bool modifier();
    bool supprimer();

    // Méthodes d'affichage et recherche
    static void afficherTableau(QTableWidget* table);
    static QList<Materiel> chercher(QString id);
    static QList<Materiel> trier(QString critere);

    // Validation
    static bool validerId(QString id);
    static bool validerNom(QString nom);
    static bool existeId(QString id);
};

#endif // MATERIEL_H
