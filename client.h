#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QVector>

struct Client {
    int     ID_CLIENT{};      // entier > 0
    QString NOM;
    QString PRENOM;
    QString ENTREPRISE;
    QString EMAIL;
    QString TYPE;
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

#endif // CLIENT_H
