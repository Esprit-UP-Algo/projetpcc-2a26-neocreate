#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "client.h"
#include "projet.h"
#include "staff.h"
#include "gestioncreateur.h"
#include "sponsormanager.h"




  // ✅ Exactement le nom du bouton
class Staff;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showStaff();
    void showClient();
    void showMateriel();
    void showProjet();
    void showSponsor();
    void showCreateur();
    // Gestion matériel
    void on_ajouter_clicked();
    void on_modifier_clicked();
    void on_supprimer_clicked();
    void on_afficher_clicked();
    void on_chercher_2_clicked();
    void on_exporter_clicked();
    void on_annuler_clicked();
    void on_comboBox_7_currentIndexChanged(int index);
    void on_tableWidget_4_itemClicked(QTableWidgetItem *item);
    // CRUD CLIENT (boutons de l'UI)
    void on_id_confirm_clicked();  // Add / Update
    void on_id_delete_clicked();   // Delete via line_id

    // ---- CLIENT helpers ----
    void setupTabClient();                 // prépare QTableWidget
    void refreshClientsGrid();             // SELECT -> remplit tableau
    void addClientEditPenForRow(int row);  // stylo pour activer l'édition
    void populateClientFormFromRow(int row);
    void setClientFormMode(bool edit);
    Client readClientForm() const;
    // CRUD PROJET (boutons de l'UI)
    void on_toolButton_52_clicked();  // Ajouter / Modifier projet
    void on_toolButton_56_clicked();  // Afficher projets
    void on_toolButton_57_clicked();  // Supprimer projet
    void on_toolButton_58_clicked();  // Éditer projet (remplit le formulaire)
    void on_toolButton_53_clicked();  // Annuler (réinitialise le formulaire)

    // ---- PROJET helpers ----
    void setupTabProjet();                 // prépare QTableWidget
    void refreshProjetsGrid();             // SELECT -> remplit tableau avec QSqlQueryModel
    Projet readProjetForm() const;         // lit les champs du formulaire
    void clearProjetForm();                // vide le formulaire
    void populateProjetFormFromRow(int row); // remplit le formulaire depuis une ligne du tableau
    void setProjetFormMode(bool edit);     // définit le mode édition/ajout
    // CRUD Sponsor
    void on_AjouterSponsor_clicked();
    void on_ModifierSponsor_clicked();
    void on_SupprimerSponsor_clicked();
    void on_AfficherSponsor_clicked();
    void on_AnnulerSponsor_clicked();
    void on_RechercherSponsor_clicked();
    void on_tableWidget_2_cellClicked(int row, int column);
    void on_btnIA_clicked();
    void lancerNotificationDemarrage();
    void on_comboBox_tri_currentIndexChanged(int index);
    void setSponsorRenouvele(const QString& sponsorId) { m_sponsorRenouvele = sponsorId; }
    void clearSponsorRenouvele() { m_sponsorRenouvele.clear(); }
    QString getSponsorRenouvele() const { return m_sponsorRenouvele; }

private:

    // Méthodes utilitaires UI seulement
    QString recupererEtat() const;
    QString recupererLocalisation() const;
    void viderChamps();
    bool m_clientTableInit = false;
    bool m_clientEditMode  = false;
    bool m_projetEditMode  = false;
    SponsorManager *sponsorManager;
    QString m_sponsorRenouvele;


    Ui::MainWindow *ui;
    Staff *staff;
    QString currentSponsorId;  // ← AJOUTER CETTE LIGNE
    GestionCreateur *gestionCreateur;
};

#endif // MAINWINDOW_H
