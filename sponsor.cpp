#include "sponsor.h"
#include <QRegularExpression>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QSqlDatabase>
#include <QSqlDriver>

// Constructeurs - COMME PROJET
Sponsor::Sponsor()
{
    id = "";
    nom = "";
    contribution = "";
    dateDebut = QDate::currentDate();
    dateFin = QDate::currentDate();
    email = "";
}

Sponsor::Sponsor(QString id, QString nom, QString contribution, QDate dateDebut, QDate dateFin, QString email)
{
    this->id = id;
    this->nom = nom;
    this->contribution = contribution;
    this->dateDebut = dateDebut;
    this->dateFin = dateFin;
    this->email = email;
}

// ----------------- AJOUTER - COMME PROJET -----------------
bool Sponsor::ajouter()
{
    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database();
    qDebug() << "[Sponsor::ajouter] DB open:" << db.isOpen() << ", driver:" << db.driverName();

    query.prepare("INSERT INTO SPONSOR (ID_SPONSOR, NOM, CONTRIBUTION, DATE_DEBUT, DATE_FIN, EMAIL) "
                  "VALUES (:id, :nom, :contribution, :dateDebut, :dateFin, :email)");

    qDebug() << "[Sponsor::ajouter] Parameters:"
             << "id=" << id
             << "nom=" << nom
             << "contribution=" << contribution
             << "dateDebut=" << dateDebut.toString("yyyy-MM-dd")
             << "dateFin=" << dateFin.toString("yyyy-MM-dd")
             << "email=" << email;

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":contribution", contribution);
    query.bindValue(":dateDebut", dateDebut);
    query.bindValue(":dateFin", dateFin);
    query.bindValue(":email", email);

    // Transaction - COMME PROJET
    bool startedTx = false;
    if (db.driver() && db.driver()->hasFeature(QSqlDriver::Transactions)) {
        startedTx = db.transaction();
        qDebug() << "[Sponsor::ajouter] Transaction started:" << startedTx;
    }

    bool ok = query.exec();
    if (!ok) {
        qWarning() << "[Sponsor::ajouter] Exec failed:" << query.lastError().text();
        if (startedTx) db.rollback();
        return false;
    }

    qDebug() << "[Sponsor::ajouter] Exec success, rowsAffected=" << query.numRowsAffected();

    if (startedTx) {
        if (!db.commit()) {
            qWarning() << "[Sponsor::ajouter] Commit failed:" << db.lastError().text();
            return false;
        }
        qDebug() << "[Sponsor::ajouter] Commit success";
    }

    return true;
}

// ----------------- MODIFIER - COMME PROJET -----------------
bool Sponsor::modifier()
{
    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database();
    qDebug() << "[Sponsor::modifier] DB open:" << db.isOpen() << ", ID:" << id;

    query.prepare("UPDATE SPONSOR SET NOM = :nom, CONTRIBUTION = :contribution, "
                  "DATE_DEBUT = :dateDebut, DATE_FIN = :dateFin, EMAIL = :email "
                  "WHERE ID_SPONSOR = :id");

    qDebug() << "[Sponsor::modifier] Parameters:"
             << "id=" << id
             << "nom=" << nom
             << "contribution=" << contribution
             << "dateDebut=" << dateDebut.toString("yyyy-MM-dd")
             << "dateFin=" << dateFin.toString("yyyy-MM-dd")
             << "email=" << email;

    query.bindValue(":nom", nom);
    query.bindValue(":contribution", contribution);
    query.bindValue(":dateDebut", dateDebut);
    query.bindValue(":dateFin", dateFin);
    query.bindValue(":email", email);
    query.bindValue(":id", id);

    // Transaction - COMME PROJET
    bool startedTx = false;
    if (db.driver() && db.driver()->hasFeature(QSqlDriver::Transactions)) {
        startedTx = db.transaction();
        qDebug() << "[Sponsor::modifier] Transaction started:" << startedTx;
    }

    bool ok = query.exec();
    if (!ok) {
        qWarning() << "[Sponsor::modifier] Exec failed:" << query.lastError().text();
        if (startedTx) db.rollback();
        return false;
    }

    int rowsAffected = query.numRowsAffected();
    qDebug() << "[Sponsor::modifier] Exec success, rowsAffected=" << rowsAffected;

    if (rowsAffected == 0) {
        qWarning() << "[Sponsor::modifier] Aucune ligne modifiée";
        if (startedTx) db.rollback();
        return false;
    }

    if (startedTx) {
        if (!db.commit()) {
            qWarning() << "[Sponsor::modifier] Commit failed:" << db.lastError().text();
            return false;
        }
        qDebug() << "[Sponsor::modifier] Commit success";
    }

    return true;
}

// ----------------- SUPPRIMER - COMME PROJET -----------------
bool Sponsor::supprimer(QString id)
{
    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database();
    qDebug() << "[Sponsor::supprimer] DB open:" << db.isOpen() << ", ID:" << id;

    // Vérifier existence - COMME PROJET
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(1) FROM SPONSOR WHERE ID_SPONSOR = :id");
    checkQuery.bindValue(":id", id);
    if (checkQuery.exec() && checkQuery.next()) {
        if (checkQuery.value(0).toInt() == 0) {
            qWarning() << "[Sponsor::supprimer] Sponsor avec ID" << id << "n'existe pas";
            return false;
        }
    }

    // Transaction - C
    bool startedTx = false;
    if (db.driver() && db.driver()->hasFeature(QSqlDriver::Transactions)) {
        startedTx = db.transaction();
        qDebug() << "[Sponsor::supprimer] Transaction started:" << startedTx;
    }

    query.prepare("DELETE FROM SPONSOR WHERE ID_SPONSOR = :id");
    query.bindValue(":id", id);

    bool ok = query.exec();
    if (!ok) {
        qWarning() << "[Sponsor::supprimer] Exec failed:" << query.lastError().text();
        if (startedTx) db.rollback();
        return false;
    }

    int rowsAffected = query.numRowsAffected();
    qDebug() << "[Sponsor::supprimer] Exec success, rowsAffected=" << rowsAffected;

    if (rowsAffected == 0) {
        qWarning() << "[Sponsor::supprimer] Aucune ligne supprimée";
        if (startedTx) db.rollback();
        return false;
    }

    if (startedTx) {
        if (!db.commit()) {
            qWarning() << "[Sponsor::supprimer] Commit failed:" << db.lastError().text();
            return false;
        }
        qDebug() << "[Sponsor::supprimer] Commit success";
    }

    return true;
}

// ----------------- AFFICHER TABLEAU - COMME PROJET -----------------
void Sponsor::afficherDansTableau(QTableWidget* tableWidget)
{
    QSqlQuery query("SELECT ID_SPONSOR, NOM, CONTRIBUTION, DATE_DEBUT, DATE_FIN, EMAIL FROM SPONSOR ORDER BY ID_SPONSOR");

    tableWidget->clear();
    tableWidget->setRowCount(0);

    // Configuration des colonnes
    QStringList headers = {"ID", "Nom", "Contribution", "Date Début", "Date Fin", "Email"};
    tableWidget->setColumnCount(headers.size());
    tableWidget->setHorizontalHeaderLabels(headers);

    // Remplissage des données
    int row = 0;
    while (query.next()) {
        tableWidget->insertRow(row);

        for (int col = 0; col < headers.size(); ++col) {
            QString text = query.value(col).toString();

            // Formater les dates
            if (col == 3 || col == 4) {
                QDate date = query.value(col).toDate();
                text = date.isValid() ? date.toString("dd/MM/yyyy") : "";
            }

            QTableWidgetItem* item = new QTableWidgetItem(text);
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            tableWidget->setItem(row, col, item);
        }
        row++;
    }

    // ▼▼▼▼▼ AJUSTEMENTS DE TAILLE SEULEMENT ▼▼▼▼▼

    // Étirer les colonnes pour prendre toute la largeur
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Ajuster la hauteur des lignes
    tableWidget->verticalHeader()->setDefaultSectionSize(40);

    // Garder toutes les lignes blanches
    tableWidget->setAlternatingRowColors(false);

    qDebug() << "[Sponsor::afficherDansTableau] Tableau rafraîchi:" << row << "lignes";
}
// ----------------- RECHERCHER PAR ID  -----------------
bool Sponsor::rechercherParId(QString id, QString& nom, QString& contribution,
                              QDate& dateDebut, QDate& dateFin, QString& email)
{
    QSqlQuery query;
    query.prepare("SELECT NOM, CONTRIBUTION, DATE_DEBUT, DATE_FIN, EMAIL FROM SPONSOR WHERE ID_SPONSOR = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        nom = query.value(0).toString();
        contribution = query.value(1).toString();
        dateDebut = query.value(2).toDate();
        dateFin = query.value(3).toDate();
        email = query.value(4).toString();

        qDebug() << "[Sponsor::rechercherParId] Sponsor trouvé - ID:" << id << "Nom:" << nom;
        return true;
    }

    qDebug() << "[Sponsor::rechercherParId] Aucun sponsor trouvé avec ID:" << id;
    return false;
}
// ================= TRI PAR NOM =================
void Sponsor::trierParNom(QTableWidget* tableWidget)
{
    if (!tableWidget) return;

    qDebug() << "🔄 Tri par ordre alphabétique des noms...";


    QList<QStringList> donnees;

    // Récupérer toutes les données du tableau
    int rowCount = tableWidget->rowCount();
    int colCount = tableWidget->columnCount();

    for (int row = 0; row < rowCount; ++row) {
        QStringList ligne;
        for (int col = 0; col < colCount; ++col) {
            QTableWidgetItem* item = tableWidget->item(row, col);
            ligne << (item ? item->text() : "");
        }
        donnees.append(ligne);
    }

    // Trier par nom (colonne 1)
    std::sort(donnees.begin(), donnees.end(), [](const QStringList &a, const QStringList &b) {
        if (a.size() > 1 && b.size() > 1) {
            return a[1].toLower() < b[1].toLower(); // Tri case-insensitive
        }
        return false;
    });

    // Vider et remplir le tableau avec les données triées
    tableWidget->setRowCount(0);

    for (int row = 0; row < donnees.size(); ++row) {
        tableWidget->insertRow(row);
        for (int col = 0; col < donnees[row].size(); ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(donnees[row][col]);
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            tableWidget->setItem(row, col, item);
        }
    }

    qDebug() << "✅ Tableau trié par ordre alphabétique des noms";
}
// ▼▼▼▼▼▼▼▼▼▼ NOUVELLES FONCTIONS À AJOUTER ▼▼▼▼▼▼▼▼▼▼

// ----------------- RECHERCHE PAR NOM -----------------
void Sponsor::rechercherParNom(QTableWidget* tableWidget, const QString& nomRecherche)
{
    if (!tableWidget) return;

    QSqlQuery query;
    query.prepare("SELECT ID_SPONSOR, NOM, CONTRIBUTION, DATE_DEBUT, DATE_FIN, EMAIL FROM SPONSOR "
                  "WHERE UPPER(NOM) LIKE UPPER(:nom) ORDER BY NOM");
    query.bindValue(":nom", "%" + nomRecherche + "%");

    // Vider le tableau
    tableWidget->clear();
    tableWidget->setRowCount(0);

    // Configuration des colonnes
    QStringList headers = {"ID", "Nom", "Contribution", "Date Début", "Date Fin", "Email"};
    tableWidget->setColumnCount(headers.size());
    tableWidget->setHorizontalHeaderLabels(headers);

    if (!query.exec()) {
        qWarning() << "[Sponsor::rechercherParNom] Erreur requête:" << query.lastError().text();
        return;
    }

    // Remplissage des données
    int row = 0;
    while (query.next()) {
        tableWidget->insertRow(row);

        for (int col = 0; col < headers.size(); ++col) {
            QString text = query.value(col).toString();

            // Formater les dates
            if (col == 3 || col == 4) {
                QDate date = query.value(col).toDate();
                text = date.isValid() ? date.toString("dd/MM/yyyy") : "";
            }

            QTableWidgetItem* item = new QTableWidgetItem(text);
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            tableWidget->setItem(row, col, item);
        }
        row++;
    }

    tableWidget->setAlternatingRowColors(false);
    qDebug() << "[Sponsor::rechercherParNom] Recherche terminée:" << row << "sponsors trouvés pour le nom:" << nomRecherche;
}

// ----------------- TRI PAR ID CROISSANT -----------------
void Sponsor::trierParId(QTableWidget* tableWidget)
{
    if (!tableWidget) return;

    qDebug() << "🔄 Tri par ordre croissant des IDs...";

    // Créer une liste pour stocker les données triées
    QList<QStringList> donnees;

    // Récupérer toutes les données du tableau
    int rowCount = tableWidget->rowCount();
    int colCount = tableWidget->columnCount();

    for (int row = 0; row < rowCount; ++row) {
        QStringList ligne;
        for (int col = 0; col < colCount; ++col) {
            QTableWidgetItem* item = tableWidget->item(row, col);
            ligne << (item ? item->text() : "");
        }
        donnees.append(ligne);
    }

    // Trier par ID (colonne 0) - ordre croissant
    std::sort(donnees.begin(), donnees.end(), [](const QStringList &a, const QStringList &b) {
        if (a.size() > 0 && b.size() > 0) {
            // Convertir les IDs en nombres pour un tri numérique
            bool ok1, ok2;
            int idA = a[0].toInt(&ok1);
            int idB = b[0].toInt(&ok2);

            // Si les deux sont des nombres, tri numérique
            if (ok1 && ok2) {
                return idA < idB;
            }
            // Sinon, tri alphabétique
            return a[0] < b[0];
        }
        return false;
    });

    // Vider et remplir le tableau avec les données triées
    tableWidget->setRowCount(0);

    for (int row = 0; row < donnees.size(); ++row) {
        tableWidget->insertRow(row);
        for (int col = 0; col < donnees[row].size(); ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(donnees[row][col]);
            item->setTextAlignment(Qt::AlignCenter);
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            tableWidget->setItem(row, col, item);
        }
    }

    qDebug() << "✅ Tableau trié par ordre croissant des IDs";
}
// ▲▲▲▲▲▲▲▲▲▲ NOUVELLES FONCTIONS À AJOUTER ▲▲▲▲▲▲▲▲▲▲
