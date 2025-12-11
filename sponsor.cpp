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

    query.prepare(
        "INSERT INTO abir.SPONSOR "
        "(ID_SPONSOR, NOM, CONTRIBUTION, DATE_DEBUT, EMAIL, DATE_FIN) "
        "VALUES (:id, :nom, :contribution, TO_DATE(:dateDebut,'YYYY-MM-DD'), :email, TO_DATE(:dateFin,'YYYY-MM-DD'))"
        );

    query.bindValue(":id", id.toInt());
    query.bindValue(":nom", nom);
    query.bindValue(":contribution", contribution);
    query.bindValue(":dateDebut", dateDebut.toString("yyyy-MM-dd"));
    query.bindValue(":dateFin", dateFin.toString("yyyy-MM-dd"));
    query.bindValue(":email", email);

    if (!query.exec()) {
        qWarning() << "[Sponsor::ajouter] Erreur:" << query.lastError().text();
        return false;
    }

    return true;
}


// ----------------- MODIFIER - COMME PROJET -----------------
bool Sponsor::modifier()
{
    QSqlQuery query;

    query.prepare(
        "UPDATE abir.SPONSOR SET "
        "NOM = :nom, "
        "CONTRIBUTION = :contribution, "
        "DATE_DEBUT = TO_DATE(:dateDebut,'YYYY-MM-DD'), "
        "EMAIL = :email, "
        "DATE_FIN = TO_DATE(:dateFin,'YYYY-MM-DD') "
        "WHERE ID_SPONSOR = :id"
        );

    query.bindValue(":nom", nom);
    query.bindValue(":contribution", contribution);
    query.bindValue(":dateDebut", dateDebut.toString("yyyy-MM-dd"));
    query.bindValue(":dateFin", dateFin.toString("yyyy-MM-dd"));
    query.bindValue(":email", email);
    query.bindValue(":id", id.toInt());

    if (!query.exec()) {
        qWarning() << "[Sponsor::modifier] Error:" << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}

// ----------------- SUPPRIMER - COMME PROJET -----------------
bool Sponsor::supprimer(QString id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM abir.SPONSOR WHERE ID_SPONSOR = :id");
    query.bindValue(":id", id.toInt());

    if (!query.exec()) {
        qWarning() << "[Sponsor::supprimer] Error:" << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() > 0;
}

// ----------------- AFFICHER TABLEAU - COMME PROJET -----------------
void Sponsor::afficherDansTableau(QTableWidget* tableWidget)
{
    QSqlQuery query("SELECT ID_SPONSOR, NOM, CONTRIBUTION, DATE_DEBUT, DATE_FIN, EMAIL FROM abir.SPONSOR ORDER BY ID_SPONSOR");

    tableWidget->clear();
    QStringList headers = {"ID", "Nom", "Contribution", "Date Début", "Date Fin", "Email"};

    tableWidget->setColumnCount(headers.size());
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->setRowCount(0);

    int row = 0;
    while (query.next()) {
        tableWidget->insertRow(row);

        tableWidget->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        tableWidget->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));

        // Date début
        QDate dDeb = query.value(3).toDate();
        tableWidget->setItem(row, 3, new QTableWidgetItem(dDeb.toString("dd/MM/yyyy")));

        // Date fin
        QDate dFin = query.value(4).toDate();
        tableWidget->setItem(row, 4, new QTableWidgetItem(dFin.toString("dd/MM/yyyy")));

        // Email
        tableWidget->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));

        row++;
    }

    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}



// ----------------- RECHERCHER PAR ID  -----------------


// ----------------- RECHERCHER PAR ID  -----------------
bool Sponsor::rechercherParId(QString id, QString& nom, QString& contribution,
                              QDate& dateDebut, QDate& dateFin, QString& email)
{
    QSqlQuery query;
    query.prepare("SELECT NOM, TYPE, DETAILS, DATE_DEBUT, DATE_FIN, CONTACT FROM abir.SPONSOR WHERE ID_SPONSOR = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        nom = query.value(0).toString();           // NOM
        contribution = query.value(1).toString();  // TYPE -> contribution  
        // Skip DETAILS (index 2)
        dateDebut = query.value(3).toDate();       // DATE_DEBUT
        dateFin = query.value(4).toDate();         // DATE_FIN
        email = query.value(5).toString();         // CONTACT -> email

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
    query.prepare("SELECT ID_SPONSOR, NOM, TYPE, DETAILS, DATE_DEBUT, DATE_FIN, CONTACT FROM abir.SPONSOR "
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

        // Map database columns to display columns  
        // DB: ID_SPONSOR, NOM, TYPE, DETAILS, DATE_DEBUT, DATE_FIN, CONTACT
        // Display: ID, Nom, Contribution, Date Début, Date Fin, Email
        
        // ID (col 0) -> DB col 0
        QTableWidgetItem* idItem = new QTableWidgetItem(query.value(0).toString());
        idItem->setTextAlignment(Qt::AlignCenter);
        idItem->setFlags(idItem->flags() & ~Qt::ItemIsEditable);
        tableWidget->setItem(row, 0, idItem);
        
        // Nom (col 1) -> DB col 1
        QTableWidgetItem* nomItem = new QTableWidgetItem(query.value(1).toString());
        nomItem->setTextAlignment(Qt::AlignCenter);
        nomItem->setFlags(nomItem->flags() & ~Qt::ItemIsEditable);
        tableWidget->setItem(row, 1, nomItem);
        
        // Contribution (col 2) -> DB col 2 (TYPE)
        QTableWidgetItem* contribItem = new QTableWidgetItem(query.value(2).toString());
        contribItem->setTextAlignment(Qt::AlignCenter);
        contribItem->setFlags(contribItem->flags() & ~Qt::ItemIsEditable);
        tableWidget->setItem(row, 2, contribItem);
        
        // Date Début (col 3) -> DB col 4 (DATE_DEBUT)
        QDate dateDebut = query.value(4).toDate();
        QString dateDebutText = dateDebut.isValid() ? dateDebut.toString("dd/MM/yyyy") : "";
        QTableWidgetItem* dateDebutItem = new QTableWidgetItem(dateDebutText);
        dateDebutItem->setTextAlignment(Qt::AlignCenter);
        dateDebutItem->setFlags(dateDebutItem->flags() & ~Qt::ItemIsEditable);
        tableWidget->setItem(row, 3, dateDebutItem);
        
        // Date Fin (col 4) -> DB col 5 (DATE_FIN)
        QDate dateFin = query.value(5).toDate();
        QString dateFinText = dateFin.isValid() ? dateFin.toString("dd/MM/yyyy") : "";
        QTableWidgetItem* dateFinItem = new QTableWidgetItem(dateFinText);
        dateFinItem->setTextAlignment(Qt::AlignCenter);
        dateFinItem->setFlags(dateFinItem->flags() & ~Qt::ItemIsEditable);
        tableWidget->setItem(row, 4, dateFinItem);
        
        // Email (col 5) -> DB col 6 (CONTACT)
        QTableWidgetItem* emailItem = new QTableWidgetItem(query.value(6).toString());
        emailItem->setTextAlignment(Qt::AlignCenter);
        emailItem->setFlags(emailItem->flags() & ~Qt::ItemIsEditable);
        tableWidget->setItem(row, 5, emailItem);

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
