#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>

// Simple DB connection helper (Singleton)
class Connection
{
private:
    QSqlDatabase db;  // QSqlDatabase instance

    // Private constructor for Singleton
    Connection();

public:
    ~Connection();

    // No copying
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    // Get the singleton instance
    static Connection* getInstance();

    // Open / close
    bool openConnection();
    void closeConnection();

    // Utility
    bool isOpen() const { return db.isOpen(); }
};

#endif // CONNECTION_H
