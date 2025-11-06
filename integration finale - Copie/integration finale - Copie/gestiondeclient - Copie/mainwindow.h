#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlError>
#include "ui_mainwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // Déclarations des fonctions que tu utilises
    QString genererIDNumerique();
    bool verifierNomOuPrenom(const QString &texte);
    bool idExisteDeja(const QString &id);
private slots:
    void afficherParID();   // 🔹 déclaration du slot pour ton bouton "Afficher"
private slots:
    void onTableItemChanged(QTableWidgetItem *item);

private slots:
    void on_btnQuitter_clicked();
    void on_btnStaff_clicked();
    void on_btnConnecter_clicked();
private slots:
    void showStaff();
    void showClient();
    void showMateriel();
    void showProjet();
    void showSponsor();
    void showCreateur();
private slots:
    void afficherStaff();                   // Affiche le contenu de la table staff                    // Ajout d’un nouvel employé
    void supprimerStaff();                  // Suppression d’un employé
    void activerModeModification();         // Active l’édition directe de la ligne sélectionnée
    void modifierStaff();                   // Enregistre la modification dans la base
    void miseAJourCellule(int row, int column);          // Optionnel : maj cellule spécifique
    void remplirChampsDepuisTableau(int row, int column); // Optionnel : remplit les champs lors du clic
private slots:
    void rechercherStaff();  // 🔍 Recherche par ID
private slots:
    void on_toolButtonAjouter_clicked();   // ✅ Ajout du slot pour le bouton Ajouter
private:
    Ui::MainWindow *ui;
    bool m_ignoreCellChanged = false;
};

#endif // MAINWINDOW_H
