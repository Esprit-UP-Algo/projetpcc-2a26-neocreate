#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QToolButton>
#include <QTableWidget>
#include <QRadioButton>
#include <QDateEdit>
#include <QComboBox>
#include <QButtonGroup>
#include "client.h"    // <-- contient struct Client + ClientDAO
#include "projet.h"   // <-- contient class Projet
#include "staff.h"    // <-- contient class Staff
#include "materiel.h" // <-- contient class Materiel
#include "sponsor.h"  // <-- contient class Sponsor

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Navigation (si tu les utilises dans ton UI)
    void showStaff();
    void showClient();
    void showMateriel();
    void showProjet();
    void showSponsor();
    void showCreateur();

    // CRUD CLIENT (boutons de l'UI)
    void on_id_confirm_clicked();  // Add / Update
    void on_id_delete_clicked();   // Delete via line_id

    // CRUD PROJET (boutons de l'UI)
    void on_toolButton_52_clicked();  // Ajouter / Modifier projet
    void on_toolButton_56_clicked();  // Afficher projets
    void on_toolButton_57_clicked();  // Supprimer projet
    void on_toolButton_58_clicked();  // Éditer projet (remplit le formulaire)
    void on_toolButton_53_clicked();  // Annuler (réinitialise le formulaire)
    void on_comboBox_12_currentTextChanged(const QString &text);  // Trier projets
    void on_toolButton_54_clicked();  // Rechercher projet par ID

    // CRUD STAFF (boutons de l'UI)
    void on_toolButton_15_clicked();  // Ajouter / Modifier staff
    void on_toolButton_23_clicked();  // Afficher staff
    void on_toolButton_25_clicked();  // Supprimer staff
    void on_toolButton_26_clicked();  // Éditer staff (remplit le formulaire)
    void on_staffCancelForm_clicked(); // Annuler formulaire staff
    void on_toolButton_27_clicked();   // Rechercher staff par ID
    void on_comboBox_currentTextChanged(const QString &text); // Trier staff
    void on_pdf_clicked();

    // CRUD MATERIEL (boutons de l'UI)
    void on_toolButton_31_clicked();  // Ajouter / Modifier matériel
    void on_toolButton_33_clicked();  // Afficher matériels
    void on_toolButton_34_clicked();  // Annuler formulaire matériel
    void on_toolButton_35_clicked();  // Supprimer matériel
    void on_toolButton_36_clicked();  // Rechercher matériel par ID (updated)
    void on_comboBox_4_currentTextChanged(const QString &text); // Trier matériel

    // CRUD SPONSOR (boutons de l'UI)
    void on_toolButton_11_clicked();  // Ajouter sponsor
    void on_toolButton_12_clicked();  // Annuler formulaire sponsor (clear form)
    void on_toolButton_59_clicked();  // Modifier sponsor (edit after select row)
    void on_toolButton_62_clicked();  // Supprimer sponsor (delete after select row)
    void on_toolButton_9_clicked();   // Rechercher sponsor par ID
    void on_toolButton_17_clicked();  // Afficher tous les sponsors
    void on_comboBox_5_currentTextChanged(const QString &text); // Trier sponsor

private:
    Ui::MainWindow *ui;

    // ---- CLIENT helpers ----
    void setupTabClient();                 // prépare QTableWidget
    void refreshClientsGrid();             // SELECT -> remplit tableau
    void addClientEditPenForRow(int row);  // stylo pour activer l'édition
    void populateClientFormFromRow(int row);
    void setClientFormMode(bool edit);
    Client readClientForm() const;

    // Setup button groups
    void setupButtonGroups();

    // ---- PROJET helpers ----
    void setupTabProjet();                 // prépare QTableWidget
    void refreshProjetsGrid();             // SELECT -> remplit tableau avec QSqlQueryModel
    Projet readProjetForm() const;         // lit les champs du formulaire
    void clearProjetForm();                // vide le formulaire
    void populateProjetFormFromRow(int row); // remplit le formulaire depuis une ligne du tableau
    void setProjetFormMode(bool edit);     // définit le mode édition/ajout

    // ---- STAFF helpers ----
    void setupTabStaff();                  // prépare QTableWidget pour staff
    void refreshStaffGrid();               // SELECT -> remplit tableau staff
    Staff readStaffForm() const;           // lit les champs du formulaire staff
    void clearStaffForm();                 // vide le formulaire staff
    void populateStaffFormFromRow(int row); // remplit le formulaire depuis une ligne du tableau
    void setStaffFormMode(bool edit);      // définit le mode édition/ajout staff
    void addStaffEditPenForRow(int row);   // ajoute le bouton edit pour chaque ligne
    void exporterTableWidgetVersHTML();
    void afficherStatistiquesDansGroupBox();
    void mettreAJourStatistiques();
    QMap<QString, int> compterEmployesParPoste();


    // ---- MATERIEL helpers ----
    void setupTabMateriel();               // prépare QTableWidget pour matériel
    void refreshMaterielGrid();            // SELECT -> remplit tableau matériel
    Materiel readMaterielForm() const;     // lit les champs du formulaire matériel
    void clearMaterielForm();              // vide le formulaire matériel
    void populateMaterielFormFromRow(int row); // remplit le formulaire depuis une ligne du tableau
    void setMaterielFormMode(bool edit);   // définit le mode édition/ajout matériel
    void addMaterielEditPenForRow(int row); // ajoute le bouton edit pour chaque ligne matériel
    void initializeStaffSortComboBox(); // initialise le comboBox de tri staff

    // ---- SPONSOR helpers ----
    void setupTabSponsor();                // prépare QTableWidget pour sponsor
    void refreshSponsorGrid();             // SELECT -> remplit tableau sponsor
    Sponsor readSponsorForm() const;       // lit les champs du formulaire sponsor
    Sponsor readSponsorFormFromRow(int row) const; // lit les données depuis une ligne du tableau
    void clearSponsorForm();               // vide le formulaire sponsor
    void populateSponsorFormFromRow(int row); // remplit le formulaire depuis une ligne du tableau
    void setSponsorFormMode(bool edit);    // définit le mode édition/ajout sponsor
    void searchSponsorById();              // recherche sponsor par ID
    void sortSponsors();                   // tri les sponsors par date
    // removed per-row edit buttons; editing is done by selecting row then clicking toolButton_59

    bool m_clientTableInit = false;
    bool m_clientEditMode  = false;
    bool m_projetEditMode  = false;
    bool m_staffEditMode   = false;
    bool m_materielEditMode = false;
    bool m_sponsorEditMode = false;

    // Button groups for Materiel radio buttons
    QButtonGroup* m_materielEtatGroup;
    QButtonGroup* m_materielLocationGroup;
    QButtonGroup* m_staffCompetenceGroup;
};

#endif // MAINWINDOW_H
