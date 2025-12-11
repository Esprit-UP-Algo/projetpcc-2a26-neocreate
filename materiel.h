#ifndef MATERIEL_H
#define MATERIEL_H

#include <QString>
#include <QSqlQueryModel>
#include <QTableWidget> // <== Important pour afficher()

class Materiel
{
private:
    QString id_materiel, nom, type, etat, localisation, couleur;
    int qte;

public:
    Materiel();
    Materiel(QString, QString, QString, QString, QString, QString = "", int = 0);

    // Getters
    QString getId() const { return id_materiel; }
    QString getNom() const { return nom; }
    QString getType() const { return type; }
    QString getEtat() const { return etat; }
    QString getLocalisation() const { return localisation; }
    QString getCouleur() const { return couleur; }
    int getQte() const { return qte; }

    // Setters
    void setId(QString i) { id_materiel = i; }
    void setNom(QString n) { nom = n; }
    void setType(QString t) { type = t; }
    void setEtat(QString e) { etat = e; }
    void setLocalisation(QString l) { localisation = l; }
    void setCouleur(QString c) { couleur = c; }
    void setQte(int q) { qte = q; }

    bool ajouter();
    bool modifier(QString, QString, QString, QString, QString, QString = "", int = 0);
    bool supprimer(QString);
    void afficher(QTableWidget* table); // <== déclaration obligatoire
    void afficherTrié(QTableWidget* table, const QString &sortBy); // Sort functionality
    void chercherParId(QTableWidget* table, const QString &id); // Search functionality
    void chercherParNom(QTableWidget* table, const QString &inom); // Search functionality
    void chercherParCouleur(QTableWidget* table, const QString &couleur); // Search by color
    static QString getMaterielNomByCouleur(const QString &couleur); // Get equipment name by color
};

#endif // MATERIEL_H
