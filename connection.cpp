#include "connection.h"

// Private constructor
Connection::Connection()
{
    // Use the ODBC driver (singleton)
    db = QSqlDatabase::addDatabase("QODBC");

    // Connection parameters
    db.setDatabaseName("Source_Projet2a2");
    db.setUserName("abir");
    db.setPassword("esprit18");

}

Connection::~Connection()
{
    if (db.isOpen())
        db.close();
}

// Return the singleton instance
Connection* Connection::getInstance()
{
    static Connection instance;
    return &instance;
}

bool Connection::openConnection()
{
    if (db.isOpen()) {
        qDebug() << "Database already open.";
        return true;
    }

    if (db.open()) {
        qDebug() << "Successfully connected to Oracle via ODBC.";
        return true;
    } else {
        qDebug() << "Connection error:" << db.lastError().text();
        QMessageBox::critical(nullptr, "Erreur", "Impossible de se connecter à la base !");
        return false;
    }
}

void Connection::closeConnection()
{
    if (db.isOpen()) {
        db.close();
        qDebug() << "Database connection closed.";
    }
}
