#include "geremateriel.h"

GereMateriel::GereMateriel(QObject *parent) : QObject(parent) {}

// Vérifier les champs
bool GereMateriel::verifierChamps(Ui::MainWindow *ui)
{
    QString id = ui->id_materiel->text().trimmed();
    QString nom = ui->nom_materiel->text().trimmed();
    QString type = ui->type_materiel->text().trimmed();
    QString etat = ui->etat_materiel->text().trimmed();
    QString localisation = ui->localisation_materiel->text().trimmed();

    if (id.isEmpty() || nom.isEmpty() || type.isEmpty() || etat.isEmpty() || localisation.isEmpty()) {
        QMessageBox::warning(nullptr, "Champs manquants", "Tous les champs sont obligatoires !");
        return false;
    }

    return true;
}

// Ajouter
bool GereMateriel::ajouterMateriel(Ui::MainWindow *ui)
{
    if (!verifierChamps(ui)) return false;

    int row = ui->tab_materiel->rowCount();
    ui->tab_materiel->insertRow(row);

    ui->tab_materiel->setItem(row, 0, new QTableWidgetItem(ui->id_materiel->text()));
    ui->tab_materiel->setItem(row, 1, new QTableWidgetItem(ui->nom_materiel->text()));
    ui->tab_materiel->setItem(row, 2, new QTableWidgetItem(ui->type_materiel->text()));
    ui->tab_materiel->setItem(row, 3, new QTableWidgetItem(ui->etat_materiel->text()));
    ui->tab_materiel->setItem(row, 4, new QTableWidgetItem(ui->localisation_materiel->text()));

    reinitialiserFormulaire(ui);
    QMessageBox::information(nullptr, "Ajout réussi", "Matériel ajouté avec succès !");
    return true;
}

// Charger pour modification
void GereMateriel::chargerPourModification(Ui::MainWindow *ui)
{
    auto selected = ui->tab_materiel->currentRow();
    if (selected < 0) {
        QMessageBox::warning(nullptr, "Aucun élément", "Veuillez sélectionner un matériel à modifier.");
        return;
    }

    ui->id_materiel->setText(ui->tab_materiel->item(selected, 0)->text());
    ui->nom_materiel->setText(ui->tab_materiel->item(selected, 1)->text());
    ui->type_materiel->setText(ui->tab_materiel->item(selected, 2)->text());
    ui->etat_materiel->setText(ui->tab_materiel->item(selected, 3)->text());
    ui->localisation_materiel->setText(ui->tab_materiel->item(selected, 4)->text());
}

// Modifier
bool GereMateriel::modifierMateriel(Ui::MainWindow *ui)
{
    int selected = ui->tab_materiel->currentRow();
    if (selected < 0) {
        QMessageBox::warning(nullptr, "Aucun élément", "Veuillez sélectionner un matériel à modifier.");
        return false;
    }

    if (!verifierChamps(ui)) return false;

    ui->tab_materiel->setItem(selected, 0, new QTableWidgetItem(ui->id_materiel->text()));
    ui->tab_materiel->setItem(selected, 1, new QTableWidgetItem(ui->nom_materiel->text()));
    ui->tab_materiel->setItem(selected, 2, new QTableWidgetItem(ui->type_materiel->text()));
    ui->tab_materiel->setItem(selected, 3, new QTableWidgetItem(ui->etat_materiel->text()));
    ui->tab_materiel->setItem(selected, 4, new QTableWidgetItem(ui->localisation_materiel->text()));

    QMessageBox::information(nullptr, "Modification", "Matériel modifié avec succès !");
    reinitialiserFormulaire(ui);
    return true;
}

// Supprimer
bool GereMateriel::supprimerMateriel(Ui::MainWindow *ui)
{
    int selected = ui->tab_materiel->currentRow();
    if (selected < 0) {
        QMessageBox::warning(nullptr, "Aucun élément", "Veuillez sélectionner un matériel à supprimer.");
        return false;
    }

    auto confirm = QMessageBox::question(nullptr, "Confirmation", "Supprimer ce matériel ?", QMessageBox::Yes | QMessageBox::No);
    if (confirm == QMessageBox::Yes) {
        ui->tab_materiel->removeRow(selected);
        QMessageBox::information(nullptr, "Suppression", "Matériel supprimé avec succès !");
        return true;
    }
    return false;
}

// Réinitialiser
void GereMateriel::reinitialiserFormulaire(Ui::MainWindow *ui)
{
    ui->id_materiel->clear();
    ui->nom_materiel->clear();
    ui->type_materiel->clear();
    ui->etat_materiel->clear();
    ui->localisation_materiel->clear();
    ui->tab_materiel->clearSelection();
}

// Exporter CSV
void GereMateriel::exporterCSV(Ui::MainWindow *ui)
{
    if (ui->tab_materiel->rowCount() == 0) {
        QMessageBox::warning(nullptr, "Export", "Aucune donnée à exporter !");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(nullptr, "Exporter CSV", QDir::homePath() + "/materiel.csv", "CSV (*.csv)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(nullptr, "Erreur", "Impossible d'ouvrir le fichier !");
        return;
    }

    QTextStream out(&file);
    for (int row = 0; row < ui->tab_materiel->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < ui->tab_materiel->columnCount(); ++col) {
            rowData << ui->tab_materiel->item(row, col)->text();
        }
        out << rowData.join(";") << "\n";
    }

    file.close();
    QMessageBox::information(nullptr, "Export réussi", "Les données ont été exportées dans :\n" + fileName);
}
