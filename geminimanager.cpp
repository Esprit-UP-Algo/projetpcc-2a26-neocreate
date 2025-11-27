#include "geminimanager.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include <QDebug>

GeminiManager::GeminiManager(const QString& apiKey, QObject* parent)
    : QObject(parent), m_apiKey(apiKey)
{
    m_networkManager = new QNetworkAccessManager(this);
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &GeminiManager::traiterReponse);
}

void GeminiManager::poserQuestion(const QString& question)
{
    // 🔥 PROMPT EXPERT SPONSORING TUNISIEN POUR GEMINI

    QString promptDirect =
        "TU ES EXPERT SPONSORING TUNISIEN (15+ ans d'expérience).\n"
        "DOMAINE EXCLUSIF : SPONSORING & PARTENARIATS EN TUNISIE UNIQUEMENT.\n\n"

        "**RÈGLES STRICTES :**\n"
        "1. RÉPONDRE UNIQUEMENT aux questions de SPONSORING/PARTENARIATS\n"
        "2. SI la question est HORS DOMAINE → \"Je suis spécialisé uniquement dans le sponsoring en Tunisie\"\n"
        "3. DONNER des CHIFFRES en TND pour les budgets\n"
        "4. PROPOSER 2-3 QUESTIONS SUIVANTES pertinentes\n\n"

        "**DOMAINES AUTORISÉS :**\n"
        "✓ Analyse sponsors (Délice, Orange, OCP, etc.)\n"
        "✓ Budgets et contributions financières\n"
        "✓ Stratégies de contact et partenariats\n"
        "✓ Recommandations sponsors\n"
        "✓ Comparaisons entre sponsors\n\n"

        "**DOMAINES INTERDITS :**\n"
        "✗ Cuisine, recettes, nutrition\n"
        "✗ Technologie, produits, services\n"
        "✗ Actualités, politique, économie générale\n"
        "✗ Autres sujets hors sponsoring\n\n"

        "**FORMAT :**\n"
        "🎯 [Réponse sponsoring uniquement]\n\n"
        "💡 *QUESTIONS SUIVANTES:*\n"
        "• [Question 1 sponsoring]\n"
        "• [Question 2 sponsoring]\n"
        "• [Question 3 sponsoring]\n\n"

        "QUESTION : " + question;


    // URL GEMINI API
    QString url ="https://generativelanguage.googleapis.com/v1/models/gemini-2.0-flash:generateContent?key=" + m_apiKey;

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // CONSTRUCTION REQUÊTE GEMINI
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

    // Paramètres supplémentaires pour de meilleures réponses
    QJsonObject generationConfig;
    generationConfig["temperature"] = 0.7;
    generationConfig["maxOutputTokens"] = 2000;
    generationConfig["topP"] = 0.8;
    generationConfig["topK"] = 40;
    payload["generationConfig"] = generationConfig;

    QJsonDocument doc(payload);
    QByteArray data = doc.toJson();

    qDebug() << "🚀 Envoi à Gemini AI...";
    qDebug() << "🔑 Clé utilisée:" << m_apiKey.left(8) + "..." + m_apiKey.right(4);
    qDebug() << "📝 Question:" << question;

    QNetworkReply *reply = m_networkManager->post(request, data);

    // GESTION DES ERREURS
    connect(reply, &QNetworkReply::errorOccurred, this, [this, reply]() {
        QString errorMsg = "Erreur réseau Gemini: " + reply->errorString();
        qDebug() << "❌ Erreur:" << errorMsg;

        // Vérifications à faire
        qDebug() << "🔧 Vérifiez :";
        qDebug() << "   1. Clé API valide sur https://makersuite.google.com/app/apikey";
        qDebug() << "   2. API Generative Language activée";
        qDebug() << "   3. Connexion internet stable";
        qDebug() << "   4. Quotas API non dépassés";

        emit erreur(errorMsg);
        reply->deleteLater();
    });
}

void GeminiManager::traiterReponse(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(responseData);
    QJsonObject json = doc.object();

    qDebug() << "✅ Réponse Gemini reçue";

    QString reponseText = "Désolé, format de réponse inattendu de Gemini AI.";

    // EXTRACTION RÉPONSE GEMINI
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
                            qDebug() << "🤖 Réponse Gemini traitée avec succès";
                        }
                    }
                }
            }
        }
    } else if (json.contains("error")) {
        QJsonObject error = json["error"].toObject();
        reponseText = "❌ Erreur Gemini API: " + error["message"].toString();
        qDebug() << "❌ Erreur API Gemini:" << reponseText;
    }

    emit reponseRecue(reponseText);
    reply->deleteLater();
}
