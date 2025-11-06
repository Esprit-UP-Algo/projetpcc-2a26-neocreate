#ifndef GEREMATERIEL_H
#define GEREMATERIEL_H

#include <QObject>
#include <QTableWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include "ui_mainwindow.h"

class GereMateriel : public QObject
{
    Q_OBJECT

public:
    explicit GereMateriel(QObject *parent = nullptr);

    // Vérifications
    static bool verifierChamps(Ui::MainWindow *ui);

    // CRUD
    static bool ajouterMateriel(Ui::MainWindow *ui);
    static bool modifierMateriel(Ui::MainWindow *ui);
    static bool supprimerMateriel(Ui::MainWindow *ui);

    // Outils
    static void chargerPourModification(Ui::MainWindow *ui);
    static void exporterCSV(Ui::MainWindow *ui);
    static void reinitialiserFormulaire(Ui::MainWindow *ui);
};

#endif // GEREMATERIEL_H
