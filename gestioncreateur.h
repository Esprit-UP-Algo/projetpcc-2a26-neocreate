#ifndef GESTIONCREATEUR_H
#define GESTIONCREATEUR_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTableWidget>
#include <QAbstractItemView>

namespace Ui {
class MainWindow;
}

class GestionCreateur : public QObject
{
    Q_OBJECT
public:
    explicit GestionCreateur(Ui::MainWindow *ui, QObject *parent = nullptr);
    ~GestionCreateur();

public slots:
    void afficher();     // Afficher tous les enregistrements

private slots:
    void ajouter();      // Ajouter un nouveau créateur
    void supprimer();    // Supprimer un créateur sélectionné
    void modifier();     // (optionnel) existe pour les connexions, peut rester vide
    void rechercher();   // Rechercher un créateur
    void trier();        // Trier les créateurs

    // IMPORTANT : déclaration du slot appelé quand une cellule change
    void onCellChanged(int row, int column);

private:
    Ui::MainWindow *ui;

    // Fonction utilitaire pour remplir le tableau à partir d'une requête SQL
    void remplirTableAvecQuery(QSqlQuery &query);
};

#endif // GESTIONCREATEUR_H
