#ifndef GEMINIMANAGER_H
#define GEMINIMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class GeminiManager : public QObject
{
    Q_OBJECT

public:
    explicit GeminiManager(const QString& apiKey, QObject* parent = nullptr);
    void poserQuestion(const QString& question);

signals:
    void reponseRecue(const QString& reponse);
    void erreur(const QString& message);

private slots:
    void traiterReponse(QNetworkReply* reply);

private:
    QString m_apiKey;
    QNetworkAccessManager* m_networkManager;
};

#endif // GEMINIMANAGER_H
