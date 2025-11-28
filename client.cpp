#include "client.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QVariant>
#include <QMessageBox>
#include <QRegularExpression>

bool ClientDAO::isInt(const QString& s) {
    static const QRegularExpression re(R"(^\d+$)");
    return re.match(s).hasMatch();
}

bool ClientDAO::isEmailLike(const QString& s) {
    static const QRegularExpression re(
        R"(^[A-Za-z0-9._%+\-]+@[A-Za-z0-9.\-]+\.[A-Za-z]{2,}$)"
        );
    return re.match(s.trimmed()).hasMatch();
}

bool ClientDAO::validate(const Client& c, QString& error) {
    if (c.ID_CLIENT <= 0) {
        error = "ID_CLIENT doit être un entier positif.";
        return false;
    }
    if (c.NOM.trimmed().isEmpty() ||
        c.PRENOM.trimmed().isEmpty() ||
        c.ENTREPRISE.trimmed().isEmpty() ||
        c.TYPE.trimmed().isEmpty()) {
        error = "NOM, PRENOM, ENTREPRISE et TYPE sont obligatoires.";
        return false;
    }
    if (!isEmailLike(c.EMAIL)) {
        error = "EMAIL invalide (ex : user@example.com).";
        return false;
    }
    return true;
}

bool ClientDAO::create(const Client& c) {
    QString err;
    if (!validate(c, err)) { QMessageBox::warning(nullptr, "Validation", err); return false; }

    QSqlQuery q(QSqlDatabase::database());
    q.prepare(R"(
        INSERT INTO ABIR.CLIENT (ID_CLIENT, NOM, PRENOM, ENTREPRISE, EMAIL, TYPE)
        VALUES (:id, :nom, :pre, :ent, :mail, :type)
    )");
    q.bindValue(":id",   c.ID_CLIENT);
    q.bindValue(":nom",  c.NOM);
    q.bindValue(":pre",  c.PRENOM);
    q.bindValue(":ent",  c.ENTREPRISE);
    q.bindValue(":mail", c.EMAIL);
    q.bindValue(":type", c.TYPE);

    auto db = QSqlDatabase::database();
    db.transaction();
    const bool ok = q.exec();
    ok ? db.commit() : db.rollback();

    if (!ok) QMessageBox::critical(nullptr, "Erreur INSERT", q.lastError().text());
    return ok;
}

bool ClientDAO::update(const Client& c) {
    QString err;
    if (!validate(c, err)) { QMessageBox::warning(nullptr, "Validation", err); return false; }

    QSqlQuery q(QSqlDatabase::database());
    q.prepare(R"(
        UPDATE ABIR.CLIENT
           SET NOM = :nom,
               PRENOM = :pre,
               ENTREPRISE = :ent,
               EMAIL = :mail,
               TYPE = :type
         WHERE ID_CLIENT = :id
    )");
    q.bindValue(":nom",  c.NOM);
    q.bindValue(":pre",  c.PRENOM);
    q.bindValue(":ent",  c.ENTREPRISE);
    q.bindValue(":mail", c.EMAIL);
    q.bindValue(":type", c.TYPE);
    q.bindValue(":id",   c.ID_CLIENT);

    auto db = QSqlDatabase::database();
    db.transaction();
    const bool ok = q.exec();
    ok ? db.commit() : db.rollback();

    if (!ok) QMessageBox::critical(nullptr, "Erreur UPDATE", q.lastError().text());
    return ok;
}

bool ClientDAO::remove(int id_client) {
    if (id_client <= 0) {
        QMessageBox::warning(nullptr, "Validation", "ID_CLIENT doit être un entier positif.");
        return false;
    }
    QSqlQuery q(QSqlDatabase::database());
    q.prepare("DELETE FROM ABIR.CLIENT WHERE ID_CLIENT = :id");
    q.bindValue(":id", id_client);

    auto db = QSqlDatabase::database();
    db.transaction();
    const bool ok = q.exec();
    ok ? db.commit() : db.rollback();

    if (!ok) QMessageBox::critical(nullptr, "Erreur DELETE", q.lastError().text());
    return ok;
}

bool ClientDAO::exists(int id_client) {
    if (id_client <= 0) return false;
    QSqlQuery q(QSqlDatabase::database());
    q.prepare("SELECT 1 FROM ABIR.CLIENT WHERE ID_CLIENT = :id");
    q.bindValue(":id", id_client);
    return q.exec() && q.next();
}

QVector<Client> ClientDAO::fetchAll() {
    QVector<Client> out;
    QSqlQuery q(QSqlDatabase::database());
    if (!q.exec(R"(
        SELECT ID_CLIENT, NOM, PRENOM, ENTREPRISE, EMAIL, TYPE
          FROM ABIR.CLIENT ORDER BY ID_CLIENT
    )")) return out;

    while (q.next()) {
        Client c;
        c.ID_CLIENT  = q.value(0).toInt();
        c.NOM        = q.value(1).toString();
        c.PRENOM     = q.value(2).toString();
        c.ENTREPRISE = q.value(3).toString();
        c.EMAIL      = q.value(4).toString();
        c.TYPE       = q.value(5).toString();
        out.push_back(c);
    }
    return out;
}
