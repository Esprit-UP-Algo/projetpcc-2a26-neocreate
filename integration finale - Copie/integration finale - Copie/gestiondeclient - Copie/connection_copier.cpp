#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

bool createConnection() {
    if (!QSqlDatabase::drivers().contains("QODBC")) {
        QMessageBox::critical(nullptr, "Oracle ODBC",
                              "Driver QODBC manquant (plugin qsqlodbc 64-bit).");
        return false;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    // ⚠️ Mets ici le nom EXACT de ton DSN si différent
    db.setDatabaseName("source_projet2A");
    db.setUserName("abir");
    db.setPassword("esprit18");

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Oracle ODBC",
                              "Connexion échouée : " + db.lastError().text());
        return false;
    }

    qDebug() << "Connexion Oracle réussie.";
    return true;
}
