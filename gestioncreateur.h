#ifndef GESTIONCREATEUR_H
#define GESTIONCREATEUR_H

#include <QObject>
#include <QSqlQuery>
#include <QTableWidget>
#include <QProcess>

// QtCharts (Qt6 – sans namespace)
#include <QChart>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class GestionCreateur : public QObject
{
    Q_OBJECT

public:
    explicit GestionCreateur(Ui::MainWindow *ui_, QObject *parent = nullptr);
    ~GestionCreateur();

    void afficher();
    void statistiques();

public slots:               // ← moved here
    void exporterPdf();      // ← NOW PUBLIC
    void plateformeDominante();
    void predire();
    void ajouter();
    void supprimer();
    void modifier();
    void rechercher();
    void trier();
    void onCellChanged(int row, int column);


private slots:

private:
    Ui::MainWindow *ui;

    QString tableToHtml();
    void remplirTableAvecQuery(QSqlQuery &q);

    int genererAbonnesAleatoire(); // auto-incrément abonnés
};

#endif // GESTIONCREATEUR_H
