#include "chatwindow.h"
#include "geminimanager.h"

#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QDateTime>
#include <QLabel>
#include <QTimer>
#include <QSqlQuery>  // AJOUTE CETTE LIGNE
#include <QSqlError>  // AJOUTE AUSSI CELLE-CI


ChatWindow::ChatWindow(QWidget *parent) : QDialog(parent)
{
    // Créer tous les widgets
    m_textEditChat = new QTextEdit(this);
    m_lineEditMessage = new QLineEdit(this);
    m_btnEnvoyer = new QPushButton("Send", this);

    // === INITIALISER GEMINI MANAGER ===
    QString apiKey = "AIzaSyDDLZWCihoOj-iLEWmyf0tuOhjXHRdX414";  // REMPLACE PAR TA VRAIE CLÉ
    m_geminiManager = new GeminiManager(apiKey, this);

    // Connecter les signaux de GeminiManager
    connect(m_geminiManager, &GeminiManager::reponseRecue, this, &ChatWindow::afficherReponseIA);
    connect(m_geminiManager, &GeminiManager::erreur, this, &ChatWindow::afficherErreur);

    // === STYLE THÈME SOMBRE INSPIRÉ DE L'IMAGE ===
    this->setStyleSheet("background-color: #0d1b2a; color: #e0e1dd;");

    // Style pour la zone de chat
    m_textEditChat->setStyleSheet(
        "QTextEdit {"
        "    background-color: #1b263b;"
        "    color: #e0e1dd;"
        "    border: 1px solid #415a77;"
        "    border-radius: 12px;"
        "    padding: 15px;"
        "    font-size: 14px;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    selection-background-color: #415a77;"
        "}"
        );

    // Style pour la zone de saisie de message
    m_lineEditMessage->setStyleSheet(
        "QLineEdit {"
        "    background-color: #415a77;"
        "    color: #e0e1dd;"
        "    border: 2px solid #778da9;"
        "    border-radius: 20px;"
        "    padding: 12px 18px;"
        "    font-size: 14px;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "}"
        "QLineEdit:focus { border-color: #00b4d8; }"
        "QLineEdit::placeholder { color: #a0a4b8; }"
        );

    // Style pour le bouton d'envoi
    m_btnEnvoyer->setStyleSheet(
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #0096c7, stop:1 #0077b6);"
        "    color: white;"
        "    border: none;"
        "    border-radius: 20px;"
        "    padding: 12px 24px;"
        "    font-weight: bold;"
        "    font-size: 14px;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    min-width: 90px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #00b4d8, stop:1 #0096c7);"
        "}"
        "QPushButton:pressed {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #0077b6, stop:1 #023e8a);"
        "}"
        "QPushButton:disabled {"
        "    background: #415a77;"
        "    color: #778da9;"
        "}"
        );

    // Configurer la zone de chat
    m_textEditChat->setReadOnly(true);
    m_lineEditMessage->setPlaceholderText("Type a message...");

    // Créer le layout principal
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(20, 15, 20, 15);
    layoutPrincipal->setSpacing(15);

    // En-tête "All About Sponsoring"
    QHBoxLayout *layoutHeader = new QHBoxLayout();
    QLabel *logoLabel = new QLabel("💼");
    logoLabel->setStyleSheet("font-size: 24px; margin-right: 10px;");

    QLabel *titleLabel = new QLabel("All About Sponsoring");
    titleLabel->setStyleSheet("color: #00b4d8; font-size: 18px; font-weight: bold; font-family: 'Segoe UI', Arial, sans-serif;");

    QLabel *subtitleLabel = new QLabel("Expert en partenariats");
    subtitleLabel->setStyleSheet("color: #90e0ef; font-size: 12px; margin-top: 2px;");

    QVBoxLayout *titleLayout = new QVBoxLayout();
    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(subtitleLabel);

    layoutHeader->addWidget(logoLabel);
    layoutHeader->addLayout(titleLayout);
    layoutHeader->addStretch();

    layoutPrincipal->addLayout(layoutHeader);

    // Ajouter la zone de chat
    layoutPrincipal->addWidget(m_textEditChat);

    // Layout pour la zone de saisie
    QHBoxLayout *layoutMessage = new QHBoxLayout();
    layoutMessage->addWidget(m_lineEditMessage);
    layoutMessage->addWidget(m_btnEnvoyer);
    layoutPrincipal->addLayout(layoutMessage);

    // Configurer la fenêtre
    setWindowTitle("💬 All About Sponsoring - AI Assistant");
    resize(500, 600);

    // Connecter les signaux
    connect(m_btnEnvoyer, &QPushButton::clicked, this, &ChatWindow::envoyerMessage);
    connect(m_lineEditMessage, &QLineEdit::returnPressed, this, &ChatWindow::envoyerMessage);

    // Message de bienvenue formaté comme dans l'image
    afficherMessageBienvenue();
}

void ChatWindow::afficherMessageBienvenue()
{
    QString bienvenueHTML =
        "<div style='margin: 20px 0; text-align: center;'>"
        "<div style='color: #00b4d8; font-size: 16px; font-weight: bold; margin-bottom: 10px;'>"
        "💼 All About Sponsoring"
        "</div>"
        "<div style='color: #90e0ef; font-size: 12px; margin-bottom: 20px;'>"
        "Expert en partenariats"
        "</div>"
        "</div>"

        "<div style='background: linear-gradient(135deg, #1b3a4b, #415a77); padding: 15px; border-radius: 15px; margin: 15px 0; border-left: 4px solid #00b4d8;'>"
        "<div style='color: #e0e1dd; font-size: 14px; line-height: 1.5;'>"
        "Hey, comment je peux vous aider à propos de sponsoring ?"
        "</div>"
        "</div>"

        "<div style='text-align: right; margin: 20px 0;'>"
        "<div style='display: inline-block; background: linear-gradient(135deg, #ff6b6b, #ee5a52); color: white; padding: 12px 18px; border-radius: 18px 18px 5px 18px; max-width: 70%;'>"
        "<div style='font-size: 14px;'>Je veux connaître les meilleures stratégies de sponsoring</div>"
        "<div style='font-size: 10px; color: rgba(255,255,255,0.8); text-align: right; margin-top: 5px;'>Just now</div>"
        "</div>"
        "</div>"

        "<div style='background: linear-gradient(135deg, #415a77, #1b3a4b); padding: 15px; border-radius: 15px; margin: 15px 0; border-left: 4px solid #48cae4;'>"
        "<div style='color: #e0e1dd; font-size: 14px; line-height: 1.5; margin-bottom: 10px;'>"
        "<strong>Excellente question !</strong> Voici quelques stratégies efficaces :"
        "</div>"
        "<div style='background: rgba(0, 180, 216, 0.2); padding: 10px; border-radius: 8px; border: 1px dashed #48cae4; margin: 5px 0;'>"
        "<div style='color: #90e0ef; font-size: 13px;'>🎯 Sponsoring ciblé par audience</div>"
        "</div>"
        "<div style='background: rgba(0, 180, 216, 0.2); padding: 10px; border-radius: 8px; border: 1px dashed #48cae4; margin: 5px 0;'>"
        "<div style='color: #90e0ef; font-size: 13px;'>📊 Partenariats valeur ajoutée</div>"
        "</div>"
        "<div style='background: rgba(0, 180, 216, 0.2); padding: 10px; border-radius: 8px; border: 1px dashed #48cae4; margin: 5px 0;'>"
        "<div style='color: #90e0ef; font-size: 13px;'>💡 Co-création de contenu</div>"
        "</div>"
        "</div>";

    m_textEditChat->setHtml(bienvenueHTML);

    // Descendre en bas
    QScrollBar *scrollbar = m_textEditChat->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
}

void ChatWindow::envoyerMessage()
{
    QString message = m_lineEditMessage->text().trimmed();
    if (message.isEmpty()) return;

    QString heure = QDateTime::currentDateTime().toString("hh:mm");

    // BULLE UTILISATEUR - Style moderne inspiré de l'image
    QString bulleUtilisateur =
        "<div style='margin: 15px 0; display: flex; justify-content: flex-end;'>"
        "<div style='max-width: 80%;'>"
        "<div style='background: linear-gradient(135deg, #ff6b6b, #ee5a52); color: #ffffff; padding: 12px 16px; border-radius: 18px 18px 5px 18px; box-shadow: 0 2px 10px rgba(255,107,107,0.3);'>"
        "<div style='font-size: 14px; line-height: 1.4; font-family: \"Segoe UI\", Arial, sans-serif;'>" + message + "</div>"
                    "<div style='font-size: 10px; color: rgba(255,255,255,0.8); text-align: right; margin-top: 6px;'>" + heure + "</div>"
                  "</div>"
                  "<div style='font-size: 11px; color: #90e0ef; text-align: right; margin-top: 4px; padding-right: 8px;'>👤 You</div>"
                  "</div>"
                  "</div>";

    m_textEditChat->append(bulleUtilisateur);
    m_lineEditMessage->clear();
    m_btnEnvoyer->setEnabled(false);
    // APRÈS LA BULLE UTILISATEUR, AVANT L'ENVOI À GEMINI :

    // ================= DÉTECTION SPONSOR BASE =================
    QString sponsorTrouve = "";
    QString infosSponsor = "";

    QStringList mots = message.split(" ", Qt::SkipEmptyParts);
    for (const QString& mot : mots) {
        if (mot.length() > 2) {
            if (sponsorExisteDansBase(mot)) {
                sponsorTrouve = mot;
                infosSponsor = getInfosSponsor(mot);
                break;
            }
        }
    }

    // ================= AFFICHER INFOS BASE =================
    // ================= AFFICHER INFOS BASE =================
    if (!sponsorTrouve.isEmpty()) {
        QString bulleBase =
            "<div style='margin: 10px 0; display: flex; justify-content: center;'>"
            "<div style='max-width: 90%;'>"
            "<div style='background: linear-gradient(135deg, #ff4757, #ff3838); color: #ffffff; padding: 12px 16px; border-radius: 15px; border: 2px solid #ff0000; box-shadow: 0 2px 10px rgba(255,0,0,0.3);'>"
            "<div style='font-size: 14px; line-height: 1.4; font-family: \"Segoe UI\", Arial, sans-serif; font-weight: bold; text-align: center;'>"
            "✅ " + sponsorTrouve.toUpper() + " - EXISTE DANS VOTRE BASE"
                                        "</div>"
                                        "<div style='font-size: 12px; margin-top: 8px; line-height: 1.3; text-align: center;'>" + infosSponsor + "</div>"
                             "<div style='font-size: 10px; color: rgba(255,255,255,0.8); text-align: right; margin-top: 6px;'>" + heure + "</div>"
                      "</div>"
                      "</div>"
                      "</div>";

        m_textEditChat->append(bulleBase);
        QScrollBar *scrollbar = m_textEditChat->verticalScrollBar();
        scrollbar->setValue(scrollbar->maximum());
    }
    m_geminiManager->poserQuestion(message);

    // Descendre en bas
    QScrollBar *scrollbar = m_textEditChat->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
}

void ChatWindow::afficherReponseIA(const QString& reponse)
{
    m_btnEnvoyer->setEnabled(true);

    QString heure = QDateTime::currentDateTime().toString("hh:mm");

    // BULLE IA - Style moderne inspiré de l'image
    QString bulleIA =
        "<div style='margin: 15px 0; display: flex; justify-content: flex-start;'>"
        "<div style='max-width: 80%;'>"
        "<div style='background: linear-gradient(135deg, #415a77, #1b3a4b); color: #e0e1dd; padding: 12px 16px; border-radius: 18px 18px 18px 5px; border-left: 4px solid #00b4d8; box-shadow: 0 2px 10px rgba(0,0,0,0.2);'>"
        "<div style='font-size: 14px; line-height: 1.4; font-family: \"Segoe UI\", Arial, sans-serif;'>" + reponse + "</div>"
                    "<div style='font-size: 10px; color: #90e0ef; text-align: right; margin-top: 6px;'>" + heure + "</div>"
                  "</div>"
                  "<div style='font-size: 11px; color: #90e0ef; text-align: left; margin-top: 4px; padding-left: 8px;'>🤖 Sponsoring Expert</div>"
                  "</div>"
                  "</div>";

    m_textEditChat->append(bulleIA);

    // Descendre en bas automatiquement
    QScrollBar *scrollbar = m_textEditChat->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());

    m_lineEditMessage->setFocus();
}

void ChatWindow::afficherErreur(const QString& message)
{
    m_btnEnvoyer->setEnabled(true);

    QString heure = QDateTime::currentDateTime().toString("hh:mm");

    QString erreurHTML =
        "<div style='margin: 15px 0; display: flex; justify-content: flex-start;'>"
        "<div style='max-width: 80%;'>"
        "<div style='background: linear-gradient(135deg, #b23b3b, #8b2c2c); color: #ffffff; padding: 12px 16px; border-radius: 18px 18px 18px 5px; border-left: 4px solid #ff6b6b;'>"
        "<div style='font-size: 14px; line-height: 1.4; font-family: \"Segoe UI\", Arial, sans-serif;'>"
        "❌ " + message +
        "</div>"
        "<div style='font-size: 10px; color: rgba(255,255,255,0.8); text-align: right; margin-top: 6px;'>" + heure + "</div>"
                  "</div>"
                  "<div style='font-size: 11px; color: #ff6b6b; text-align: left; margin-top: 4px; padding-left: 8px;'>⚠️ System Error</div>"
                  "</div>"
                  "</div>";

    m_textEditChat->append(erreurHTML);

    m_lineEditMessage->setFocus();
}
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

bool ChatWindow::sponsorExisteDansBase(const QString& nomSponsor)
{
    // OUVRE LA CONNEXION À LA BASE
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "❌ Base de données non connectée";
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM SPONSOR WHERE UPPER(NOM) LIKE UPPER(?)");
    query.addBindValue("%" + nomSponsor + "%");

    if (query.exec() && query.next()) {
        bool existe = query.value(0).toInt() > 0;
        qDebug() << "🔍" << nomSponsor << "existe dans base:" << existe;
        return existe;
    } else {
        qDebug() << "❌ Erreur requête:" << query.lastError().text();
        return false;
    }
}

QString ChatWindow::getInfosSponsor(const QString& nomSponsor)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) return "";

    QSqlQuery query;
    query.prepare("SELECT CONTRIBUTION, DATE_DEBUT, DATE_FIN, EMAIL FROM SPONSOR WHERE UPPER(NOM) LIKE UPPER(?)");
    query.addBindValue("%" + nomSponsor + "%");

    if (query.exec() && query.next()) {
        QString infos = QString("Type: %1 | Contrat: %2 à %3 | Email: %4")
                            .arg(query.value(0).toString())
                            .arg(query.value(1).toDate().toString("dd/MM/yyyy"))
                            .arg(query.value(2).toDate().toString("dd/MM/yyyy"))
                            .arg(query.value(3).toString());

        qDebug() << "📋 Infos récupérées pour" << nomSponsor << ":" << infos;
        return infos;
    }

    qDebug() << "❌ Aucune info trouvée pour" << nomSponsor;
    return "Informations non disponibles";
}
// AJOUTE À LA FIN DU FICHIER
ChatWindow::~ChatWindow()
{
    // Destructeur vide - mais nécessaire pour le linking
}
