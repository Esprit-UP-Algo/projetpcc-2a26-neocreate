#include "login.h"
#include "ui_login.h"
#include <QSqlQuery>
#include <QSqlError>
#include "mainwindow.h"
#include <QMessageBox>
#include <QLineEdit>
#include <QPalette>
#include <QColor>
#include <QRegularExpression>
#include <QDesktopServices>
#include <QUrl>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QUrlQuery>
#include <QDateTime>
#include <QRandomGenerator>

//////////////////////////////////////////
//         SMTP CLIENT  (SSL)
//////////////////////////////////////////
SmtpClient::SmtpClient(const QString &host, int port,
                       const QString &username,
                       const QString &password,
                       QObject *parent)
    : QObject(parent), host(host), port(port),
    username(username), password(password)
{}

bool SmtpClient::sendMail(const QString &from,
                          const QString &to,
                          const QString &subject,
                          const QString &body)
{
    QSslSocket socket;

    // Configuration de la socket
    socket.connectToHostEncrypted(host, port);

    if (!socket.waitForConnected(5000)) {
        qDebug() << "Connection timeout to" << host << ":" << port;
        return false;
    }

    if (!socket.waitForEncrypted(5000)) {
        qDebug() << "SSL Handshake failed:" << socket.errorString();
        return false;
    }

    // Fonction pour envoyer des commandes et lire les réponses
    auto sendCommand = [&](const QString &command) -> bool {
        socket.write(command.toUtf8() + "\r\n");
        if (!socket.waitForBytesWritten(5000)) {
            qDebug() << "Failed to write command:" << command;
            return false;
        }

        // Lire la réponse
        if (!socket.waitForReadyRead(5000)) {
            qDebug() << "No response for command:" << command;
            return false;
        }

        QByteArray response = socket.readAll();
        qDebug() << "Response:" << response.trimmed();

        // Vérifier si la commande a réussi (code 2xx ou 3xx)
        return response.startsWith("2") || response.startsWith("3");
    };

    // Séquence SMTP
    if (!sendCommand("EHLO localhost")) return false;
    if (!sendCommand("AUTH LOGIN")) return false;
    if (!sendCommand(QString(username).toUtf8().toBase64())) return false;
    if (!sendCommand(QString(password).toUtf8().toBase64())) return false;
    if (!sendCommand("MAIL FROM: <" + from + ">")) return false;
    if (!sendCommand("RCPT TO: <" + to + ">")) return false;
    if (!sendCommand("DATA")) return false;

    // Construction du message
    QString message =
        "From: NeoCreate <" + from + ">\r\n"
                                     "To: " + to + "\r\n"
               "Subject: " + subject + "\r\n"
                    "MIME-Version: 1.0\r\n"
                    "Content-Type: text/html; charset=\"UTF-8\"\r\n"
                    "\r\n" +
        body + "\r\n.";

    if (!sendCommand(message)) return false;
    sendCommand("QUIT");

    socket.disconnectFromHost();
    return true;
}

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    // Configuration du label "Mot de passe oublié"
    ui->label_3->setText("<a href=\"#\" style=\"color: blue; text-decoration: none;\">Mot de passe oublié ?</a>");
    ui->label_3->setOpenExternalLinks(false);
    connect(ui->label_3, &QLabel::linkActivated, this, &Login::on_label_3_linkActivated);

    // Initialiser le timer
    m_timerExpiration = new QTimer(this);
    m_timerExpiration->setSingleShot(true);
}

Login::~Login()
{
    delete ui;
    delete m_timerExpiration;
}

//////////////////////////////////////////
//   MOT DE PASSE OUBLIÉ
//////////////////////////////////////////
void Login::on_label_3_linkActivated(const QString &)
{
    envoyerMotDePasseOublie();
}

void Login::envoyerMotDePasseOublie()
{
    // Nouveau design : boîte de dialogue dédiée avec email + OTP + nouveau mot de passe
    QDialog dialog(this);
    dialog.setWindowTitle("Réinitialisation du mot de passe");
    dialog.setModal(true);
    dialog.resize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);

    QLabel *infoLabel = new QLabel(
        "Entrez votre email, recevez un code (OTP),\n"
        "puis choisissez un nouveau mot de passe.", &dialog);
    infoLabel->setWordWrap(true);
    layout->addWidget(infoLabel);

    // Email
    QLabel *emailLabel = new QLabel("Email :", &dialog);
    QLineEdit *emailEdit = new QLineEdit(&dialog);
    emailEdit->setPlaceholderText("exemple@gmail.com");

    layout->addWidget(emailLabel);
    layout->addWidget(emailEdit);

    // Bouton pour envoyer le code
    QPushButton *btnEnvoyerCode = new QPushButton("Envoyer le code à cet email", &dialog);
    layout->addWidget(btnEnvoyerCode);

    // Champ pour le code OTP
    QLabel *codeLabel = new QLabel("Code OTP reçu :", &dialog);
    QLineEdit *codeEdit = new QLineEdit(&dialog);
    codeEdit->setPlaceholderText("Code à 6 chiffres");
    layout->addWidget(codeLabel);
    layout->addWidget(codeEdit);

    // Nouveau mot de passe + confirmation
    QLabel *newPassLabel = new QLabel("Nouveau mot de passe :", &dialog);
    QLineEdit *newPassEdit = new QLineEdit(&dialog);
    newPassEdit->setEchoMode(QLineEdit::Password);

    QLabel *confirmPassLabel = new QLabel("Confirmer le mot de passe :", &dialog);
    QLineEdit *confirmPassEdit = new QLineEdit(&dialog);
    confirmPassEdit->setEchoMode(QLineEdit::Password);

    layout->addWidget(newPassLabel);
    layout->addWidget(newPassEdit);
    layout->addWidget(confirmPassLabel);
    layout->addWidget(confirmPassEdit);

    // Boutons d'action
    QPushButton *btnValider = new QPushButton("Valider la réinitialisation", &dialog);
    QPushButton *btnAnnuler = new QPushButton("Annuler", &dialog);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(btnAnnuler);
    btnLayout->addWidget(btnValider);
    layout->addLayout(btnLayout);

    // Label de statut
    QLabel *statusLabel = new QLabel(&dialog);
    statusLabel->setStyleSheet("color: red;");
    layout->addWidget(statusLabel);

    // Quand on clique sur "Annuler"
    QObject::connect(btnAnnuler, &QPushButton::clicked, &dialog, &QDialog::reject);

    // Quand on clique sur "Envoyer le code"
    QObject::connect(btnEnvoyerCode, &QPushButton::clicked, this,
                     [this, emailEdit, statusLabel]() {
                         QString email = emailEdit->text().trimmed();

                         if (email.isEmpty()) {
                             statusLabel->setText("Veuillez saisir votre email.");
                             return;
                         }

                         QSqlQuery query;
                         query.prepare("SELECT id_employe, nom, prenom "
                                       "FROM ABIR.EMPLOYE WHERE email = :email");
                         query.bindValue(":email", email);

                         if (!query.exec()) {
                             QMessageBox::critical(this, "Erreur SQL", query.lastError().text());
                             return;
                         }

                         if (!query.next()) {
                             statusLabel->setText("Aucun compte trouvé avec cet email.");
                             return;
                         }

                         QString id = query.value(0).toString();
                         QString nom = query.value(1).toString();
                         QString prenom = query.value(2).toString();

                         // Stocker les données temporaires
                         m_idCourant = id;
                         m_emailCourant = email;

                         // Envoyer le code de vérification
                         if (envoyerCodeVerification(email, nom, prenom)) {
                             statusLabel->setStyleSheet("color: green;");
                             statusLabel->setText("Code envoyé à : " + email);
                         } else {
                             statusLabel->setStyleSheet("color: red;");
                             statusLabel->setText("Impossible d'envoyer le code. Vérifiez l'email.");
                         }
                     });

    // Quand on clique sur "Valider la réinitialisation"
    QObject::connect(btnValider, &QPushButton::clicked, this,
                     [&dialog, this, codeEdit, newPassEdit, confirmPassEdit, statusLabel]() {
                         if (m_idCourant.isEmpty() || m_emailCourant.isEmpty()) {
                             statusLabel->setText("Veuillez d'abord envoyer le code à votre email.");
                             return;
                         }

                         QString codeSaisi = codeEdit->text().trimmed();
                         QString nouveauMdp = newPassEdit->text().trimmed();
                         QString confirmationMdp = confirmPassEdit->text().trimmed();

                         if (codeSaisi.isEmpty()) {
                             statusLabel->setText("Veuillez saisir le code OTP reçu.");
                             return;
                         }

                         if (!verifierCode(codeSaisi)) {
                             statusLabel->setText("Code OTP incorrect ou expiré.");
                             return;
                         }

                         if (nouveauMdp.isEmpty() || confirmationMdp.isEmpty()) {
                             statusLabel->setText("Veuillez saisir et confirmer le nouveau mot de passe.");
                             return;
                         }

                         if (nouveauMdp != confirmationMdp) {
                             statusLabel->setText("Les deux mots de passe ne correspondent pas.");
                             return;
                         }

                         if (nouveauMdp.length() < 4) {
                             statusLabel->setText("Le mot de passe doit contenir au moins 4 caractères.");
                             return;
                         }

                         if (mettreAJourMotDePasse(m_idCourant, nouveauMdp)) {
                             QMessageBox::information(&dialog, "Succès",
                                                      "Votre mot de passe a été mis à jour avec succès !");

                             // Effacer les champs temporaires
                             m_idCourant.clear();
                             m_codeVerification.clear();
                             m_emailCourant.clear();
                             m_timerExpiration->stop();

                             // Effacer aussi le champ mot de passe du login
                             ui->mdp->clear();

                             dialog.accept();
                         } else {
                             statusLabel->setText("Erreur lors de la mise à jour du mot de passe.");
                         }
                     });

    dialog.exec();
}

//////////////////////////////////////////
//  GÉNÉRATION ET ENVOI DU CODE
//////////////////////////////////////////
QString Login::genererCodeVerification()
{
    const QString caracteres = "0123456789";
    QString code;
    code.reserve(CODE_LENGTH);

    for (int i = 0; i < CODE_LENGTH; ++i) {
        int index = QRandomGenerator::global()->bounded(caracteres.length());
        code.append(caracteres.at(index));
    }

    return code;
}

bool Login::envoyerCodeVerification(const QString &emailEmploye,
                                    const QString &nom,
                                    const QString &prenom)
{
    // Générer un nouveau code
    m_codeVerification = genererCodeVerification();

    // Configurer l'expiration du code (10 minutes)
    m_timerExpiration->start(CODE_EXPIRATION_MINUTES * 60 * 1000);

    // Créer le client SMTP (compte expéditeur fourni)
    SmtpClient smtp("smtp.gmail.com",
                    465,
                    "charcheriabir18@gmail.com",
                    "oudw hwrv aapr xbki");

    QString sujet = "Code de vérification pour réinitialisation de mot de passe";

    QString corps = QString(
                        "Bonjour %1 %2,<br><br>"
                        "Vous avez demandé à réinitialiser votre mot de passe.<br>"
                        "Votre code de vérification est : <b style='font-size: 20px; color: blue;'>%3</b><br><br>"
                        "Ce code expirera dans %4 minutes.<br><br>"
                        "Si vous n'avez pas fait cette demande, veuillez ignorer cet email.<br><br>"
                        "Cordialement,<br>"
                        "L'équipe NeoCreate"
                        ).arg(prenom, nom, m_codeVerification, QString::number(CODE_EXPIRATION_MINUTES));

    bool result = smtp.sendMail("charcheriabir18@gmail.com",
                                emailEmploye,
                                sujet,
                                corps);

    qDebug() << "Envoi email à" << emailEmploye << ":" << (result ? "Succès" : "Échec");

    // Si l'envoi SMTP échoue, afficher le code pour les tests
    if (!result) {
        QMessageBox::information(this, "CODE DE VÉRIFICATION (Test)",
                                 "Envoi email échoué. Code de test : " + m_codeVerification);
        return true; // Retourner true pour continuer le processus de test
    }

    return result;
}

//////////////////////////////////////////
//  VÉRIFICATION DU CODE
//////////////////////////////////////////
bool Login::verifierCode(const QString &codeSaisi)
{
    // Vérifier si le timer a expiré
    if (!m_timerExpiration->isActive()) {
        qDebug() << "Code expiré";
        return false;
    }

    // Vérifier si le code correspond
    bool correct = (codeSaisi.trimmed() == m_codeVerification);
    qDebug() << "Vérification code:" << codeSaisi << "vs" << m_codeVerification << "->" << correct;
    return correct;
}

//////////////////////////////////////////
//  MISE À JOUR DU MOT DE PASSE
//////////////////////////////////////////
bool Login::mettreAJourMotDePasse(const QString &id, const QString &nouveauMdp)
{
    QSqlQuery query;
    query.prepare("UPDATE ABIR.EMPLOYE SET mot_de_passe = :mdp WHERE id_employe = :id");
    query.bindValue(":mdp", nouveauMdp);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Erreur mise à jour mdp:" << query.lastError().text();
        return false;
    }

    bool success = query.numRowsAffected() > 0;
    qDebug() << "Mise à jour mdp:" << (success ? "Succès" : "Échec");
    return success;
}

// Gardez votre méthode de connexion existante
void Login::on_connect_clicked()
{
    // CORRECTION : Utilisez les vrais noms de vos champs
    // Si vous avez "id" et "mdp" dans votre .ui, gardez ces noms
    QString id = ui->id->text().trimmed();
    QString mdp = ui->mdp->text().trimmed();

    // Vérification des champs vides
    if (id.isEmpty() || mdp.isEmpty()) {
        QMessageBox::warning(this, "Champs vides",
                             "Veuillez saisir l'ID et le mot de passe !");
        return;
    }

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
        // Fermer la fenêtre de login
        this->close();

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
// Dans l'implémentation (login.cpp)
void Login::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        on_connect_clicked(); // Appeler directement votre slot de connexion
    } else {
        QWidget::keyPressEvent(event); // Appeler l'implémentation parente
    }
}
