#include "projet.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlDriver>

Projet::Projet()
{
    id = 0;
    type = "";
    date_debut = QDate::currentDate();
    date_fin = QDate::currentDate();
    montant = 0.0;
    paiment = "";
    id_client = 0;
    note_materiel="";
}

Projet::Projet(int id, const QString &type, const QDate &date_debut,
               const QDate &date_fin, float montant, const QString &paiment, const QString &note_materiel)
{
    this->id = id;
    this->type = type;
    this->date_debut = date_debut;
    this->date_fin = date_fin;
    this->montant = montant;
    this->paiment = paiment;
    this->note_materiel=note_materiel;
}

bool Projet::AjouterProjet()
{
    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database();

    QString sql;
    if (id_client > 0) {
        sql = "INSERT INTO ABIR.PROJET (ID_PROJET, TYPE, DATE_D, DATE_F, MONTANT, PAIMENT, MATRIEL, ID_CLIENT) "
              "VALUES (:id, :type, :date_d, :date_f, :montant, :paiment, :note_materiel, :id_client)";
    } else {
        sql = "INSERT INTO ABIR.PROJET (ID_PROJET, TYPE, DATE_D, DATE_F, MONTANT, PAIMENT, MATRIEL) "
              "VALUES (:id, :type, :date_d, :date_f, :montant, :paiment, :note_materiel)";
    }

    query.prepare(sql);
    query.bindValue(":id", id);
    query.bindValue(":type", type);
    query.bindValue(":date_d", date_debut);
    query.bindValue(":date_f", date_fin);
    query.bindValue(":montant", montant);
    query.bindValue(":paiment", paiment);
    query.bindValue(":note_materiel", note_materiel);

    if (id_client > 0) {
        query.bindValue(":id_client", id_client);
    }

    bool success = query.exec();

    if (!success) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        qDebug() << "Requête:" << query.lastQuery();
    }

    return success;
}
QSqlQueryModel* Projet::AfficherProjets()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(
        "SELECT ID_PROJET, TYPE, TO_CHAR(DATE_D, 'YYYY-MM-DD') AS DATE_D, "
        "TO_CHAR(DATE_F, 'YYYY-MM-DD') AS DATE_F, MONTANT, PAIMENT, MATRIEL, ID_CLIENT FROM ABIR.PROJET"
        );

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_PROJET"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date début"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date fin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Paiement"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Matriel"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID_CLIENT"));

    return model;
}

QSqlQueryModel* Projet::AfficherProjetsTriés(const QString &sortBy)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString query = "SELECT ID_PROJET, TYPE, TO_CHAR(DATE_D, 'YYYY-MM-DD') AS DATE_D, "
                    "TO_CHAR(DATE_F, 'YYYY-MM-DD') AS DATE_F, MONTANT, PAIMENT, MATRIEL, ID_CLIENT FROM ABIR.PROJET ";

    if (sortBy == "Date début (asc)" || sortBy == "Date début") {
        query += "ORDER BY DATE_D ASC";
    } else if (sortBy == "Date début (desc)") {
        query += "ORDER BY DATE_D DESC";
    } else if (sortBy == "Date fin (asc)" || sortBy == "Date fin") {
        query += "ORDER BY DATE_F ASC";
    } else if (sortBy == "Date fin (desc)") {
        query += "ORDER BY DATE_F DESC";
    } else if (sortBy == "Montant (asc)") {
        query += "ORDER BY MONTANT ASC";
    } else if (sortBy == "Montant (desc)" || sortBy == "Montant" || sortBy == "montant") {
        query += "ORDER BY MONTANT DESC";
    } else {
        query += "ORDER BY ID_PROJET";
    }

    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_PROJET"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date début"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date fin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Paiement"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Matriel"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID_CLIENT"));

    return model;
}

QSqlQueryModel* Projet::ChercherProjetParId(int id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString query = "SELECT ID_PROJET, TYPE, TO_CHAR(DATE_D, 'YYYY-MM-DD') AS DATE_D, "
                    "TO_CHAR(DATE_F, 'YYYY-MM-DD') AS DATE_F, MONTANT, PAIMENT, MATRIEL, ID_CLIENT FROM ABIR.PROJET "
                    "WHERE ID_PROJET = " + QString::number(id);

    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_PROJET"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date début"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date fin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Paiement"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Matriel"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID_CLIENT"));

    return model;
}

QSqlQueryModel* Projet::ChercherProjetParIdStatique(int id)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString query = "SELECT ID_PROJET, TYPE, TO_CHAR(DATE_D, 'YYYY-MM-DD') AS DATE_D, "
                    "TO_CHAR(DATE_F, 'YYYY-MM-DD') AS DATE_F, MONTANT, PAIMENT, MATRIEL, ID_CLIENT FROM ABIR.PROJET "
                    "WHERE ID_PROJET = " + QString::number(id);

    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_PROJET"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date début"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date fin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Paiement"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Matriel"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("ID_CLIENT"));

    return model;
}
// Méthode statique pour chercher des projets par TYPE (ex: "podcast", "live")
QSqlQueryModel* Projet::ChercherProjetParTypeStatique(const QString &type)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    // sanitize single quotes
    QString t = type.trimmed();
    t.replace("'", "''");
    // Case-insensitive match
    QString query = "SELECT ID_PROJET, TYPE, TO_CHAR(DATE_D, 'YYYY-MM-DD') AS DATE_D, "
                    "TO_CHAR(DATE_F, 'YYYY-MM-DD') AS DATE_F, MONTANT, PAIMENT, ID_CLIENT FROM ABIR.PROJET "
                    "WHERE UPPER(TYPE) = UPPER('" + t + "')";

    model->setQuery(query);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_PROJET"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date début"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date fin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Paiement"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Matriel"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ID_CLIENT"));

    if (model->lastError().isValid()) {
        qWarning() << "[ChercherProjetParTypeStatique] Query error:" << model->lastError().text();
    } else {
        qDebug() << "[ChercherProjetParTypeStatique] Query set successfully for TYPE:" << type;
    }

    return model;
}

bool Projet::ModifierProjet()
{
    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database();

    QString sql;
    if (id_client > 0) {
        sql = "UPDATE ABIR.PROJET SET TYPE = :type, DATE_D = :date_d, DATE_F = :date_f, MONTANT = :montant, PAIMENT = :paiment, MATRIEL = :note_materiel, ID_CLIENT = :id_client WHERE ID_PROJET = :id";
    } else {
        sql = "UPDATE ABIR.PROJET SET TYPE = :type, DATE_D = :date_d, DATE_F = :date_f, MONTANT = :montant, PAIMENT = :paiment, MATRIEL = :note_materiel, ID_CLIENT = NULL WHERE ID_PROJET = :id";
    }
    query.prepare(sql);

    query.bindValue(":type", type);
    query.bindValue(":date_d", date_debut);
    query.bindValue(":date_f", date_fin);
    query.bindValue(":montant", montant);
    query.bindValue(":paiment", paiment);
    query.bindValue(":note_materiel", note_materiel);
    if (id_client > 0) {
        query.bindValue(":id_client", id_client);
    }
    query.bindValue(":id", id);

    bool success = query.exec();

    if (!success) {
        qDebug() << "Erreur SQL modification:" << query.lastError().text();
    }

    return success;
}

bool Projet::SupprimerProjet(int id)
{
    QSqlQuery query;

    query.prepare("DELETE FROM ABIR.PROJET WHERE ID_PROJET = :id");
    query.bindValue(":id", id);

    bool success = query.exec();

    if (!success) {
        qDebug() << "Erreur SQL suppression:" << query.lastError().text();
    }

    return success;
}

QString Projet::getNoteMateriel() const
{
    return note_materiel;
}

void Projet::setNoteMateriel(const QString &newNote_materiel)
{
    note_materiel = newNote_materiel;
}


// -------------------- Statistics --------------------
double Projet::TotalMontant()
{
    QSqlQuery q;
    // Use COALESCE to normalize NULL to 0 (works in Oracle/other DBs)
    if (q.exec("SELECT COALESCE(SUM(MONTANT),0) FROM ABIR.PROJET") && q.next()) {
        return q.value(0).toDouble();
    }
    return 0.0;
}

double Projet::AverageMontant()
{
    QSqlQuery q;
    if (q.exec("SELECT COALESCE(AVG(MONTANT),0) FROM ABIR.PROJET") && q.next()) {
        return q.value(0).toDouble();
    }
    return 0.0;
}

QVector<QPair<QString,int>> Projet::CountsByType()
{
    QVector<QPair<QString,int>> out;
    QSqlQuery q;
    if (!q.exec("SELECT TYPE, COUNT(*) FROM ABIR.PROJET GROUP BY TYPE")) {
        qDebug() << "[CountsByType] Query failed:" << q.lastError().text();
        return out;
    }
    while (q.next()) {
        QString t = q.value(0).toString();
        int cnt = q.value(1).toInt();
        out.append(qMakePair(t, cnt));
    }
    return out;
}

QVector<QPair<QString,double>> Projet::MontantByPaiment()
{
    QVector<QPair<QString,double>> out;
    QSqlQuery q;
    // Group sums by PAIMENT (payment method)
    // Use TRIM(PAIMENT) so values like 'virement ' are treated the same as 'virement'
    if (!q.exec("SELECT TRIM(PAIMENT), COALESCE(SUM(MONTANT),0) FROM ABIR.PROJET GROUP BY TRIM(PAIMENT)")) {
        qDebug() << "[MontantByPaiment] Query failed:" << q.lastError().text();
        return out;
    }
    while (q.next()) {
        QString paiment = q.value(0).toString();
        double sum = q.value(1).toDouble();
        out.append(qMakePair(paiment, sum));
    }
    return out;
}

QVector<QPair<QString,int>> Projet::CountsByPaiment()
{
    QVector<QPair<QString,int>> out;
    QSqlQuery q;
    // Group counts by trimmed PAIMENT to normalize values with trailing spaces
    if (!q.exec("SELECT TRIM(PAIMENT), COUNT(*) FROM ABIR.PROJET GROUP BY TRIM(PAIMENT)")) {
        qDebug() << "[CountsByPaiment] Query failed:" << q.lastError().text();
        return out;
    }
    while (q.next()) {
        QString paiment = q.value(0).toString();
        int cnt = q.value(1).toInt();
        out.append(qMakePair(paiment, cnt));
    }
    return out;
}
