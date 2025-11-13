#include "gestioncreateur.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include <QTableWidgetItem>
#include <QDebug>

GestionCreateur::GestionCreateur(Ui::MainWindow *ui_, QObject *parent)
    : QObject(parent), ui(ui_)
{
    ui->tab_9->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tab_9->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tab_9->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

    connect(ui->toolbuttajouter, &QToolButton::clicked, this, &GestionCreateur::ajouter);
    connect(ui->toolbutsupp, &QToolButton::clicked, this, &GestionCreateur::supprimer);
    connect(ui->toolbuttmodifier, &QToolButton::clicked, this, &GestionCreateur::modifier);
    connect(ui->toolbuttrecherche, &QToolButton::clicked, this, &GestionCreateur::rechercher);
    //connect(ui->toolbutttrier, &QToolButton::clicked, this, &GestionCreateur::trier);
    connect(ui->tab_9, &QTableWidget::cellChanged, this, &GestionCreateur::onCellChanged);

    afficher();
}

GestionCreateur::~GestionCreateur() {}

void GestionCreateur::ajouter()
{
    QString id = ui->lineid->text().trimmed();
    QString nom = ui->linenom->text().trimmed();
    QString prenom = ui->lineprenom->text().trimmed();
    QString pseudo = ui->linepseudo->text().trimmed();
    QString telephone = ui->linetelephone->text().trimmed();
    QString plat = ui->lineplat->text().trimmed();

    if (nom.isEmpty() || prenom.isEmpty() || pseudo.isEmpty()) {
        QMessageBox::warning(nullptr, "Champs obligatoires", "Veuillez remplir tous les champs requis.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO CREATEUR (ID_CREATEUR, NOM, PRENOM, PSEUDO, TELEPHONE, RESEAU) "
                  "VALUES (:id, :nom, :prenom, :pseudo, :tel, :reseau)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":pseudo", pseudo);
    query.bindValue(":tel", telephone);
    query.bindValue(":reseau", plat);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL (ajout)", query.lastError().text());
        return;
    }

    QMessageBox::information(nullptr, "Succès", "Créateur ajouté avec succès !");
    afficher();
}

void GestionCreateur::supprimer()
{
    QString id = ui->lineid->text().trimmed();

    if (id.isEmpty()) {
        QMessageBox::warning(nullptr, "Suppression", "Veuillez sélectionner un créateur à supprimer.");
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM CREATEUR WHERE ID_CREATEUR = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL (suppression)", query.lastError().text());
        return;
    }

    QMessageBox::information(nullptr, "Succès", "Créateur supprimé avec succès !");
    afficher();
}

void GestionCreateur::modifier()
{
    // ✅ This function *must exist* exactly like this to fix your linker error
    QMessageBox::information(nullptr, "Information",
                             "Les modifications se font directement dans le tableau (double clic sur une cellule).");
}

void GestionCreateur::rechercher()
{
    QString critere = ui->linerech->text().trimmed();
    QSqlQuery query;

    QString sql = "SELECT * FROM CREATEUR WHERE NOM LIKE :critere "
                  "OR PRENOM LIKE :critere "
                  "OR PSEUDO LIKE :critere "
                  "OR TELEPHONE LIKE :critere "
                  "OR RESEAU LIKE :critere";

    query.prepare(sql);
    query.bindValue(":critere", "%" + critere + "%");

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL (recherche)", query.lastError().text());
        return;
    }

    remplirTableAvecQuery(query);
}

void GestionCreateur::trier()
{
    QSqlQuery query;
    if (!query.exec("SELECT * FROM CREATEUR ORDER BY NOM ASC")) {
        QMessageBox::critical(nullptr, "Erreur SQL (tri)", query.lastError().text());
        return;
    }
    remplirTableAvecQuery(query);
}

void GestionCreateur::afficher()
{
    QSqlQuery query;
    if (!query.exec("SELECT * FROM CREATEUR ORDER BY ID_CREATEUR ASC")) {
        QMessageBox::critical(nullptr, "Erreur SQL (affichage)", query.lastError().text());
        return;
    }
    remplirTableAvecQuery(query);
}

void GestionCreateur::remplirTableAvecQuery(QSqlQuery &query)
{
    ui->tab_9->blockSignals(true);
    ui->tab_9->clearContents();
    ui->tab_9->setRowCount(0);
    ui->tab_9->setColumnCount(6);
    ui->tab_9->setHorizontalHeaderLabels(QStringList() << "ID" << "Nom" << "Prénom" << "Pseudo" << "Téléphone" << "Réseau");

    int row = 0;
    while (query.next()) {
        ui->tab_9->insertRow(row);
        for (int col = 0; col < 6; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            if (col == 0) // ID non modifiable
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            ui->tab_9->setItem(row, col, item);
        }
        ++row;
    }

    ui->tab_9->blockSignals(false);
}

void GestionCreateur::onCellChanged(int row, int column)
{
    if (column == 0) {
        QMessageBox::warning(nullptr, "Modification interdite", "L’ID ne peut pas être modifié !");
        afficher();
        return;
    }

    QString id = ui->tab_9->item(row, 0)->text();
    QString nom = ui->tab_9->item(row, 1)->text();
    QString prenom = ui->tab_9->item(row, 2)->text();
    QString pseudo = ui->tab_9->item(row, 3)->text();
    QString telephone = ui->tab_9->item(row, 4)->text();
    QString reseau = ui->tab_9->item(row, 5)->text();

    QSqlQuery query;
    query.prepare("UPDATE CREATEUR SET NOM = :nom, PRENOM = :prenom, PSEUDO = :pseudo, TELEPHONE = :tel, RESEAU = :reseau "
                  "WHERE ID_CREATEUR = :id");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":pseudo", pseudo);
    query.bindValue(":tel", telephone);
    query.bindValue(":reseau", reseau);
    query.bindValue(":id", id);

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Erreur SQL (modif tableau)", query.lastError().text());
        afficher();
    }
}
