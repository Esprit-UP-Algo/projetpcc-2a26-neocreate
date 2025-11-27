#include <QApplication>
#include "login.h"
#include "connection.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Utiliser le singleton Connection pour ouvrir la connexion
    Connection* conn = Connection::getInstance();
    if (!conn->openConnection()) {
        QMessageBox::critical(nullptr, "Erreur de connexion",
                              "Impossible de se connecter à Oracle.\n"
                              "Vérifie ODBC (DSN), identifiants et services Oracle.");
        return 1;
    }
    
    Login login;
    login.show();
    return a.exec();
}
