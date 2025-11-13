#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

bool Connection::createconnect() {
    if (!QSqlDatabase::drivers().contains("QODBC")) {
        QMessageBox::critical(nullptr, "Oracle ODBC",
                              "Driver QODBC manquant (plugin qsqlodbc 64-bit).");
        return false;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setUserName("abir");
    db.setPassword("esprit18");
    db.setDatabaseName("Source_Projet2a");

    if (!db.open()) {
        QMessageBox::critical(nullptr, "Oracle ODBC",
                              "Connexion échouée : " + db.lastError().text());
        return false;
    }

    qDebug() << "Connexion Oracle réussie.";
    return true;
}
