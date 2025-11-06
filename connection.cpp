#include "connection.h"
#include <QDebug>
#include <QMessageBox>

Connection* Connection::p_instance = nullptr;

Connection::Connection()
{
    db = QSqlDatabase::addDatabase("QODBC" , "qt_oracle_connection");
    // Retirez AUTOCOMMIT si vous gérez les transactions manuellement
    // db.setConnectOptions();
}

Connection* Connection::instance()
{
    if (p_instance == nullptr) {
        p_instance = new Connection();
    }
    return p_instance;
}

bool Connection::createconnect()
{
    // Si la base est déjà ouverte, on la retourne
    if (db.isOpen()) {
        return true;
    }

    db.setDatabaseName("source_projet2a");
    db.setUserName("abir");
    db.setPassword("esprit18");

    if (db.open()) {
        qDebug() << "✅ Connexion réussie à la base de données Oracle";
        return true;
    } else {
        QString error = db.lastError().text();
        qDebug() << "❌ Erreur de connexion:" << error;
        QMessageBox::critical(nullptr, "Erreur", "Impossible de se connecter à la base de données !");
        return false;
    }
}


Connection::~Connection()
{
    if (db.isOpen()) {
        db.close();
        qDebug() << "Connexion fermée";
    }
}
