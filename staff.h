#ifndef STAFF_H
#define STAFF_H

#include <QMainWindow>
#include <QString>
#include <QDate>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QTableWidget>
#include <QRadioButton>
#include <QTimer>
#include <QToolButton>
#include <QItemDelegate>  // ✅ AJOUTER
#include <QStyleOptionViewItem>  // ✅ AJOUTER
#include <QModelIndex>
class StaffSQL;  // CHANGÉ EN StaffSQL
// ✅ CLASSE CORRIGÉE
class ReadOnlyDelegate : public QItemDelegate
{
public:
    ReadOnlyDelegate(QObject* parent = nullptr) : QItemDelegate(parent) {}

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const override
    {
        Q_UNUSED(parent)
        Q_UNUSED(option)
        Q_UNUSED(index)
        return nullptr; // Pas d'éditeur = lecture seule
    }
};
class Staff : public QMainWindow
{
    Q_OBJECT

public:
    Staff();
    bool verifS(const QString& id, const QString& nom, const QString& prenom,
                const QString& poste, const QString& tel, const QString& email,
                const QString& pass, const QString& competence);

    bool verifId(const QString& id);
    bool verifNomPrenom(const QString& nom, const QString& prenom);
    bool verifTel(const QString& tel);
    bool verifPoste(const QString& poste);
    bool verifPass(const QString& pass);
    bool verifEmail(const QString& email);

    void initS(QLineEdit* id, QLineEdit* nom, QLineEdit* prenom,
               QComboBox* poste, QLineEdit* tel, QLineEdit* email,
               QLineEdit* pass, QRadioButton* radio1, QRadioButton* radio2, QRadioButton* radio3);

    void affTab(QTableWidget* table);
    void initTab(QTableWidget *tab_staff);
    void initTrier(QComboBox* trier_e);
    void initRech(QLineEdit* taper_e);
    void initRechercheID(QLineEdit* lineEditD, QToolButton* toolButtonR); // Nouvelle fonction
    void initAfficherTout(QToolButton* toolButtonAff);
    void initAjouterButton(QToolButton* toolButtonAjouter);
public slots:
    void ConfS();
    void modifS();
    void suppS();
    void reinitS();
    void expoS();
    void tabClick(int row, int column);
    void trierS();
    void refTab();
    void onCellChanged(int row, int column);
private slots:
    void onToolButtonRClicked();
    void onToolButtonAffClicked();
    bool getCompetence(const QString& competence);

    void sauvegarderModification(int row, int column, const QString& newValue);  // ✅ AJOUTER CETTE LIGNE

private:
    QLineEdit* ui_id;
    QLineEdit* ui_nom;
    QLineEdit* ui_prenom;
    QComboBox* ui_poste;
    QLineEdit* ui_tel;
    QLineEdit* ui_email;
    QLineEdit* ui_pass;
    QRadioButton* ui_radio1;
    QRadioButton* ui_radio2;
    QRadioButton* ui_radio3;

    QTableWidget *table;
    QTableWidget *ui_table_ajout_S;
    QTableWidget *ui_tab_staff;
    QComboBox* ui_trier_e;
    QLineEdit* ui_taper_e;

    QString currId;
    StaffSQL* sqls;  // CHANGÉ EN StaffSQL

    QLineEdit* lineEditD;
    QToolButton* toolButtonR;
    QToolButton* toolButtonAff;
     bool m_isUpdating;
    QString getOriginalValueFromDB(int row, int column);
    void restaurerValeurDepuisBD(int row, int column);
    bool validationActive;
    bool m_isProgrammaticChange;
    void restaurerValeurOriginale(int row, int column);
    QToolButton* toolButtonAjouter;

};

#endif // STAFF_H
