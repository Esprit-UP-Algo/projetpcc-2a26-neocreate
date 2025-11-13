#include <QApplication>
#include "login.h"
#include "mainwindow.h"
#include "connection.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlDatabase>  // AJOUTEZ CET INCLUDE MANQUANT

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Debug : afficher les pilotes disponibles
    qDebug() << "Pilotes disponibles:" << QSqlDatabase::drivers();

    // Utiliser Connection::createconnect()
    if (!Connection::createconnect()) {
        QMessageBox::critical(nullptr, "Erreur de connexion",
                              "Impossible de se connecter à la base de données.\n"
                              "Vérifiez:\n"
                              "- La source de données ODBC\n"
                              "- L'utilisateur: abir\n"
                              "- Le mot de passe\n"
                              "- Que le service Oracle est démarré");
        return 1;
    }

    qDebug() << "Connexion à la base de données réussie";

    // Afficher la fenêtre de login
    Login login;

    // Utiliser exec() pour attendre la réponse modale
    if (login.exec() == QDialog::Accepted) {
        // Si le login est réussi, ouvrir MainWindow
        MainWindow w;
        w.show();
        return a.exec();
    } else {
        // Si le login est annulé ou échoué, quitter l'application
        return 0;
    }
}
