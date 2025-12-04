#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QSslSocket>
#include <QTimer>

namespace Ui {
class Login;
}

class SmtpClient : public QObject
{
    Q_OBJECT

public:
    SmtpClient(const QString &host,
               int port,
               const QString &username,
               const QString &password,
               QObject *parent = nullptr);

    bool sendMail(const QString &from,
                  const QString &to,
                  const QString &subject,
                  const QString &body);

private:
    QString host;
    int port;
    QString username;
    QString password;
};

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_label_3_linkActivated(const QString &link);
    void on_connect_clicked();

private:
    Ui::Login *ui;
    void envoyerMotDePasseOublie();
    bool envoyerCodeVerification(const QString &emailEmploye, const QString &nom, const QString &prenom);
    bool verifierCode(const QString &codeSaisi);
    bool mettreAJourMotDePasse(const QString &id, const QString &nouveauMdp);
    QString genererCodeVerification();

    // Variables pour stocker les données temporaires
    QString m_idCourant;
    QString m_codeVerification;
    QString m_emailCourant;
    QTimer *m_timerExpiration;

    // Constantes
    static const int CODE_LENGTH = 6;
    static const int CODE_EXPIRATION_MINUTES = 10;

// Dans le header de votre classe Login (login.h)
protected:
void keyPressEvent(QKeyEvent *event) override;
};
#endif // LOGIN_H
