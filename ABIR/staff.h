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
    QString mot_de_passe;


public:
    Staff(); // constructeur vide
    Staff(QString, QString, QString, QString, QString, QString, QString, QString);

    // Getters
    QString getId() const { return id; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getPoste() const { return poste; }
    QString getCompetence() const { return competence; }
    QString getTelephone() const { return telephone; }
    QString getEmail() const { return email; }
    QString getMotDePasse() const { return mot_de_passe; }
    
    // Setters
    void setId(const QString &id) { this->id = id; }
    void setNom(const QString &nom) { this->nom = nom; }
    void setPrenom(const QString &prenom) { this->prenom = prenom; }
    void setPoste(const QString &poste) { this->poste = poste; }
    void setCompetence(const QString &competence) { this->competence = competence; }
    void setTelephone(const QString &telephone) { this->telephone = telephone; }
    void setEmail(const QString &email) { this->email = email; }
    void setMotDePasse(const QString &mot_de_passe) { this->mot_de_passe = mot_de_passe; }
    
    // Méthodes CRUD
    bool ajouter();
    bool supprimer(QString);
    bool modifier();

    // Méthode optionnelle si tu veux afficher via QTableView plus tard
    QSqlQueryModel* afficher();
    
    // Validation
    static bool isValidEmail(const QString &email);
    
    // Search and Sort
    QSqlQueryModel* afficherTrié(const QString &sortBy);
    static QSqlQueryModel* chercherParId(const QString& id);
    static QSqlQueryModel* rechercherParNom(const QString& nom);
};

#endif // STAFF_H
