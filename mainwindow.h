#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qtablewidget.h"
#include <QMainWindow>
#include <QPushButton>
#include <QList>
#include "materiel.h"

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
    void showStaff();
    void showClient();
    void showMateriel();
    void showProjet();
    void showSponsor();
    void showCreateur();
    void afficherTableau();
    void on_ajouter_clicked();
    void on_modifier_clicked();
    void on_supprimer_clicked();
    void on_afficher_clicked();
    void on_chercher_2_clicked();
    QString recupererEtat();
    QString recupererLocalisation();
    void on_exporter_clicked();


    void on_tableWidget_4_itemClicked(QTableWidgetItem *item);


private:
    Ui::MainWindow *ui;
    QList<Materiel> listeMateriel;




};

#endif // MAINWINDOW_H
