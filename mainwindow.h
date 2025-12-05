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
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include "client.h"    // <-- contient struct Client + ClientDAO
#include "projet.h"   // <-- contient class Projet
#include "staff.h"    // <-- contient class Staff
#include "materiel.h" // <-- contient class Materiel
#include "sponsor.h"  // <-- contient class Sponsor
#include "sponsormanager.h"
#include "chatwindow.h"
#include "geminimanager.h"
#include "gestioncreateur.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QtGui>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QClipboard>
#include <QApplication>
#include <QRegularExpression>
#include "connection.h"
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

class PieChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PieChartWidget(QWidget *parent = nullptr);
    void setData(const QMap<QString, int> &data, int total);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QMap<QString, int> m_data;
    int m_total;
    QMap<QString, QColor> m_colors;

};
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
    void updateNavigationStyle(int activeIndex);

    // CRUD CLIENT (boutons de l'UI)
    void on_id_confirm_clicked();  // Add / Update
    void on_id_delete_clicked();    // Delete via line_id
    void on_toolButton_5_clicked();
    void on_comboBox_15_currentTextChanged(const QString &text);
    void on_btnCheckSuivi_clicked();
    void on_btn_export_clients_clicked();

    void on_btn_clientStats_clicked();
    void buildClientStatsCharts();

    // CRUD PROJET (boutons de l'UI)
    void on_toolButton_52_clicked();  // Ajouter / Modifier projet
    void on_toolButton_56_clicked();  // Afficher projets
    void on_toolButton_57_clicked();  // Supprimer projet
    void on_toolButton_58_clicked();  // Éditer projet (remplit le formulaire)
    void on_toolButton_53_clicked();  // Annuler (réinitialise le formulaire)
    void on_comboBox_12_currentTextChanged(const QString &text);  // Trier projets
    void on_toolButton_54_clicked();  // Rechercher projet par ID
    void on_toolButton_55_clicked();

    void on_btn_refresh_stats_clicked(); // Refresh project statistics

    void onFlashTimer(); // toggle flashing rows

    // CRUD STAFF (boutons de l'UI)
    void on_toolButton_15_clicked();  // Ajouter / Modifier staff
    void on_toolButton_23_clicked();  // Afficher staff
    void on_toolButton_25_clicked();  // Supprimer staff
    void on_toolButton_26_clicked();  // Éditer staff (remplit le formulaire)
    void on_staffCancelForm_clicked(); // Annuler formulaire staff
    void on_comboBox_currentTextChanged(const QString &text); // Trier staff
    void on_pdf_clicked();
    void rechercherStaff();
    //void setupIntelligentCalendar();
    // CRUD MATERIEL (boutons de l'UI)
    void on_toolButton_31_clicked();  // Ajouter / Modifier matériel
    void on_toolButton_33_clicked();  // Afficher matériels
    void on_toolButton_34_clicked();  // Annuler formulaire matériel
    void on_toolButton_35_clicked();  // Supprimer matériel
    void on_toolButton_36_clicked();  // Rechercher matériel par ID (updated)
    void on_comboBox_4_currentTextChanged(const QString &text); // Trier matériel
    void on_toolButton_68_clicked();
    void onTableMaterielSelectionChanged();

    // CRUD SPONSOR (boutons de l'UI)
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


    void on_toolButton_11_clicked();

private:
    Ui::MainWindow *ui;
    Staff *staff;
    QString currentSponsorId;
    // ---- CLIENT helpers ----
    void setupTabClient();                 // prépare QTableWidget
    void refreshClientsGrid();             // SELECT -> remplit tableau
    void addClientEditPenForRow(int row);  // stylo pour activer l'édition
    void populateClientFormFromRow(int row);
    void setClientFormMode(bool edit);
    Client readClientForm() const;

    // Setup button groups
    void setupButtonGroups();
    QChartView *m_clientStatsView = nullptr;

    // ---- PROJET helpers ----
    void setupTabProjet();                 // prépare QTableWidget
    void refreshProjetsGrid();             // SELECT -> remplit tableau avec QSqlQueryModel
    Projet readProjetForm() const;         // lit les champs du formulaire
    void clearProjetForm();                // vide le formulaire
    void populateProjetFormFromRow(int row); // remplit le formulaire depuis une ligne du tableau
    void setProjetFormMode(bool edit);     // définit le mode édition/ajout
    void updateProjetStatistics();         // refresh pie chart + summary labels for projets
    void setupProjetStatisticsUI();        // setup statistics UI in tab_14
    void displayProjetStatistics();        // display project statistics in tab_14
    void displayProjetPieCharts(const QVector<QPair<QString,int>>& countsByType,
                               const QVector<QPair<QString,double>>& montantByPaiment,
                               int totalProjects, double totalMontant);

    // ---- STAFF helpers ----
    void setupTabStaff();                  // prépare QTableWidget pour staff
    void refreshStaffGrid();               // SELECT -> remplit tableau staff
    Staff readStaffForm() const;           // lit les champs du formulaire staff
    void clearStaffForm();                 // vide le formulaire staff
    void populateStaffFormFromRow(int row); // remplit le formulaire depuis une ligne du tableau
    void setStaffFormMode(bool edit);      // définit le mode édition/ajout staff
    void addStaffEditPenForRow(int row);   // ajoute le bouton edit pour chaque ligne
    void exporterTableWidgetVersPDF();
    void afficherStatistiquesDansGroupBox();
    void mettreAJourStatistiques();
    QMap<QString, int> compterEmployesParPoste();
    QMap<QString, int> compterEmployesParCompetence();
    void afficherStatistiquesCompetencesDansGroupBox4();
    void mettreAJourStatistiquesCompetences();
    //CalendarWidget *m_calendarWidget;
    // ---- MATERIEL helpers ----
    void setupTabMateriel();
    void refreshMaterielGrid();
    Materiel readMaterielForm() const;
    void clearMaterielForm();
    void populateMaterielFormFromRow(int row);
    void setMaterielFormMode(bool edit);
    void addMaterielEditPenForRow(int row);
    void initializeStaffSortComboBox();
    QMap<QString, int> compterMaterielParEtat();
    QMap<QString, int> compterMaterielParType();
    void afficherStatistiquesMateriel();
    void afficherPieChartDansGroupBox(QGroupBox *groupBox, const QMap<QString, int> &stats, int total, const QString &title);
    void ajouterLegendeSimple(QVBoxLayout *layout, const QMap<QString, int> &stats, int total);

    void afficherQRCodePourLigne(int row);
    void genererQRCode(const QString &data);
    QString getInfoMaterielPourQR(int row);
    bool materielEstUtiliseDansProjet(const QString &idMateriel);
    QString getProjetUtilisateur(const QString &idMateriel);
    void afficherErreurQR(QLabel *qrLabel, QVBoxLayout *layout, const QString &message);
    void afficherDonneesQR(QVBoxLayout *layout, const QString &data);
    bool m_blockQRRefresh = false;
private:
    // ... tes autres fonctions ...

    QString getProjetUtilisateurPourQR(const QString &idMateriel);
    void genererQRCodeImage(QLabel *qrLabel, const QString &data);
    int m_derniereLigneQR = -1;
    bool m_qrCodeEnCours = false;

    class PieChartWidget *m_pieChartEtat;
    class PieChartWidget *m_pieChartType;
    void ajouterLegendeMateriel(QHBoxLayout *mainLayout,
                                const QMap<QString, int> &statsEtat,
                                const QMap<QString, int> &statsType);
    void ajouterItemsLegende(QVBoxLayout *layout,
                             const QMap<QString, int> &stats,
                             int total);
    // ---- SPONSOR helpers ----

    // removed per-row edit buttons; editing is done by selecting row then clicking toolButton_59

    // AI Predictor setup
    void setupAIPredictorUI();

    bool m_clientTableInit = false;
    bool m_clientEditMode  = false;
    bool m_projetEditMode  = false;
    bool m_staffEditMode   = false;
    bool m_materielEditMode = false;
    SponsorManager *sponsorManager;
    QString m_sponsorRenouvele;


    // Button groups for Materiel radio buttons
    QButtonGroup* m_materielEtatGroup;
    QButtonGroup* m_materielLocationGroup;
    QButtonGroup* m_staffCompetenceGroup;

    // Chart view for projets (created at runtime) - keep as QWidget pointer to avoid QtCharts in header
    QWidget* m_projetChartView = nullptr;
    QWidget* m_projetChartView2 = nullptr; // chart for montant by payment
    QTimer* m_flashTimer = nullptr;
    QVector<int> m_flashingRows; // rows that should flash (one-day remaining)

    // AI Predictor components
    QProcess* m_aiProcess = nullptr;
    QTextEdit* m_predictionDisplay = nullptr;
    QPushButton* m_predictButton = nullptr;
    QGroupBox* m_aiGroupBox = nullptr;
    bool m_flashOn = false;
};

#endif // MAINWINDOW_H
