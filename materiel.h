#ifndef MATERIEL_H
#define MATERIEL_H

#include <QString>
#include <QSqlQueryModel>
#include <QTableWidget> // <== Important pour afficher()

class Materiel
{
private:
    QString id_materiel, nom, type, etat, localisation;

public:
    Materiel();
    Materiel(QString, QString, QString, QString, QString);

    // Getters
    QString getId() const { return id_materiel; }
    QString getNom() const { return nom; }
    QString getType() const { return type; }
    QString getEtat() const { return etat; }
    QString getLocalisation() const { return localisation; }

    // Setters
    void setId(QString i) { id_materiel = i; }
    void setNom(QString n) { nom = n; }
    void setType(QString t) { type = t; }
    void setEtat(QString e) { etat = e; }
    void setLocalisation(QString l) { localisation = l; }

    bool ajouter();
    bool modifier(QString, QString, QString, QString, QString);
    bool supprimer(QString);
    void afficher(QTableWidget* table); // <== déclaration obligatoire
};

#endif // MATERIEL_H
