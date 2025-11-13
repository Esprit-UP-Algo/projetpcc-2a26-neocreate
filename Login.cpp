#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <QPalette>
#include <QBrush>

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    this->showFullScreen();


    setWindowTitle("Connexion");
    ui->mdpp->setEchoMode(QLineEdit::Password);

    // ✅ Image de fond ajustée à la taille de la fenêtre (sans déformation)
    QPixmap bkgnd(":/new/prefix1/back.png");
    if (!bkgnd.isNull()) {
        bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    } else {
        qDebug() << "❌ Impossible de charger l'image de fond :/new/prefix1/back.png";
    }
}

// ✅ Pour redimensionner le fond automatiquement si la fenêtre change de taille
void Login::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    QPixmap bkgnd(":/new/prefix1/back.png");
    if (!bkgnd.isNull()) {
        // 🟩 Garde le ratio, remplit tout, sans déformation ni coupure visible
        bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        QPalette palette;
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    }
}

Login::~Login()
{
    delete ui;
}

void Login::on_connect_clicked()
{
    QString id = ui->id->text().trimmed();
    QString mdp = ui->mdpp->text().trimmed();

    if (id.isEmpty() || mdp.isEmpty()) {
        QMessageBox::warning(this, "Champs vides", "Veuillez saisir l'ID et le mot de passe !");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT ID_STAFF, NOM_STAFF, PRENOM_STAFF, POSTE_STAFF "
                  "FROM EMPLOYE WHERE ID_STAFF = :id AND PASS_STAFF = :mdp");
    query.bindValue(":id", id);
    query.bindValue(":mdp", mdp);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur SQL",
                              "Erreur lors de la vérification : " + query.lastError().text());
        return;
    }

    if (query.next()) {
        QString nom = query.value("NOM_STAFF").toString();
        QString prenom = query.value("PRENOM_STAFF").toString();
        QString poste = query.value("POSTE_STAFF").toString();

        QMessageBox::information(this, "Connexion réussie",
                                 "Bienvenue " + prenom + " " + nom + " !\nPoste : " + poste);

        this->accept();
    } else {
        QMessageBox::warning(this, "Erreur de connexion", "ID ou mot de passe incorrect !");
        ui->mdpp->clear();
        ui->mdpp->setFocus();
    }
}
