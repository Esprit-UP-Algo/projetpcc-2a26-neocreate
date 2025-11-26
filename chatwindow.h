#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>
#include <QSqlQuery>  // AJOUTE CETTE LIGNE
#include <QSqlError>  // AJOUTE AUSSI CELLE-CI
#include <QSqlDatabase>
class QTextEdit;
class QLineEdit;
class QPushButton;
class GeminiManager;

class ChatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();
    void poserQuestion(const QString& question);
private slots:
    void envoyerMessage();
    void afficherReponseIA(const QString& reponse);
    void afficherErreur(const QString& message);
    void afficherMessageBienvenue();
private:
    QTextEdit *m_textEditChat;
    QLineEdit *m_lineEditMessage;
    QPushButton *m_btnEnvoyer;
    GeminiManager *m_geminiManager;
    bool sponsorExisteDansBase(const QString& nomSponsor);
    QString getInfosSponsor(const QString& nomSponsor);
};

#endif // CHATWINDOW_H
