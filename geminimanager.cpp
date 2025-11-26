#include "geminimanager.h"
#include <QTimer>

GeminiManager::GeminiManager(const QString& apiKey, QObject* parent)
    : QObject(parent), m_apiKey(apiKey)
{
    m_networkManager = new QNetworkAccessManager(this);
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &GeminiManager::traiterReponse);
}

void GeminiManager::poserQuestion(const QString& question)
{
    QString promptDirect = "TU ES EXPERT SPONSORING TUNISIEN. RÈGLES :\n\n"

                           "1. RÉPOND UNIQUEMENT À LA QUESTION\n"
                           "2. À LA FIN, PROPOSER 2-3 QUESTIONS SUIVANTES PERTINENTES\n"
                           "3. FORMAT : \n"
                           "[Réponse principale]\n\n"
                           "💡 **QUESTIONS SUIVANTES:**\n"
                           "• [Question 1]\n"
                           "• [Question 2]\n"
                           "• [Question 3]\n\n"

                           "EXEMPLES :\n"
                           "Si on analyse Délice → Proposer : Contacts? Recommandation? Comparaison?\n"
                           "Si on compare → Proposer : Budget? Délai? Stratégie approche?\n\n"

                           "Question: " + question;

    QString url = "https://generativelanguage.googleapis.com/v1/models/gemini-2.0-flash:generateContent?key=" + m_apiKey;

    // ... reste du code inchangé ...
    // ... reste du code inchangé ...
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject payload;
    QJsonArray contents;
    QJsonObject content;
    QJsonArray parts;
    QJsonObject textPart;

    textPart["text"] = promptDirect;
    parts.append(textPart);
    content["parts"] = parts;
    contents.append(content);
    payload["contents"] = contents;

    QJsonDocument doc(payload);
    QByteArray data = doc.toJson();

    m_networkManager->post(request, data);
}

void GeminiManager::traiterReponse(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(responseData);
        QJsonObject json = doc.object();

        // Extraction de la réponse texte
        QString reponseText = "Erreur: Format de réponse inattendu";

        if (json.contains("candidates")) {
            QJsonArray candidates = json["candidates"].toArray();
            if (!candidates.isEmpty()) {
                QJsonObject candidate = candidates[0].toObject();
                if (candidate.contains("content")) {
                    QJsonObject content = candidate["content"].toObject();
                    if (content.contains("parts")) {
                        QJsonArray parts = content["parts"].toArray();
                        if (!parts.isEmpty()) {
                            QJsonObject part = parts[0].toObject();
                            if (part.contains("text")) {
                                reponseText = part["text"].toString();
                            }
                        }
                    }
                }
            }
        }

        emit reponseRecue(reponseText);
    } else {
        emit erreur("Erreur réseau: " + reply->errorString());
    }

    reply->deleteLater();
}
