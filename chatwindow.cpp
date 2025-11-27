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
#include <QSqlQuery>
#include <QSqlError>
#include <QApplication>
#include <QDebug>

ChatWindow::ChatWindow(QWidget *parent) : QDialog(parent)
{
    setupUI();
    setupConnections();

    // Message de bienvenue formaté
    afficherMessageBienvenue();
}

void ChatWindow::setupUI()
{
    // === STYLE THÈME SOMBRE AMÉLIORÉ ===
    this->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #0d1b2a, stop:0.5 #1b263b, stop:1 #0d1b2a); color: #e0e1dd;");

    // Créer tous les widgets
    m_textEditChat = new QTextEdit(this);
    m_lineEditMessage = new QLineEdit(this);
    m_btnEnvoyer = new QPushButton("Send", this);
    m_typingIndicator = new QLabel(this);
    m_typingTimer = new QTimer(this);

    // === INITIALISER GEMINI MANAGER ===
    QString apiKey = "AIzaSyC4P3Ri6n9p1ahQeTRhdwXtFReJV95ozuw";
    m_geminiManager = new GeminiManager(apiKey, this);

    // === STYLE ZONE DE CHAT AMÉLIORÉE ===
    m_textEditChat->setStyleSheet(
        "QTextEdit {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "        stop:0 #0d1b2a, stop:0.5 #1b263b, stop:1 #0d1b2a);"
        "    color: #e0e1dd;"
        "    border: 2px solid #415a77;"
        "    border-radius: 16px;"
        "    padding: 20px;"
        "    font-size: 14px;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    selection-background-color: #415a77;"
        "}"
        );

    // === STYLE ZONE DE SAISIE AVEC ICÔNE ===
    m_lineEditMessage->setStyleSheet(
        "QLineEdit {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #415a77, stop:1 #1b263b);"
        "    color: #e0e1dd;"
        "    border: 2px solid #778da9;"
        "    border-radius: 25px;"
        "    padding: 15px 50px 15px 20px;"
        "    font-size: 14px;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "}"
        "QLineEdit:focus {"
        "    border-color: #00b4d8;"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #415a77, stop:1 #1b263b);"
        "}"
        "QLineEdit::placeholder {"
        "    color: #a0a4b8;"
        "    font-style: italic;"
        "}"
        );

    // === STYLE BOUTON ENVOYER AMÉLIORÉ ===
    m_btnEnvoyer->setStyleSheet(
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #0096c7, stop:1 #0077b6);"
        "    color: white;"
        "    border: none;"
        "    border-radius: 25px;"
        "    padding: 15px 30px;"
        "    font-weight: bold;"
        "    font-size: 14px;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    min-width: 100px;"
        "    margin-left: 10px;"
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

    // === INDICATEUR DE FRAPPE ===
    m_typingIndicator->setText("🤖 Sponsoring Expert is typing...");
    m_typingIndicator->setStyleSheet(
        "color: #90e0ef; font-size: 12px; font-style: italic; padding: 8px 20px; "
        "background: rgba(0, 180, 216, 0.1); border-radius: 15px; margin: 5px 20px;"
        );
    m_typingIndicator->setVisible(false);
    m_typingIndicator->setAlignment(Qt::AlignCenter);

    // Configurer la zone de chat
    m_textEditChat->setReadOnly(true);
    m_lineEditMessage->setPlaceholderText("💬 Type your message about sponsoring...");

    // === CRÉER LE LAYOUT PRINCIPAL ===
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->setContentsMargins(20, 15, 20, 15);
    layoutPrincipal->setSpacing(12);

    // === EN-TÊTE PROFESSIONNEL ===
    QHBoxLayout *layoutHeader = new QHBoxLayout();

    // Logo gradient
    QLabel *logoLabel = new QLabel("💼");
    logoLabel->setStyleSheet(
        "font-size: 24px; margin-right: 12px; padding: 10px; "
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #00b4d8, stop:1 #0077b6); "
        "border-radius: 50%; width: 45px; height: 45px; text-align: center;"
        );

    // Titres
    QVBoxLayout *titleLayout = new QVBoxLayout();
    QLabel *titleLabel = new QLabel("All About Sponsoring");
    titleLabel->setStyleSheet("color: #00b4d8; font-size: 22px; font-weight: bold; font-family: 'Segoe UI', Arial, sans-serif;");

    QLabel *subtitleLabel = new QLabel("🤖 Expert IA en partenariats");
    subtitleLabel->setStyleSheet("color: #90e0ef; font-size: 13px; margin-top: 2px; font-style: italic;");

    titleLayout->addWidget(titleLabel);
    titleLayout->addWidget(subtitleLabel);

    // Statut en ligne
    QLabel *statusLabel = new QLabel("🟢 En ligne");
    statusLabel->setStyleSheet("color: #4ade80; font-size: 11px; background: rgba(74, 222, 128, 0.1); padding: 6px 12px; border-radius: 12px;");

    layoutHeader->addWidget(logoLabel);
    layoutHeader->addLayout(titleLayout);
    layoutHeader->addStretch();
    layoutHeader->addWidget(statusLabel);

    layoutPrincipal->addLayout(layoutHeader);

    // === BOUTONS D'ACTIONS RAPIDES ===
    setupQuickActions(layoutPrincipal);

    // === ZONE DE CHAT ===
    layoutPrincipal->addWidget(m_textEditChat);

    // === INDICATEUR DE FRAPPE ===
    layoutPrincipal->addWidget(m_typingIndicator);

    // === ZONE DE SAISIE ===
    QHBoxLayout *layoutMessage = new QHBoxLayout();
    layoutMessage->addWidget(m_lineEditMessage);
    layoutMessage->addWidget(m_btnEnvoyer);
    layoutPrincipal->addLayout(layoutMessage);

    // === CONFIGURATION FENÊTRE ===
    setWindowTitle("💬 All About Sponsoring - AI Assistant");
    resize(550, 700);
    setMinimumSize(500, 600);
}

void ChatWindow::setupQuickActions(QVBoxLayout *mainLayout)
{
    QHBoxLayout *layoutQuickActions = new QHBoxLayout();
    QStringList quickButtons = {"🎯 Stratégies", "🏢 Sponsors", "💰 Budget", "📞 Contact", "📊 Analytics"};

    for (const QString &text : quickButtons) {
        QPushButton *btn = new QPushButton(text, this);
        btn->setStyleSheet(
            "QPushButton {"
            "    background: rgba(65, 90, 119, 0.7);"
            "    color: #e0e1dd;"
            "    border: 1px solid #778da9;"
            "    border-radius: 18px;"
            "    padding: 10px 16px;"
            "    font-size: 12px;"
            "    font-weight: bold;"
            "    margin: 3px;"
            "}"
            "QPushButton:hover {"
            "    background: rgba(0, 180, 216, 0.4);"
            "    border-color: #00b4d8;"
            "}"
            "QPushButton:pressed {"
            "    background: rgba(0, 119, 182, 0.6);"
            "}"
            );
        connect(btn, &QPushButton::clicked, this, [this, text]() {
            QString question;
            if (text.contains("Stratégies")) question = "Quelles sont les meilleures stratégies de sponsoring ?";
            else if (text.contains("Sponsors")) question = "Comment trouver des sponsors pertinents ?";
            else if (text.contains("Budget")) question = "Comment établir un budget de sponsoring ?";
            else if (text.contains("Contact")) question = "Quelles sont les techniques de prise de contact avec les sponsors ?";
            else question = "Quels analytics suivre pour mes partenariats ?";

            m_lineEditMessage->setText(question);
            envoyerMessage();
        });
        layoutQuickActions->addWidget(btn);
    }

    mainLayout->addLayout(layoutQuickActions);
}

void ChatWindow::setupConnections()
{
    // Connecter les signaux de GeminiManager
    connect(m_geminiManager, &GeminiManager::reponseRecue, this, &ChatWindow::afficherReponseIA);
    connect(m_geminiManager, &GeminiManager::erreur, this, &ChatWindow::afficherErreur);

    // Connecter l'interface
    connect(m_btnEnvoyer, &QPushButton::clicked, this, &ChatWindow::envoyerMessage);
    connect(m_lineEditMessage, &QLineEdit::returnPressed, this, &ChatWindow::envoyerMessage);

    // Timer pour l'indicateur de frappe
    connect(m_typingTimer, &QTimer::timeout, this, &ChatWindow::cacherTypingIndicator);
}

void ChatWindow::afficherMessageBienvenue()
{
    QString styleCSS =
        "<style>"
        "@keyframes fadeIn { from { opacity: 0; transform: translateY(10px); } to { opacity: 1; transform: translateY(0); } }"
        ".message { animation: fadeIn 0.6s ease-out; }"
        ".user-message { animation: fadeIn 0.4s ease-out; }"
        "</style>";

    QString bienvenueHTML = styleCSS +
                            "<div class='message' style='margin: 20px 0; text-align: center;'>"
                            "<div style='color: #00b4d8; font-size: 18px; font-weight: bold; margin-bottom: 8px;'>"
                            "💼 All About Sponsoring"
                            "</div>"
                            "<div style='color: #90e0ef; font-size: 13px; margin-bottom: 25px; padding: 8px; background: rgba(0, 180, 216, 0.1); border-radius: 10px;'>"
                            "🤖 Expert IA en partenariats"
                            "</div>"
                            "</div>"

                            "<div class='message' style='background: linear-gradient(135deg, #1b3a4b, #415a77); padding: 18px; border-radius: 18px; margin: 20px 0; border-left: 4px solid #00b4d8; box-shadow: 0 4px 15px rgba(0,0,0,0.2);'>"
                            "<div style='color: #e0e1dd; font-size: 14px; line-height: 1.5;'>"
                            "👋 <strong>Hey !</strong> Comment je peux vous aider avec vos stratégies de sponsoring aujourd'hui ?"
                            "</div>"
                            "</div>"

                            "<div class='user-message' style='text-align: right; margin: 25px 0;'>"
                            "<div style='display: inline-block; background: linear-gradient(135deg, #ff6b6b, #ee5a52); color: white; padding: 14px 20px; border-radius: 20px 20px 6px 20px; max-width: 75%; box-shadow: 0 4px 15px rgba(255,107,107,0.3); position: relative;'>"
                            "<div style='position: absolute; top: -8px; right: 15px; background: #ff6b6b; color: white; border-radius: 50%; width: 24px; height: 24px; text-align: center; font-size: 12px; line-height: 24px;'>👤</div>"
                            "<div style='font-size: 14px; line-height: 1.4; font-family: \"Segoe UI\", Arial, sans-serif; margin-top: 8px;'>Je veux connaître les meilleures stratégies de sponsoring</div>"
                            "<div style='font-size: 10px; color: rgba(255,255,255,0.9); text-align: right; margin-top: 8px; padding-top: 5px; border-top: 1px solid rgba(255,255,255,0.2);'>Just now</div>"
                            "</div>"
                            "</div>"

                            "<div class='message' style='background: linear-gradient(135deg, #415a77, #1b3a4b); padding: 18px; border-radius: 18px; margin: 20px 0; border-left: 4px solid #48cae4; box-shadow: 0 4px 15px rgba(0,0,0,0.2); position: relative;'>"
                            "<div style='position: absolute; top: -8px; left: 15px; background: #48cae4; color: white; border-radius: 50%; width: 24px; height: 24px; text-align: center; font-size: 12px; line-height: 24px;'>🤖</div>"
                            "<div style='color: #e0e1dd; font-size: 14px; line-height: 1.5; margin-bottom: 15px; margin-top: 10px;'>"
                            "<strong>🎉 Excellente question !</strong> Voici quelques stratégies efficaces :"
                            "</div>"
                            "<div style='background: rgba(0, 180, 216, 0.25); padding: 12px; border-radius: 12px; border: 1px dashed #48cae4; margin: 8px 0;'>"
                            "<div style='color: #90e0ef; font-size: 13px; font-weight: bold;'>🎯 Sponsoring ciblé par audience</div>"
                            "</div>"
                            "<div style='background: rgba(0, 180, 216, 0.25); padding: 12px; border-radius: 12px; border: 1px dashed #48cae4; margin: 8px 0;'>"
                            "<div style='color: #90e0ef; font-size: 13px; font-weight: bold;'>📊 Partenariats valeur ajoutée</div>"
                            "</div>"
                            "<div style='background: rgba(0, 180, 216, 0.25); padding: 12px; border-radius: 12px; border: 1px dashed #48cae4; margin: 8px 0;'>"
                            "<div style='color: #90e0ef; font-size: 13px; font-weight: bold;'>💡 Co-création de contenu</div>"
                            "</div>"
                            "<div style='font-size: 11px; color: #90e0ef; text-align: right; margin-top: 12px; padding-top: 8px; border-top: 1px solid rgba(144, 224, 239, 0.2);'>Prêt à approfondir ?</div>"
                            "</div>";

    m_textEditChat->setHtml(bienvenueHTML);

    // Descendre en bas
    QTimer::singleShot(100, [this]() {
        QScrollBar *scrollbar = m_textEditChat->verticalScrollBar();
        scrollbar->setValue(scrollbar->maximum());
    });
}

void ChatWindow::envoyerMessage()
{
    QString message = m_lineEditMessage->text().trimmed();
    if (message.isEmpty()) return;

    QString heure = QDateTime::currentDateTime().toString("HH:mm");

    // BULLE UTILISATEUR - Style moderne
    QString bulleUtilisateur =
        "<div class='user-message' style='margin: 20px 0; display: flex; justify-content: flex-end;'>"
        "<div style='max-width: 80%;'>"
        "<div style='background: linear-gradient(135deg, #ff6b6b, #ee5a52); color: #ffffff; padding: 14px 18px; border-radius: 20px 20px 6px 20px; box-shadow: 0 4px 15px rgba(255,107,107,0.3); position: relative;'>"
        "<div style='position: absolute; top: -8px; right: 15px; background: #ff6b6b; color: white; border-radius: 50%; width: 24px; height: 24px; text-align: center; font-size: 12px; line-height: 24px;'>👤</div>"
        "<div style='font-size: 14px; line-height: 1.4; font-family: \"Segoe UI\", Arial, sans-serif; margin-top: 8px;'>" + message + "</div>"
                    "<div style='font-size: 10px; color: rgba(255,255,255,0.9); text-align: right; margin-top: 8px; padding-top: 5px; border-top: 1px solid rgba(255,255,255,0.2);'>" + heure + "</div>"
                  "</div>"
                  "<div style='font-size: 11px; color: #90e0ef; text-align: right; margin-top: 6px; padding-right: 12px;'>You</div>"
                  "</div>"
                  "</div>";

    m_textEditChat->append(bulleUtilisateur);
    m_lineEditMessage->clear();
    m_btnEnvoyer->setEnabled(false);

    // Afficher l'indicateur de frappe
    afficherTypingIndicator();

    // Détection sponsor
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

    // Afficher infos sponsor si trouvé
    if (!sponsorTrouve.isEmpty()) {
        QString bulleBase =
            "<div style='margin: 15px 0; display: flex; justify-content: center;'>"
            "<div style='max-width: 90%;'>"
            "<div style='background: linear-gradient(135deg, #ff4757, #ff3838); color: #ffffff; padding: 15px 20px; border-radius: 16px; border: 2px solid #ff0000; box-shadow: 0 4px 15px rgba(255,0,0,0.3);'>"
            "<div style='font-size: 15px; line-height: 1.4; font-family: \"Segoe UI\", Arial, sans-serif; font-weight: bold; text-align: center; margin-bottom: 8px;'>"
            "✅ " + sponsorTrouve.toUpper() + " - TROUVÉ DANS VOTRE BASE"
                                        "</div>"
                                        "<div style='font-size: 13px; line-height: 1.4; text-align: center; background: rgba(255,255,255,0.1); padding: 8px; border-radius: 8px;'>" + infosSponsor + "</div>"
                             "<div style='font-size: 10px; color: rgba(255,255,255,0.8); text-align: right; margin-top: 10px; padding-top: 5px; border-top: 1px solid rgba(255,255,255,0.2);'>" + heure + "</div>"
                      "</div>"
                      "</div>"
                      "</div>";

        m_textEditChat->append(bulleBase);
    }

    // Envoyer à Gemini
    m_geminiManager->poserQuestion(message);

    // Scroll automatique
    QScrollBar *scrollbar = m_textEditChat->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
}

void ChatWindow::afficherTypingIndicator()
{
    m_typingIndicator->setVisible(true);
    m_typingTimer->start(2000); // Cache après 2 secondes
}

void ChatWindow::cacherTypingIndicator()
{
    m_typingIndicator->setVisible(false);
    m_typingTimer->stop();
}

void ChatWindow::afficherReponseIA(const QString& reponse)
{
    m_btnEnvoyer->setEnabled(true);
    cacherTypingIndicator();

    QString heure = QDateTime::currentDateTime().toString("HH:mm");

    // BULLE IA - Style moderne avec animation
    QString bulleIA =
        "<div class='message' style='margin: 20px 0; display: flex; justify-content: flex-start;'>"
        "<div style='max-width: 85%;'>"
        "<div style='background: linear-gradient(135deg, #415a77, #1b3a4b); color: #e0e1dd; padding: 18px 20px; border-radius: 20px 20px 20px 8px; border-left: 4px solid #00b4d8; box-shadow: 0 4px 15px rgba(0,0,0,0.3); position: relative;'>"
        "<div style='position: absolute; top: -8px; left: 15px; background: #00b4d8; color: white; border-radius: 50%; width: 24px; height: 24px; text-align: center; font-size: 12px; line-height: 24px;'>🤖</div>"
        "<div style='font-size: 14px; line-height: 1.5; font-family: \"Segoe UI\", Arial, sans-serif; margin-top: 10px;'>" + reponse + "</div>"
                    "<div style='font-size: 10px; color: #90e0ef; text-align: right; margin-top: 12px; padding-top: 8px; border-top: 1px solid rgba(144, 224, 239, 0.2);'>" + heure + "</div>"
                  "</div>"
                  "<div style='font-size: 11px; color: #90e0ef; text-align: left; margin-top: 6px; padding-left: 12px;'>🤖 Sponsoring Expert</div>"
                  "</div>"
                  "</div>";

    m_textEditChat->append(bulleIA);

    // Scroll automatique avec délai pour l'animation
    QTimer::singleShot(100, [this]() {
        QScrollBar *scrollbar = m_textEditChat->verticalScrollBar();
        scrollbar->setValue(scrollbar->maximum());
    });

    m_lineEditMessage->setFocus();
}

void ChatWindow::afficherErreur(const QString& message)
{
    m_btnEnvoyer->setEnabled(true);
    cacherTypingIndicator();

    QString heure = QDateTime::currentDateTime().toString("HH:mm");

    QString erreurHTML =
        "<div style='margin: 20px 0; display: flex; justify-content: flex-start;'>"
        "<div style='max-width: 80%;'>"
        "<div style='background: linear-gradient(135deg, #b23b3b, #8b2c2c); color: #ffffff; padding: 15px 18px; border-radius: 18px 18px 18px 8px; border-left: 4px solid #ff6b6b; box-shadow: 0 4px 15px rgba(255,0,0,0.2);'>"
        "<div style='font-size: 14px; line-height: 1.4; font-family: \"Segoe UI\", Arial, sans-serif;'>"
        "⚠️ " + message +
        "</div>"
        "<div style='font-size: 10px; color: rgba(255,255,255,0.8); text-align: right; margin-top: 10px; padding-top: 5px; border-top: 1px solid rgba(255,255,255,0.2);'>" + heure + "</div>"
                  "</div>"
                  "<div style='font-size: 11px; color: #ff6b6b; text-align: left; margin-top: 6px; padding-left: 12px;'>⚠️ System</div>"
                  "</div>"
                  "</div>";

    m_textEditChat->append(erreurHTML);
    m_lineEditMessage->setFocus();
}

bool ChatWindow::sponsorExisteDansBase(const QString& nomSponsor)
{
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
        QString infos = QString("💰 Contribution: %1\n📅 Contrat: %2 - %3\n📧 Email: %4")
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

void ChatWindow::poserQuestion(const QString& question)
{
    m_lineEditMessage->setText(question);
    envoyerMessage();
}

ChatWindow::~ChatWindow()
{
    // Nettoyage
    if (m_typingTimer && m_typingTimer->isActive()) {
        m_typingTimer->stop();
    }
}
