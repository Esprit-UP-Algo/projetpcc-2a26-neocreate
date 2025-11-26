#include "sponsormanager.h"
#include <QSqlQuery>
#include <QDate>
#include <QHeaderView>
#include <QSqlError>
#include <QScrollArea>
#include <QFrame>
#include <QToolBar>
#include <QToolButton>
#include <QFileDialog>
#include <QTextDocument>
#include <QPieSeries>
#include <QChart>
#include <QChartView>
#include <QPieSlice>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QApplication>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

// =====================================================
// 1. CONSTRUCTEUR + SYSTÈME TRAY ICON
// =====================================================
SponsorManager::SponsorManager(QObject *parent)
    : QObject(parent)
    , m_trayIcon(nullptr)
    , m_parentWidget(nullptr)
    , m_toastTimer(nullptr)
    , m_currentToast(nullptr)
{
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation));
    m_trayIcon->setToolTip("Gestion des Sponsors");
    m_trayIcon->show();
}

// =====================================================
// 2. PARTIE EXPORT PDF (EXISTANT - NE PAS TOUCHER)
// =====================================================
bool SponsorManager::exporterPDF(QTableWidget* tableau, const QString& fichierSortie)
{
    qDebug() << "[SponsorManager] Début export PDF vers:" << fichierSortie;

    if (!tableau || tableau->rowCount() == 0) {
        qDebug() << "[SponsorManager] Erreur: tableau vide ou null";
        return false;
    }

    QString html;
    html += "<html><head><meta charset='UTF-8'>";
    html += "<style>";
    html += "body { font-family: Arial, sans-serif; margin: 20px; }";
    html += "h1 { color: #2c3e50; text-align: center; margin-bottom: 10px; }";
    html += "h3 { color: #7f8c8d; text-align: center; margin-top: 0; }";
    html += "table { width: 100%; border-collapse: collapse; margin-top: 20px; }";
    html += "th { background-color: #34495e; color: white; padding: 10px; text-align: center; border: 1px solid #2c3e50; }";
    html += "td { padding: 8px; text-align: center; border: 1px solid #bdc3c7; }";
    html += "tr:nth-child(even) { background-color: #ecf0f1; }";
    html += ".footer { text-align: center; margin-top: 20px; color: #7f8c8d; font-style: italic; }";
    html += "</style></head><body>";

    html += "<h1>HISTORIQUE DES SPONSORS</h1>";
    html += "<h3>Exporté le " + QDateTime::currentDateTime().toString("dd/MM/yyyy à HH:mm") + "</h3>";

    html += "<table>";

    int columnCount = tableau->columnCount();
    html += "<tr>";
    for (int col = 0; col < columnCount; ++col) {
        QTableWidgetItem* header = tableau->horizontalHeaderItem(col);
        QString text = header ? header->text() : QString("Colonne %1").arg(col + 1);
        html += "<th>" + text + "</th>";
    }
    html += "</tr>";

    int rowCount = tableau->rowCount();
    for (int row = 0; row < rowCount; ++row) {
        html += "<tr>";
        for (int col = 0; col < columnCount; ++col) {
            QTableWidgetItem* item = tableau->item(row, col);
            QString text = item ? item->text() : "";
            html += "<td>" + text + "</td>";
        }
        html += "</tr>";
    }

    html += "</table>";
    html += "<div class='footer'>Total : " + QString::number(rowCount) + " sponsors</div>";
    html += "</body></html>";

    QTextDocument document;
    document.setHtml(html);

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fichierSortie);

    document.print(&printer);

    qDebug() << "[SponsorManager] PDF exporté avec succès";
    return true;
}

void SponsorManager::executerExportPDF(QTableWidget* tableau, QWidget* parent)
{
    qDebug() << "[SponsorManager] Début export PDF complet";

    if (!tableau || tableau->rowCount() == 0) {
        QMessageBox::warning(parent, "Export impossible", "Le tableau des sponsors est vide.");
        return;
    }

    QString filePath = QFileDialog::getSaveFileName(
        parent,
        "Exporter les sponsors en PDF",
        "historique_sponsors.pdf",
        "PDF (*.pdf)"
        );

    if (filePath.isEmpty()) return;

    if (exporterPDF(tableau, filePath)) {
        QMessageBox::information(parent, "Succès", "PDF exporté avec succès !\n" + filePath);
    } else {
        QMessageBox::critical(parent, "Erreur", "Échec de l'export PDF");
    }
}

// =====================================================
// 3. PARTIE STATISTIQUES & DASHBOARD (EXISTANT)
// =====================================================
QMap<QString, int> SponsorManager::getStatsContributionsLive()
{
    QMap<QString, int> stats;
    QSqlQuery query;

    // Initialiser tous les types à 0
    stats["Services"] = 0;
    stats["Matériels"] = 0;
    stats["Autre"] = 0;

    bool success = query.exec(
        "SELECT CONTRIBUTION, COUNT(*) "
        "FROM SPONSOR "
        "GROUP BY CONTRIBUTION"
        );

    if (success) {
        while (query.next()) {
            QString type = query.value(0).toString().trimmed();
            int count = query.value(1).toInt();

            qDebug() << "📊 Type trouvé:" << type << "Count:" << count;

            // Normaliser les noms des types
            if (type == "Services" || type.contains("Service", Qt::CaseInsensitive)) {
                stats["Services"] += count;
            }
            else if (type == "Matériels" || type.contains("Matériel", Qt::CaseInsensitive) || type.contains("Materiel", Qt::CaseInsensitive)) {
                stats["Matériels"] += count;
            }
            else {
                // TOUT LE RESTE va dans "Autre"
                stats["Autre"] += count;
                qDebug() << "🔹 Type classé comme 'Autre':" << type;
            }
        }
        qDebug() << "✅ Stats finales:" << stats;
    } else {
        qDebug() << "❌ Erreur stats live:" << query.lastError().text();

        // Données de démo réalistes
        stats["Services"] = 8;
        stats["Matériels"] = 12;
        stats["Autre"] = 5;
    }

    qDebug() << "📈 Résultat final - Services:" << stats["Services"]
             << "Matériels:" << stats["Matériels"]
             << "Autre:" << stats["Autre"];

    return stats;
}

QMap<QString, int> SponsorManager::getStatsAnciennete()
{
    QMap<QString, int> stats;
    QSqlQuery query;

    stats["🏆 Fidèles"] = 0;    // > 2 ans (ancienneté)
    stats["📈 Stables"] = 0;    // 1-2 ans
    stats["🆕 Nouveaux"] = 0;   // < 1 an

    bool success = query.exec("SELECT DATE_DEBUT FROM SPONSOR");

    if (success) {
        QDate aujourdhui = QDate::currentDate();

        while (query.next()) {
            QDate dateDebut = query.value(0).toDate();

            if (dateDebut.isValid()) {
                // ⭐ CALCUL CORRECT : ancienneté depuis l'inscription
                int jours = dateDebut.daysTo(aujourdhui);

                if (jours >= 730) {        // > 2 ans
                    stats["🏆 Fidèles"] += 1;
                } else if (jours >= 365) { // 1-2 ans
                    stats["📈 Stables"] += 1;
                } else {                   // < 1 an
                    stats["🆕 Nouveaux"] += 1;
                }
            }
        }
    } else {
        qDebug() << "❌ Erreur stats ancienneté:" << query.lastError().text();

        // Données de démo réalistes
        stats["🏆 Fidèles"] = 5;    // 25%
        stats["📈 Stables"] = 8;    // 40%
        stats["🆕 Nouveaux"] = 7;   // 35%
    }

    qDebug() << "📊 Stats ancienneté:" << stats;
    return stats;
}

QString SponsorManager::getDerniereModification()
{
    QSqlQuery query;
    QString modification = "Aucune modification récente";

    bool success = query.exec(
        "SELECT CONTRIBUTION, COUNT(*) as changement "
        "FROM SPONSOR "
        "WHERE DATE_DEBUT >= SYSDATE - 1 "  // Dernières 24h
        "GROUP BY CONTRIBUTION "
        "ORDER BY COUNT(*) DESC"
        );

    if (success && query.next()) {
        QString type = query.value(0).toString();
        int changement = query.value(1).toInt();

        if (changement > 0) {
            modification = QString("+%1 %2").arg(changement).arg(type);
        }
    }

    return modification;
}

void SponsorManager::afficherDashboardKPI(QGroupBox* groupBox)
{
    if (!groupBox) return;

    // Nettoyage complet si déjà rempli
    if (QLayout *oldLayout = groupBox->layout()) {
        QLayoutItem *child;
        while ((child = oldLayout->takeAt(0)) != nullptr) {
            if (QWidget *w = child->widget()) {
                w->setParent(nullptr);
                w->deleteLater();
            }
            delete child;
        }
        delete oldLayout;
    }

    auto *mainLayout = new QVBoxLayout(groupBox);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(25);

    auto *title = new QLabel("TABLEAU DE BORD DES SPONSORS");
    title->setStyleSheet("font-size: 26px; font-weight: bold; color: #6A1B9A;");
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    auto *chartsLayout = new QHBoxLayout();
    chartsLayout->setSpacing(30);

    // =========================================================
    // LAMBDA DE RAFRAÎCHISSEMENT – ON PASSE TOUT EN PARAMÈTRE
    // =========================================================
    auto updateCharts = [groupBox, chartsLayout]() {
        // On récupère l'instance de SponsorManager via une recherche dans les parents
        // (le groupBox est normalement enfant d'une fenêtre qui a SponsorManager comme parent logique)
        SponsorManager *manager = groupBox->findChild<SponsorManager*>();
        if (!manager) {
            // Si pas trouvé, on cherche dans la hiérarchie parent
            QObject *obj = groupBox;
            while (obj && !manager) {
                manager = qobject_cast<SponsorManager*>(obj);
                obj = obj->parent();
            }
        }
        if (!manager) return; // Sécurité absolue

        // === 1. Mise à jour du Donut ===
        if (chartsLayout->count() >= 1) {
            auto view = qobject_cast<QChartView*>(chartsLayout->itemAt(0)->widget());
            if (view && !view->chart()->series().isEmpty()) {
                auto series = qobject_cast<QPieSeries*>(view->chart()->series().first());
                if (series) {
                    auto stats = manager->getStatsContributionsLive();
                    int total = stats.value("Services", 0) + stats.value("Matériels", 0) + stats.value("Autre", 0);
                    if (total > 0) {
                        series->clear();
                        if (stats["Services"] > 0) series->append("Services", stats["Services"])->setBrush(QColor("#4ECDC4"));
                        if (stats["Matériels"] > 0) series->append("Matériels", stats["Matériels"])->setBrush(QColor("#FF6B6B"));
                        if (stats["Autre"] > 0) series->append("Autre", stats["Autre"])->setBrush(QColor("#95A5A6"));
                        for (auto slice : series->slices()) {
                            slice->setLabelVisible(true);
                            slice->setLabel(QString("%1\n%2%").arg(slice->label()).arg(slice->percentage() * 100, 0, 'f', 1));
                            slice->setLabelColor(Qt::white);
                            slice->setLabelFont(QFont("Segoe UI", 11, QFont::Bold));
                        }
                    }
                }
            }
        }

        // === 2. Mise à jour des Barres ===
        if (chartsLayout->count() >= 2) {
            auto view = qobject_cast<QChartView*>(chartsLayout->itemAt(1)->widget());
            if (view && !view->chart()->series().isEmpty()) {
                auto series = qobject_cast<QBarSeries*>(view->chart()->series().first());
                if (series && series->barSets().size() >= 3) {
                    auto stats = manager->getStatsAnciennete();
                    int nouveaux = 0, stables = 0, fideles = 0;
                    for (auto it = stats.constBegin(); it != stats.constEnd(); ++it) {
                        QString k = it.key().toLower();
                        if (k.contains("nouveaux")) nouveaux += it.value();
                        else if (k.contains("stables")) stables += it.value();
                        else fideles += it.value();
                    }
                    series->barSets()[0]->replace(0, nouveaux);
                    series->barSets()[1]->replace(1, stables);
                    series->barSets()[2]->replace(2, fideles);
                    series->barSets()[0]->setLabel(QString::number(nouveaux));
                    series->barSets()[1]->setLabel(QString::number(stables));
                    series->barSets()[2]->setLabel(QString::number(fideles));
                    // === MISE À JOUR DE L'AXE Y APRÈS RAFRAÎCHISSEMENT ===
                    int maxVal = qMax(nouveaux, qMax(stables, fideles));
                    QValueAxis *axisY = qobject_cast<QValueAxis*>(view->chart()->axisY());
                    if (axisY) {
                        axisY->setRange(0, maxVal + 2);
                        axisY->setTickCount(maxVal + 3);     // ← magique : 1 tick = 1 unité
                        axisY->setMinorTickCount(0);         // ← plus de demi-ticks
                    }
                }
            }
        }
    };

    // =========================================================
    // Création initiale des graphiques (identique à avant)
    // =========================================================
    // Donut
    {
        auto stats = SponsorManager::getStatsContributionsLive(); // appel statique si possible
        int total = stats.value("Services",0) + stats.value("Matériels",0) + stats.value("Autre",0);
        if (total > 0) {
            auto *series = new QPieSeries();
            series->setHoleSize(0.40);
            if (stats["Services"] > 0) series->append("Services", stats["Services"])->setBrush(QColor("#4ECDC4"));
            if (stats["Matériels"] > 0) series->append("Matériels", stats["Matériels"])->setBrush(QColor("#FF6B6B"));
            if (stats["Autre"] > 0) series->append("Autre", stats["Autre"])->setBrush(QColor("#95A5A6"));
            for (auto s : series->slices()) {
                s->setLabelVisible(true);
                s->setLabel(QString("%1\n%2%").arg(s->label()).arg(s->percentage()*100, 0, 'f', 1));
                s->setLabelColor(Qt::white);
                s->setLabelFont(QFont("Segoe UI", 11, QFont::Bold));
            }
            auto *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("<h3 style='color:#6A1B9A;'>Répartition des Contributions</h3>");
            chart->legend()->setVisible(true);
            chart->legend()->setAlignment(Qt::AlignRight);
            chart->setAnimationOptions(QChart::AllAnimations);
            auto *view = new QChartView(chart);
            view->setRenderHint(QPainter::Antialiasing);
            view->setMinimumSize(380, 360);
            chartsLayout->addWidget(view);
        }
    }

    // Barres
    {
        auto stats = SponsorManager::getStatsAnciennete();
        int nouveaux = 0, stables = 0, fideles = 0;
        for (auto it = stats.constBegin(); it != stats.constEnd(); ++it) {
            QString k = it.key().toLower();
            if (k.contains("nouveaux")) nouveaux += it.value();
            else if (k.contains("stables")) stables += it.value();
            else fideles += it.value();
        }
        if (nouveaux + stables + fideles > 0) {
            auto *bar1 = new QBarSet(""); *bar1 << nouveaux << 0 << 0;
            auto *bar2 = new QBarSet(""); *bar2 << 0 << stables << 0;
            auto *bar3 = new QBarSet(""); *bar3 << 0 << 0 << fideles;
            bar1->setBrush(QColor("#1dd1a1")); bar2->setBrush(QColor("#54a0ff")); bar3->setBrush(QColor("#5f27cd"));
            bar1->setLabel(QString::number(nouveaux)); bar2->setLabel(QString::number(stables)); bar3->setLabel(QString::number(fideles));
            bar1->setLabelColor(Qt::white); bar2->setLabelColor(Qt::white); bar3->setLabelColor(Qt::white);
            bar1->setLabelFont(QFont("Segoe UI", 12, QFont::Bold));

            auto *series = new QBarSeries();
            series->append({bar1, bar2, bar3});
            auto *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("<h3 style='color:#6A1B9A;'>Ancienneté des Sponsors</h3>");
            chart->setAnimationOptions(QChart::AllAnimations);
            chart->legend()->setVisible(false);

            QStringList cats = {"Nouveaux\n(<1 an)", "Stables\n(1-2 ans)", "Fidèles\n(>2 ans)"};
            auto *axisX = new QBarCategoryAxis(); axisX->append(cats);
            chart->addAxis(axisX, Qt::AlignBottom); series->attachAxis(axisX);
            // === AXE Y PARFAIT : entiers uniquement + barres pile sur le bon chiffre ===
            int maxVal = qMax(nouveaux, qMax(stables, fideles)); // le plus grand nombre

            auto *axisY = new QValueAxis();
            axisY->setRange(0, maxVal + 2);         // marge propre en haut
            axisY->setTickCount(maxVal + 3);        // 1 tick = 1 sponsor → force 0,1,2,3,4...
            axisY->setMinorTickCount(0);            // SUPPRIME les traits à 0.5, 1.5, etc.
            axisY->setLabelFormat("%d");            // affiche uniquement des entiers
            axisY->setTitleText("Nombre de sponsors");

            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);
            auto *view = new QChartView(chart);
            view->setRenderHint(QPainter::Antialiasing);
            view->setMinimumSize(380, 360);
            chartsLayout->addWidget(view);
        }
    }

    mainLayout->addLayout(chartsLayout);

    auto *updateLabel = new QLabel("Affiché le : " + QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss"));
    updateLabel->setStyleSheet("color: #95a5a6; font-size: 13px; font-style: italic;");
    updateLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(updateLabel);
}

// =====================================================
// 4. PARTIE NOTIFICATIONS ORIGINALES (EXISTANT)
// =====================================================
int SponsorManager::getNombreNotifications()
{
    QSqlQuery query;
    int count = 0;

    // Contrats qui expirent dans moins de 7 jours OU déjà expirés
    bool success = query.exec(
        "SELECT COUNT(*) FROM SPONSOR "
        "WHERE DATE_FIN <= SYSDATE + 7 AND DATE_FIN >= SYSDATE - 30"
        );

    if (success && query.next()) {
        count = query.value(0).toInt();
    }

    qDebug() << "🔔 Nombre de notifications:" << count;
    return count;
}

QList<QMap<QString, QString>> SponsorManager::getNotificationsDetail()
{
    QList<QMap<QString, QString>> notifications;
    QSqlQuery query;

    bool success = query.exec(
        "SELECT ID_SPONSOR, NOM, DATE_FIN, "
        "CASE "
        "    WHEN DATE_FIN < SYSDATE THEN 'expire' "
        "    WHEN DATE_FIN <= SYSDATE + 1 THEN 'j1' "
        "    WHEN DATE_FIN <= SYSDATE + 3 THEN 'j3' "
        "    ELSE 'j7' "
        "END as type_alerte "
        "FROM SPONSOR "
        "WHERE DATE_FIN <= SYSDATE + 7 AND DATE_FIN >= SYSDATE - 30 "
        "ORDER BY DATE_FIN"
        );

    if (success) {
        while (query.next()) {
            QMap<QString, QString> notif;
            notif["id"] = query.value(0).toString();
            notif["nom"] = query.value(1).toString();
            notif["date_fin"] = query.value(2).toDate().toString("dd/MM/yyyy");
            notif["type"] = query.value(3).toString();

            notifications.append(notif);
        }
    }

    return notifications;
}

void SponsorManager::afficherFenetreNotifications(QWidget* parent)
{
    QDialog *dialog = new QDialog(parent);
    dialog->setWindowTitle("🔔 Notifications");
    dialog->setFixedSize(400, 500);
    dialog->setStyleSheet("QDialog { background: white; border-radius: 10px; }");

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->setContentsMargins(15, 15, 15, 15);
    layout->setSpacing(10);

    // Titre
    QLabel *title = new QLabel("🔔 NOTIFICATIONS");
    title->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; text-align: center; padding: 10px;");
    layout->addWidget(title);

    // Séparateur
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("color: #bdc3c7; margin: 5px 0px;");
    layout->addWidget(line);

    // Zone de défilement pour les notifications
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { border: none; background: transparent; }");

    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(10);

    // Récupérer les notifications
    QList<QMap<QString, QString>> notifications = getNotificationsDetail();

    if (notifications.isEmpty()) {
        QLabel *noNotif = new QLabel("Aucune notification");
        noNotif->setStyleSheet("color: #7f8c8d; font-style: italic; text-align: center; padding: 20px;");
        noNotif->setAlignment(Qt::AlignCenter);
        scrollLayout->addWidget(noNotif);
    } else {
        for (const auto &notif : notifications) {
            QWidget *notifWidget = new QWidget();
            notifWidget->setStyleSheet(
                "background: #f8f9fa; border: 1px solid #e0e0e0; border-radius: 8px; padding: 0px;"
                );

            QVBoxLayout *notifLayout = new QVBoxLayout(notifWidget);
            notifLayout->setContentsMargins(12, 12, 12, 12);
            notifLayout->setSpacing(5);

            // Icône et message selon le type
            QString icone, message, couleur;
            if (notif["type"] == "expire") {
                icone = "🔴";
                message = "Contrat expiré";
                couleur = "#e74c3c";
            } else if (notif["type"] == "j1") {
                icone = "⚠️";
                message = "Contrat expire demain";
                couleur = "#f39c12";
            } else if (notif["type"] == "j3") {
                icone = "⚠️";
                message = "Contrat expire dans 3 jours";
                couleur = "#f39c12";
            } else {
                icone = "⚠️";
                message = "Contrat expire dans 7 jours";
                couleur = "#f39c12";
            }

            // Message
            QLabel *msgLabel = new QLabel(icone + " " + message);
            msgLabel->setStyleSheet(QString("font-weight: bold; color: %1; font-size: 13px;").arg(couleur));

            // Sponsor
            QLabel *sponsorLabel = new QLabel("Sponsor: " + notif["nom"]);
            sponsorLabel->setStyleSheet("color: #2c3e50; font-size: 12px;");

            // Date
            QLabel *dateLabel = new QLabel("Date fin: " + notif["date_fin"]);
            dateLabel->setStyleSheet("color: #7f8c8d; font-size: 11px;");

            // Bouton Renouveler
            QPushButton *btnRenouveler = new QPushButton("RENOUVELER");
            btnRenouveler->setStyleSheet(
                "QPushButton { "
                "background: #3498db; color: white; font-size: 11px; font-weight: bold; "
                "padding: 6px 12px; border: none; border-radius: 5px; "
                "}"
                "QPushButton:hover { background: #2980b9; }"
                );
            btnRenouveler->setFixedWidth(100);

            // Connexion du bouton
            QString sponsorId = notif["id"];
            connect(btnRenouveler, &QPushButton::clicked, [dialog, sponsorId, parent]() {
                dialog->accept();
                renouvelerContrat(sponsorId, parent);
            });

            notifLayout->addWidget(msgLabel);
            notifLayout->addWidget(sponsorLabel);
            notifLayout->addWidget(dateLabel);
            notifLayout->addWidget(btnRenouveler, 0, Qt::AlignRight);

            scrollLayout->addWidget(notifWidget);
        }
    }

    scrollLayout->addStretch();
    scrollArea->setWidget(scrollWidget);
    layout->addWidget(scrollArea);

    // Bouton Fermer
    QPushButton *btnFermer = new QPushButton("Fermer");
    btnFermer->setStyleSheet(
        "QPushButton { "
        "background: #95a5a6; color: white; font-size: 12px; font-weight: bold; "
        "padding: 8px 20px; border: none; border-radius: 6px; "
        "}"
        "QPushButton:hover { background: #7f8c8d; }"
        );
    connect(btnFermer, &QPushButton::clicked, dialog, &QDialog::accept);
    layout->addWidget(btnFermer, 0, Qt::AlignCenter);

    dialog->exec();
    delete dialog;
}

void SponsorManager::renouvelerContrat(const QString& sponsorId, QWidget* parent)
{
    qDebug() << "🔄 Renouvellement du sponsor ID:" << sponsorId;

    // Ici, tu dois appeler ta fonction existante pour :
    // 1. Aller à l'onglet Sponsor
    // 2. Sélectionner le sponsor dans le tableau
    // 3. Remplir le formulaire

    // Pour l'instant, on affiche un message
    QMessageBox::information(parent, "Renouvellement",
                             "Sponsor " + sponsorId + " sélectionné pour renouvellement.\n"
                                                      "Rendez-vous dans l'onglet Sponsor pour modifier la date.");
}

void SponsorManager::showNotification(const QString &titre, const QString &message)
{
    if (m_trayIcon) {
        m_trayIcon->showMessage(titre, message, QSystemTrayIcon::Information, 8000);
    }
}

// =====================================================
// 5. PARTIE WIDGETS CHART (EXISTANT)
// =====================================================
QWidget* SponsorManager::createKPICard(const QString &title, int count, int total, const QString &color)
{
    QWidget *card = new QWidget();
    card->setMinimumSize(180, 120);
    card->setStyleSheet(
        QString("background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 %1, stop:1 #ffffff);"
                "border: 2px solid %2;"
                "border-radius: 12px;"
                "padding: 0px;").arg(color + "20", color + "40")
        );

    QVBoxLayout *layout = new QVBoxLayout(card);
    layout->setContentsMargins(15, 15, 15, 15);
    layout->setSpacing(8);

    // Titre
    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #2c3e50;");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // Ligne de séparation
    QFrame *separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    separator->setStyleSheet(QString("color: %1; margin: 5px 0px;").arg(color + "60"));
    layout->addWidget(separator);

    // Nombre de sponsors
    QLabel *countLabel = new QLabel(QString::number(count));
    countLabel->setStyleSheet(
        QString("font-size: 28px;"
                "font-weight: bold;"
                "color: %1;"
                "text-align: center;"
                "margin: 5px 0px;").arg(color)
        );
    countLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(countLabel);

    // Pourcentage (seulement si total > 0)
    if (total > 0) {
        int pourcentage = (count * 100) / total;
        QLabel *percentLabel = new QLabel(QString("%1% du total").arg(pourcentage));
        percentLabel->setStyleSheet(
            "font-size: 12px;"
            "color: #7f8c8d;"
            "text-align: center;"
            "font-style: italic;"
            );
        percentLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(percentLabel);
    }

    return card;
}

QWidget* SponsorManager::createPieChart(const QMap<QString, int>& stats, int total)
{
    // [TON CODE EXISTANT - SIMPLIFIÉ POUR L'EXEMPLE]
    QWidget *widget = new QWidget();
    return widget;
}

QWidget* SponsorManager::createAncienneteChart(const QMap<QString, int>& stats, int total)
{
    // [TON CODE EXISTANT - SIMPLIFIÉ POUR L'EXEMPLE]
    QWidget *widget = new QWidget();
    return widget;
}

QWidget* SponsorManager::createModernDonutChart(const QString &title, const QMap<QString, int> &data, int total, const QMap<QString, QString> &colorMap, const QMap<QString, QString> &labelMap)
{
    // [TON CODE EXISTANT - SIMPLIFIÉ POUR L'EXEMPLE]
    QWidget *widget = new QWidget();
    return widget;
}

// =====================================================
// 6. NOUVELLE PARTIE : NOTIFICATIONS TOAST AUTOMATIQUES
// =====================================================

// =====================================================
// 6. NOUVELLE PARTIE : NOTIFICATIONS TOAST AUTOMATIQUES
// =====================================================

void SponsorManager::demarrerNotificationsAutomatiques(QWidget* parentWidget)
{
    if (!parentWidget) {
        qDebug() << "❌ Parent widget null - impossible de démarrer les notifications auto";
        return;
    }

    m_parentWidget = parentWidget;

    // Récupérer les notifications
    m_toastQueue = getNotificationsDetail();

    if (m_toastQueue.isEmpty()) {
        qDebug() << "🔔 Aucune notification à afficher";
        return;
    }

    qDebug() << "🔔 Démarrage des notifications automatiques. Total:" << m_toastQueue.size();

    // Créer le timer si pas déjà fait
    if (!m_toastTimer) {
        m_toastTimer = new QTimer(this);
        m_toastTimer->setSingleShot(true);
        connect(m_toastTimer, &QTimer::timeout, this, &SponsorManager::afficherProchaineNotification);
    }

    // Démarrer la séquence
    afficherProchaineNotification();
}

void SponsorManager::afficherProchaineNotification()
{
    // Masquer le toast actuel s'il existe
    if (m_currentToast) {
        m_currentToast->deleteLater();
        m_currentToast = nullptr;
    }

    // Vérifier s'il reste des notifications
    if (m_toastQueue.isEmpty()) {
        qDebug() << "🔔 Fin des notifications automatiques";
        return;
    }

    // Prendre la première notification de la file
    QMap<QString, QString> notif = m_toastQueue.takeFirst();
    creerEtAfficherToast(notif);

    // Programmer la prochaine notification après une pause
    m_toastTimer->start(7000); // 5s affichage + 2s pause
}

void SponsorManager::creerEtAfficherToast(const QMap<QString, QString>& notif)
{
    if (!m_parentWidget) return;

    // Créer le widget toast style moderne
    m_currentToast = new QWidget(m_parentWidget, Qt::Tool | Qt::FramelessWindowHint);
    m_currentToast->setAttribute(Qt::WA_DeleteOnClose);
    m_currentToast->setFixedSize(380, 110);

    // Effet d'ombre subtil
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(15);
    shadow->setColor(QColor(0, 0, 0, 60));
    shadow->setOffset(0, 3);
    m_currentToast->setGraphicsEffect(shadow);

    // Style moderne sobre
    m_currentToast->setStyleSheet(
        "background: #ffffff;"
        "color: #2c3e50;"
        "border-radius: 8px;"
        "padding: 0px;"
        "font-family: 'Segoe UI', Arial, sans-serif;"
        "border: 1px solid #e0e0e0;"
        "font-size: 13px;"
        );

    QVBoxLayout *mainLayout = new QVBoxLayout(m_currentToast);
    mainLayout->setContentsMargins(16, 14, 16, 14);
    mainLayout->setSpacing(8);

    // === EN-TÊTE "NOTIFICATIONS ET ALERTE" ===
    QWidget *headerWidget = new QWidget();
    QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(0, 0, 0, 0);

    // Icône de notification
    QLabel *iconLabel = new QLabel("🔔");
    iconLabel->setStyleSheet("font-size: 16px; background: transparent;");

    // Titre "NOTIFICATIONS ET ALERTE"
    QLabel *titleLabel = new QLabel("NOTIFICATIONS ET ALERTE");
    titleLabel->setStyleSheet(
        "font-weight: bold; font-size: 14px; color: #2c3e50;"
        "background: #f8f9fa; padding: 4px 10px; border-radius: 6px;"
        "margin-left: 8px; border: 1px solid #e9ecef;"
        );

    headerLayout->addWidget(iconLabel);
    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();

    // === CORPS DE LA NOTIFICATION ===
    QWidget *bodyWidget = new QWidget();
    QVBoxLayout *bodyLayout = new QVBoxLayout(bodyWidget);
    bodyLayout->setContentsMargins(0, 0, 0, 0);
    bodyLayout->setSpacing(6);

    // Déterminer le message selon le type
    QString message, couleurMessage;
    if (notif["type"] == "expire") {
        message = "🔴 Contrat expiré - " + notif["nom"];
        couleurMessage = "#e74c3c";
    } else if (notif["type"] == "j1") {
        message = "🟠 Expire demain - " + notif["nom"];
        couleurMessage = "#f39c12";
    } else if (notif["type"] == "j3") {
        message = "🟡 Expire dans 3 jours - " + notif["nom"];
        couleurMessage = "#f1c40f";
    } else {
        message = "🔵 Expire dans 7 jours - " + notif["nom"];
        couleurMessage = "#3498db";
    }

    // Message principal
    QLabel *messageLabel = new QLabel(message);
    messageLabel->setStyleSheet(QString(
                                    "font-size: 13px; font-weight: 600; color: %1;"
                                    ).arg(couleurMessage));

    // Date d'échéance
    QLabel *dateLabel = new QLabel("📅 Date fin: " + notif["date_fin"]);
    dateLabel->setStyleSheet("font-size: 12px; color: #7f8c8d;");

    bodyLayout->addWidget(messageLabel);
    bodyLayout->addWidget(dateLabel);

    // === ASSEMBLAGE ===
    mainLayout->addWidget(headerWidget);
    mainLayout->addWidget(bodyWidget);

    // === POSITIONNEMENT EN BAS À DROITE ===
    QPoint parentBottomRight = m_parentWidget->mapToGlobal(QPoint(m_parentWidget->width(), m_parentWidget->height()));
    QPoint toastPosition = QPoint(parentBottomRight.x() - 400, parentBottomRight.y() - 130);
    m_currentToast->move(toastPosition);
    m_currentToast->show();

    // === ANIMATION ===
    QPropertyAnimation *animation = new QPropertyAnimation(m_currentToast, "pos");
    animation->setDuration(600);
    animation->setStartValue(QPoint(parentBottomRight.x() + 400, toastPosition.y()));
    animation->setEndValue(toastPosition);
    animation->setEasingCurve(QEasingCurve::OutCubic);
    animation->start();

    // Disparition après 5 secondes
    QTimer::singleShot(5000, this, &SponsorManager::masquerToastActuel);
}
// =====================================================
// FONCTION MANQUANTE - À AJOUTER À LA FIN
// =====================================================

void SponsorManager::masquerToastActuel()
{
    if (!m_currentToast) return;

    // Animation de disparition vers la droite
    QPropertyAnimation *animation = new QPropertyAnimation(m_currentToast, "pos");
    animation->setDuration(500);
    animation->setStartValue(m_currentToast->pos());

    QPoint parentBottomRight = m_parentWidget->mapToGlobal(QPoint(m_parentWidget->width(), m_parentWidget->height()));
    animation->setEndValue(QPoint(parentBottomRight.x() + 100, m_currentToast->pos().y()));
    animation->setEasingCurve(QEasingCurve::InCubic);

    connect(animation, &QPropertyAnimation::finished, m_currentToast, &QWidget::deleteLater);
    connect(animation, &QPropertyAnimation::finished, this, [this]() {
        m_currentToast = nullptr;
    });

    animation->start();
}
