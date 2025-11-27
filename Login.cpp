#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QPalette>
#include <QColor>
#include <QSqlError>
Login::Login(QWidget *parent)
    : QDialog(parent), ui(new Ui::Login)
{
    ui->setupUi(this);

    // Champs (dans login.ui) : QLineEdit id, QLineEdit mdp, QPushButton connect
    ui->mdp->setEchoMode(QLineEdit::Password);

    // === Texte noir + placeholder gris ===
    auto tune = [](QLineEdit* le){
        QPalette p = le->palette();
        p.setColor(QPalette::Text, Qt::black);   // texte saisi noir
        p.setColor(QPalette::Base, Qt::white);   // fond blanc
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        p.setColor(QPalette::PlaceholderText, QColor(130,130,130)); // placeholder gris
#endif
        le->setPalette(p);
    };
    tune(ui->id);
    tune(ui->mdp);
}

Login::~Login()
{
    delete ui;
}



void Login::on_connect_clicked()
{
    QString id = ui->id->text().trimmed();
    QString mdp = ui->mdp->text().trimmed();

    // Vérification des champs vides
    if (id.isEmpty() || mdp.isEmpty()) {
        QMessageBox::warning(this, "Champs vides",
                             "Veuillez saisir l'ID et le mot de passe !");
        return;
    }

    // Vérifier que l'ID contient exactement 8 chiffres
    // QRegularExpression reg("^\\d{8}$");
    //if (!reg.match(id).hasMatch()) {
    //   QMessageBox::warning(this, "Erreur ID",
    //"L'ID doit contenir exactement 8 chiffres !");
    //return;
    //}

    // Vérification dans la base de données
    QSqlQuery query;
    query.prepare("SELECT id_employe, nom, prenom, poste, competence, telephone, email, mot_de_passe "
                  " FROM ABIR.EMPLOYE WHERE id_employe = :id AND mot_de_passe = :mdp");
    query.bindValue(":id", id);
    query.bindValue(":mdp", mdp);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL",
                              "Erreur lors de la vérification : " + query.lastError().text());
        return;
    }

    if (query.next()) {
        // Connexion réussie
        QString nom = query.value("nom").toString();
        QString prenom = query.value("prenom").toString();
        QString poste = query.value("poste").toString();

        QMessageBox::information(this, "Connexion réussie",
                                 "Bienvenue " + prenom + " " + nom + "!\nPoste: " + poste);
        // Ouvrir la fenêtre principale
        MainWindow *mainWindow = new MainWindow();
        mainWindow->show();
        // Accepter la dialog pour indiquer le succès
        this->accept();

    } else {
        // Vérifier si l'ID existe mais le mot de passe est incorrect
        QSqlQuery checkId;
        checkId.prepare("SELECT COUNT(*) FROM ABIR.EMPLOYE WHERE id_employe = :id");
        checkId.bindValue(":id", id);

        if (checkId.exec() && checkId.next()) {
            if (checkId.value(0).toInt() > 0) {
                // ID existe mais mot de passe incorrect
                QMessageBox::warning(this, "Erreur de connexion",
                                     "Mot de passe incorrect !");
            } else {
                // ID n'existe pas
                QMessageBox::warning(this, "Erreur de connexion",
                                     "ID employé non trouvé !");
            }
        } else {
            QMessageBox::critical(this, "Erreur",
                                  "Erreur lors de la vérification de l'ID");
        }

        // Effacer les champs
        ui->mdp->clear();
        ui->mdp->setFocus();
    }
}

