#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QVector>
#include <QDate>
struct Client {
    int     ID_CLIENT{};      // entier > 0
    QString NOM;
    QString PRENOM;
    QString ENTREPRISE;
    QString EMAIL;
    QString TYPE;
    QDate   DATE_AJOUT;
};

class ClientDAO {
public:
    // CRUD
    static bool create(const Client& c);
    static bool update(const Client& c);
    static bool remove(int id_client);
    static bool exists(int id_client);

    // Read
    static QVector<Client> fetchAll();

    // Validation (utilisée côté UI et DAO)
    static bool validate(const Client& c, QString& errorMsg);

private:
    static bool isInt(const QString& s);             // ^\d+$
    static bool isEmailLike(const QString& s);       // regex simple
};

#include <QListWidget>

class ClientHistory {
public:
    static void setListWidget(QListWidget *list);
    static void addEntry(const QString &action, int id, const QString &nom);
    static void loadHistory();
    static void clearHistory();

private:
    static QString logPath();
    static void saveToFile(const QString &msg);

    static QListWidget *m_listWidget;
};
// =============================
//  TWILIO : ENVOI SMS
// =============================
bool sendSmsTwilio(const QString &toE164, const QString &body);

#endif // CLIENT_H
