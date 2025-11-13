#ifndef STAFFSQL_H
#define STAFFSQL_H

#include <QObject>
#include <QLineEdit>
#include <QTableWidget>
#include <QModelIndex>
#include <QComboBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QTimer>
class StaffSQL : public QObject
{
    Q_OBJECT

public:
    explicit StaffSQL(QObject* parent = nullptr);

    // Fonctions CRUD
    void ConfS(QLineEdit* ui_id, QLineEdit* ui_nom, QLineEdit* ui_prenom,
               QComboBox* ui_poste, QLineEdit* ui_tel, QLineEdit* ui_email,
               QLineEdit* ui_pass, const QString& competence, QString& currID);

    void modifS(QLineEdit* ui_id, QLineEdit* ui_nom, QLineEdit* ui_prenom,
                QComboBox* ui_poste, QLineEdit* ui_tel, QLineEdit* ui_email,
                QLineEdit* ui_pass, const QString& competence, QString& currID);

    void suppS(QString& currID, QTableWidget* table);

    QString tabClick(const QModelIndex &index, QLineEdit* ui_id, QLineEdit* ui_nom,
                     QLineEdit* ui_prenom, QComboBox* ui_poste, QLineEdit* ui_tel,
                     QLineEdit* ui_email, QLineEdit* ui_pass, QString& competence,
                     QTableWidget* table);

    void refTab(QTableWidget* ui_table_staff);

    bool chercheID(const QString& id, const QString& suppID = "");
    void trierTab(QTableWidget* table, const QString& critere);
    void rech(QTableWidget* table, const QString& nom);
};

#endif // STAFFSQL_H
