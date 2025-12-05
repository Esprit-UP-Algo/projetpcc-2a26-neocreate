#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>

class QTextEdit;
class QLineEdit;
class QPushButton;
class QLabel;
class QTimer;
class QVBoxLayout;
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
    void afficherTypingIndicator();
    void cacherTypingIndicator();

private:
    QTextEdit *m_textEditChat;
    QLineEdit *m_lineEditMessage;
    QPushButton *m_btnEnvoyer;
    QLabel *m_typingIndicator;
    QTimer *m_typingTimer;
    GeminiManager *m_geminiManager;

    bool sponsorExisteDansBase(const QString& nomSponsor);
    QString getInfosSponsor(const QString& nomSponsor);
    void setupUI();
    void setupConnections();
    void setupQuickActions(QVBoxLayout *mainLayout);
};

#endif // CHATWINDOW_H
