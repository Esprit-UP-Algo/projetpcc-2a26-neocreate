#include "client.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QEventLoop>
// =============================
// VALIDATION (déjà présente)
// =============================
bool ClientDAO::isInt(const QString& s) {
    QRegularExpression re(R"(^\d+$)");
    return re.match(s).hasMatch();
}

bool ClientDAO::isEmailLike(const QString& s) {
    QRegularExpression re(R"(^[A-Za-z0-9._%+\-]+@[A-Za-z0-9.\-]+\.[A-Za-z]{2,}$)");
    return re.match(s).hasMatch();
}

bool ClientDAO::validate(const Client& c, QString& errorMsg) {
    if (c.ID_CLIENT <= 0) {
        errorMsg = "ID_CLIENT doit être un entier positif.";
        return false;
    }
    if (!isEmailLike(c.EMAIL)) {
        errorMsg = "Email invalide.";
        return false;
    }
    if (c.NOM.trimmed().isEmpty() ||
        c.PRENOM.trimmed().isEmpty() ||
        c.ENTREPRISE.trimmed().isEmpty() ||
        c.TYPE.trimmed().isEmpty()) {
        errorMsg = "Tous les champs sont obligatoires.";
        return false;
    }
    return true;
}

// ========================================
//     IMPLEMENTATION CRUD DE ClientDAO
// ========================================

QVector<Client> ClientDAO::fetchAll()
{
    QVector<Client> list;

    // 👇 AJOUT DATE_AJOUT DANS LE SELECT
    QSqlQuery q("SELECT ID_CLIENT, NOM, PRENOM, ENTREPRISE, EMAIL, TYPE, DATE_AJOUT FROM CLIENT");

    while (q.next()) {
        Client c;
        c.ID_CLIENT  = q.value(0).toInt();
        c.NOM        = q.value(1).toString();
        c.PRENOM     = q.value(2).toString();
        c.ENTREPRISE = q.value(3).toString();
        c.EMAIL      = q.value(4).toString();
        c.TYPE       = q.value(5).toString();
        c.DATE_AJOUT = q.value(6).toDate();   // 👈 NEW DATE_AJOUT

        list.append(c);
    }
    return list;
}

bool ClientDAO::exists(int id_client)
{
    QSqlQuery q;
    q.prepare("SELECT COUNT(*) FROM CLIENT WHERE ID_CLIENT = :id");
    q.bindValue(":id", id_client);
    q.exec();

    if (q.next())
        return q.value(0).toInt() > 0;

    return false;
}

bool ClientDAO::create(const Client& c)
{
    QSqlQuery q;

    // 👇 AJOUT DATE_AJOUT DANS L’INSERT
    q.prepare("INSERT INTO CLIENT (ID_CLIENT, NOM, PRENOM, ENTREPRISE, EMAIL, TYPE, DATE_AJOUT) "
              "VALUES (:id, :nom, :pre, :ent, :email, :type, :dateajout)");

    q.bindValue(":id", c.ID_CLIENT);
    q.bindValue(":nom", c.NOM);
    q.bindValue(":pre", c.PRENOM);
    q.bindValue(":ent", c.ENTREPRISE);
    q.bindValue(":email", c.EMAIL);
    q.bindValue(":type", c.TYPE);

    // 👇 NOUVELLE BIND DATE_AJOUT
    q.bindValue(":dateajout", c.DATE_AJOUT);  // QDate envoyé depuis Qt

    return q.exec();
}

bool ClientDAO::update(const Client& c)
{
    QSqlQuery q;
    q.prepare(R"(
        UPDATE CLIENT SET
            NOM        = :nom,
            PRENOM     = :pre,
            ENTREPRISE = :ent,
            EMAIL      = :email,
            TYPE       = :type,
            DATE_AJOUT = :dateajout        -- 👈 on met à jour la date
        WHERE ID_CLIENT = :id
    )");

    q.bindValue(":nom",       c.NOM);
    q.bindValue(":pre",       c.PRENOM);
    q.bindValue(":ent",       c.ENTREPRISE);
    q.bindValue(":email",     c.EMAIL);
    q.bindValue(":type",      c.TYPE);
    q.bindValue(":dateajout", c.DATE_AJOUT);   // 🔥 nouvelle date choisie
    q.bindValue(":id",        c.ID_CLIENT);

    return q.exec();
}

bool ClientDAO::remove(int id_client)
{
    QSqlQuery q;
    q.prepare("DELETE FROM CLIENT WHERE ID_CLIENT = :id");
    q.bindValue(":id", id_client);
    return q.exec();
}



// ===============================
// HISTORIQUE CLIENT – NE PAS TOUCHER
// ===============================

#include <QApplication>
#include <QDateTime>
#include <QTextStream>
#include <QFile>
#include <QStringConverter>

QListWidget* ClientHistory::m_listWidget = nullptr;

void ClientHistory::setListWidget(QListWidget *list)
{
    m_listWidget = list;
}

QString ClientHistory::logPath()
{
    return QApplication::applicationDirPath() + "/client_history.log";
}

void ClientHistory::addEntry(const QString &action, int id, const QString &nom)
{
    QString ts = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString msg = QString("[%1] %2 - Client #%3 (%4)")
                      .arg(ts, action, QString::number(id), nom);

    if (m_listWidget) {
        m_listWidget->insertItem(0, msg);
        if (m_listWidget->count() > 50)
            delete m_listWidget->item(50);
    }

    saveToFile(msg);
}

void ClientHistory::saveToFile(const QString &msg)
{
    QFile f(logPath());
    if (f.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&f);
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
        out.setEncoding(QStringConverter::Utf8);
#endif
        out << msg << "\n";
        f.close();
    }
}

void ClientHistory::loadHistory()
{
    if (!m_listWidget) return;

    m_listWidget->clear();

    QFile f(logPath());
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&f);
#if QT_VERSION >= QT_VERSION_CHECK(6,0,0)
    in.setEncoding(QStringConverter::Utf8);
#endif

    QStringList all;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.isEmpty())
            all.prepend(line);
    }

    int start = qMax(0, all.size() - 50);
    for (int i = start; i < all.size(); ++i)
        m_listWidget->addItem(all[i]);

    f.close();
}

void ClientHistory::clearHistory()
{
    if (m_listWidget)
        m_listWidget->clear();

    QFile f(logPath());
    if (f.open(QIODevice::WriteOnly | QIODevice::Text)) {
        f.resize(0);
        f.close();
    }
}
// =============================
//  TWILIO : ENVOI SMS
// =============================

// ⚠️ Mets tes vraies infos Twilio ici :
static const char* TWILIO_ACCOUNT_SID = "AC0b810ce76bedb9aa78fb1eaf984fa287";  // SID
static const char* TWILIO_AUTH_TOKEN  = "5106c8c1a0de665209229833c5fdb55a";   // Token
static const char* TWILIO_FROM_NUMBER = "+15172009154";                       // Numéro Twilio


bool sendSmsTwilio(const QString &toE164, const QString &body)
{
    // 1) Manager réseau
    QNetworkAccessManager manager;

    // 2) Construire l’URL Twilio
    QString urlStr =
        QString("https://api.twilio.com/2010-04-01/Accounts/%1/Messages.json")
            .arg(TWILIO_ACCOUNT_SID);

    // 👉 On sépare en 2 lignes pour éviter tout bug de parsing
    QUrl url(urlStr);
    QNetworkRequest req(url);

    // 3) Headers
    req.setHeader(QNetworkRequest::ContentTypeHeader,
                  "application/x-www-form-urlencoded");

    // Auth Basic : SID:TOKEN
    QByteArray creds = QByteArray(TWILIO_ACCOUNT_SID) + ":" + TWILIO_AUTH_TOKEN;
    QByteArray authHeader = "Basic " + creds.toBase64();
    req.setRawHeader("Authorization", authHeader);

    // 4) Corps de la requête (POST)
    QUrlQuery params;
    params.addQueryItem("To",   toE164);
    params.addQueryItem("From", TWILIO_FROM_NUMBER);
    params.addQueryItem("Body", body);

    QByteArray postData = params.toString(QUrl::FullyEncoded).toUtf8();

    // 5) Envoi + attente
    QEventLoop loop;
    QNetworkReply *reply = manager.post(req, postData);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // 6) Vérification
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Twilio error:" << reply->errorString();
        qDebug() << "Twilio details:" << reply->readAll();
        reply->deleteLater();
        return false;
    }

    qDebug() << "Twilio OK:" << reply->readAll();
    reply->deleteLater();
    return true;
}
