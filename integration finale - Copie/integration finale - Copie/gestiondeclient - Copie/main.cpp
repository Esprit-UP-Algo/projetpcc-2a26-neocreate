#include <QApplication>
#include "login.h"
#include "connection.h"
#include <QMessageBox>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (!createConnection()) {
        QMessageBox::critical(nullptr, "Erreur de connexion",
                              "Impossible de se connecter à Oracle.\n"
                              "Vérifie ODBC (DSN), identifiants et services Oracle.");
        return 1;
    }
    Login login;
    login.show();
    return a.exec();
}
