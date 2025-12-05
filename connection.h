#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

class Connection
{
private:
    QSqlDatabase db;
    Connection();
    ~Connection();

public:
    static Connection* getInstance();

    bool openConnection();
    void closeConnection();

    QSqlDatabase getDatabase() const { return db; } // getter pour le singleton
};

#endif // CONNECTION_H
