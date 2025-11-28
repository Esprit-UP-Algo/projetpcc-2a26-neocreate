#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QPalette>
#include <QColor>

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
    const QString user = ui->id->text().trimmed();
    const QString pass = ui->mdp->text();

    if (user == "admin" && pass == "admin") {
        auto *w = new MainWindow();   // fenêtre principale
        w->show();
        this->close();                // fermer la fenêtre de login
    } else {
        QMessageBox::warning(this, "Erreur", "ID ou mot de passe incorrect !");
        ui->mdp->clear();
        ui->mdp->setFocus();
    }
}
