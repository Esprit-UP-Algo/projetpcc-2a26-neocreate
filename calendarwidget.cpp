/*#include "CalendarWidget.h"
#include <QApplication>
#include <QDate>
#include <QTime>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDrag>
#include <QMimeData>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QScrollBar>
#include <QProgressDialog>
#include <QInputDialog>
#include <QHeaderView>
#include <QDebug>

CalendarWidget::CalendarWidget(QWidget *parent) : QWidget(parent),
    m_mainCalendarWidget(nullptr),
    m_detailsGroupBox(nullptr),
    m_groupBox5(nullptr),
    m_currentYear(QDate::currentDate().year()),
    m_currentMonth(QDate::currentDate().month())
{
    setupUI();
    setupConnections();
    setupAIFeatures();
    setupNotifications();

    refreshCalendar();
}

CalendarWidget::~CalendarWidget()
{
    if (m_deadlineTimer) {
        m_deadlineTimer->stop();
        delete m_deadlineTimer;
    }
}

void CalendarWidget::connectToCalendarWidget(QCalendarWidget *calendarWidget)
{
    if (m_mainCalendarWidget) {
        disconnect(m_mainCalendarWidget, &QCalendarWidget::selectionChanged,
                   this, &CalendarWidget::onCalendarDateSelected);
    }

    m_mainCalendarWidget = calendarWidget;
    if (m_mainCalendarWidget) {
        connect(m_mainCalendarWidget, &QCalendarWidget::selectionChanged,
                this, &CalendarWidget::onCalendarDateSelected);

        // Style d'origine pour le calendrier
        m_mainCalendarWidget->setStyleSheet(""); // Remettre le style par défaut

        qDebug() << "Calendrier principal connecté avec succès";
    }
}

void CalendarWidget::connectToDetailsGroupBox(QGroupBox *detailsGroupBox)
{
    m_detailsGroupBox = detailsGroupBox;
    if (m_detailsGroupBox) {
        // NE PAS changer le style - garder l'apparence d'origine
        m_detailsGroupBox->setStyleSheet(""); // Style par défaut
        qDebug() << "GroupBox détails connecté avec succès";
    }
}

void CalendarWidget::connectToGroupBox5(QGroupBox *groupBox_5)
{
    m_groupBox5 = groupBox_5;
    if (m_groupBox5) {
        // NE PAS changer le style - garder l'apparence d'origine
        m_groupBox5->setStyleSheet(""); // Style par défaut
        qDebug() << "GroupBox_5 connecté avec succès";
    }
}

void CalendarWidget::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(5, 5, 5, 5);
    mainLayout->setSpacing(5);

    // Header avec contrôles
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(3);

    // Sélecteur de vue
    m_viewModeCombo = new QComboBox();
    m_viewModeCombo->addItem("Mois");
    m_viewModeCombo->addItem("Semaine");
    m_viewModeCombo->addItem("Jour");
    m_viewModeCombo->setMaximumWidth(80);
    headerLayout->addWidget(new QLabel("Vue:"));
    headerLayout->addWidget(m_viewModeCombo);

    // Filtres
    m_filterCombo = new QComboBox();
    m_filterCombo->addItem("Tous");
    m_filterCombo->addItem("Staff");
    m_filterCombo->addItem("Client");
    m_filterCombo->addItem("Matériel");
    m_filterCombo->addItem("Projet");
    m_filterCombo->addItem("Sponsor");
    m_filterCombo->addItem("Createur");
    m_filterCombo->setMaximumWidth(80);
    headerLayout->addWidget(new QLabel("Filtre:"));
    headerLayout->addWidget(m_filterCombo);

    // Navigation mois/année
    m_monthCombo = new QComboBox();
    for (int i = 1; i <= 12; i++) {
        m_monthCombo->addItem(QLocale().monthName(i).left(3));
    }
    m_monthCombo->setMaximumWidth(70);
    m_monthCombo->setCurrentIndex(m_currentMonth - 1);

    m_yearCombo = new QComboBox();
    for (int i = m_currentYear - 1; i <= m_currentYear + 1; i++) {
        m_yearCombo->addItem(QString::number(i));
    }
    m_yearCombo->setMaximumWidth(60);
    m_yearCombo->setCurrentText(QString::number(m_currentYear));

    headerLayout->addWidget(new QLabel("Mois:"));
    headerLayout->addWidget(m_monthCombo);
    headerLayout->addWidget(new QLabel("Année:"));
    headerLayout->addWidget(m_yearCombo);

    headerLayout->addStretch();

    // Boutons IA
    m_aiGenerateButton = new QPushButton("🤖");
    m_aiGenerateButton->setToolTip("Générer Idées IA");
    m_aiGenerateButton->setMaximumWidth(40);

    m_aiAnalyzeButton = new QPushButton("⏱️");
    m_aiAnalyzeButton->setToolTip("Temps Optimal IA");
    m_aiAnalyzeButton->setMaximumWidth(40);

    m_aiScheduleButton = new QPushButton("📅");
    m_aiScheduleButton->setToolTip("Planif. Auto IA");
    m_aiScheduleButton->setMaximumWidth(40);

    m_aiRescheduleButton = new QPushButton("🔄");
    m_aiRescheduleButton->setToolTip("Réorg. Intelligente");
    m_aiRescheduleButton->setMaximumWidth(40);

    m_aiAnalyticsButton = new QPushButton("📊");
    m_aiAnalyticsButton->setToolTip("Analytics IA");
    m_aiAnalyticsButton->setMaximumWidth(40);

    headerLayout->addWidget(m_aiGenerateButton);
    headerLayout->addWidget(m_aiAnalyzeButton);
    headerLayout->addWidget(m_aiScheduleButton);
    headerLayout->addWidget(m_aiRescheduleButton);
    headerLayout->addWidget(m_aiAnalyticsButton);

    mainLayout->addLayout(headerLayout);

    // Liste des événements
    m_eventsList = new QListWidget();
    // Style simple pour la liste
    m_eventsList->setMaximumHeight(150);
    m_eventsList->setAlternatingRowColors(true);

    mainLayout->addWidget(m_eventsList);

    // Boutons d'action
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    m_addButton = new QPushButton("➕ Ajouter Événement");
    m_editButton = new QPushButton("✏️ Modifier");
    m_deleteButton = new QPushButton("🗑️ Supprimer");

    // Styles simples pour les boutons
    m_addButton->setStyleSheet("");
    m_editButton->setStyleSheet("");
    m_deleteButton->setStyleSheet("");

    buttonLayout->addWidget(m_addButton);
    buttonLayout->addWidget(m_editButton);
    buttonLayout->addWidget(m_deleteButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);

    this->setMaximumSize(600, 400);
    this->setMinimumSize(400, 300);
}

void CalendarWidget::setupAIFeatures()
{
    // Styles simples pour les boutons IA
    m_aiGenerateButton->setStyleSheet("");
    m_aiAnalyzeButton->setStyleSheet("");
    m_aiScheduleButton->setStyleSheet("");
    m_aiRescheduleButton->setStyleSheet("");
    m_aiAnalyticsButton->setStyleSheet("");
}

void CalendarWidget::setupConnections()
{
    connect(m_viewModeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CalendarWidget::onViewModeChanged);
    connect(m_filterCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CalendarWidget::onFilterChanged);
    connect(m_monthCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CalendarWidget::onMonthChanged);
    connect(m_yearCombo, QOverload<const QString &>::of(&QComboBox::currentTextChanged), this, &CalendarWidget::onMonthChanged);

    connect(m_addButton, &QPushButton::clicked, this, &CalendarWidget::onAddEvent);
    connect(m_editButton, &QPushButton::clicked, this, &CalendarWidget::onEditEvent);
    connect(m_deleteButton, &QPushButton::clicked, this, &CalendarWidget::onDeleteEvent);

    // Connexions IA
    connect(m_aiGenerateButton, &QPushButton::clicked, this, &CalendarWidget::onGenerateAIContent);
    connect(m_aiAnalyzeButton, &QPushButton::clicked, this, &CalendarWidget::onAnalyzeOptimalTime);
    connect(m_aiScheduleButton, &QPushButton::clicked, this, &CalendarWidget::onAutoSchedule);
    connect(m_aiRescheduleButton, &QPushButton::clicked, this, &CalendarWidget::onSmartReschedule);
    connect(m_aiAnalyticsButton, &QPushButton::clicked, this, &CalendarWidget::showAIAnalytics);

    connect(m_eventsList, &QListWidget::itemDoubleClicked, this, [this](QListWidgetItem *item){
        QString eventText = item->text();
        QMessageBox::information(this, "Détails Événement",
                                 QString("📅 **Événement complet:**\n\n%1").arg(eventText));
    });
}

// ===================================================
// FONCTIONS PRINCIPALES
// ===================================================

void CalendarWidget::onCalendarDateSelected()
{
    if (!m_mainCalendarWidget) return;

    QDate selectedDate = m_mainCalendarWidget->selectedDate();
    qDebug() << "Date sélectionnée:" << selectedDate.toString("dd/MM/yyyy");

    // Mettre à jour groupBox_5 seulement
    if (m_groupBox5) {
        updateGroupBox5Content(selectedDate);
    }
}

void CalendarWidget::updateCalendarDetails(const QDate &date)
{
    // Fonction conservée pour la compatibilité
    if (m_detailsGroupBox) {
        // Votre code d'origine pour detailsGroupBox
        QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(m_detailsGroupBox->layout());
        if (!layout) {
            layout = new QVBoxLayout(m_detailsGroupBox);
            m_detailsGroupBox->setLayout(layout);
        }

        while (QLayoutItem* item = layout->takeAt(0)) {
            if (QWidget* widget = item->widget()) {
                widget->hide();
                widget->deleteLater();
            }
            delete item;
        }

        QLabel *dateLabel = new QLabel(date.toString("dddd d MMMM yyyy"));
        dateLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(dateLabel);

        QTextEdit *detailsText = new QTextEdit();
        detailsText->setReadOnly(true);
        QString intelligentReport = generateDayReport(date);
        detailsText->setPlainText(intelligentReport);
        layout->addWidget(detailsText);
    }
}

// ===================================================
// FONCTIONS POUR GROUPBOX_5 (apparence originale)
// ===================================================

void CalendarWidget::updateGroupBox5Content(const QDate &date)
{
    if (!m_groupBox5) {
        qDebug() << "ERREUR: m_groupBox5 est null!";
        return;
    }

    qDebug() << "Mise à jour groupBox_5 pour:" << date.toString("dd/MM/yyyy");

    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(m_groupBox5->layout());
    if (!layout) {
        layout = new QVBoxLayout(m_groupBox5);
        m_groupBox5->setLayout(layout);
    }

    // Nettoyer le layout existant
    while (QLayoutItem* item = layout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->hide();
            widget->deleteLater();
        }
        delete item;
    }

    // 1. Titre avec la date (style original)
    QLabel *titleLabel = new QLabel(date.toString("dddd d MMMM yyyy"));
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // 2. Liste du travail du jour
    QListWidget *workList = new QListWidget();
    workList->setObjectName("listWidget");

    // Remplir la liste
    populateWorkList(workList, date);
    layout->addWidget(workList);

    // 3. Rapport IA (comme dans l'original)
    QTextEdit *reportText = new QTextEdit();
    reportText->setReadOnly(true);
    QString intelligentReport = generateDayReport(date);
    reportText->setPlainText(intelligentReport);
    layout->addWidget(reportText);

    // 4. Alertes IA (comme dans l'original)
    QLabel *alertsLabel = new QLabel("ALERTES INTELLIGENTES");
    layout->addWidget(alertsLabel);

    QTextEdit *alertsText = new QTextEdit();
    alertsText->setReadOnly(true);
    QString alertsContent = generateAIAlerts(date);
    alertsText->setPlainText(alertsContent);
    layout->addWidget(alertsText);

    qDebug() << "GroupBox_5 mis à jour pour:" << date.toString("dd/MM/yyyy");
}

void CalendarWidget::populateWorkList(QListWidget *list, const QDate &date)
{
    // Récupérer les événements du jour
    QList<QString> events = getEventsForDate(date);
    QList<QString> tasks = getTasksForDate(date);
    QList<QString> meetings = getMeetingsForDate(date);

    list->clear();

    // Ajouter les événements
    for (const QString &event : events) {
        QListWidgetItem *item = new QListWidgetItem("🎯 " + event);
        item->setData(Qt::UserRole, "event");
        list->addItem(item);
    }

    // Ajouter les tâches
    for (const QString &task : tasks) {
        QListWidgetItem *item = new QListWidgetItem("✅ " + task);
        item->setData(Qt::UserRole, "task");
        list->addItem(item);
    }

    // Ajouter les réunions
    for (const QString &meeting : meetings) {
        QListWidgetItem *item = new QListWidgetItem("👥 " + meeting);
        item->setData(Qt::UserRole, "meeting");
        list->addItem(item);
    }

    // Si pas de données, afficher un message
    if (list->count() == 0) {
        QListWidgetItem *item = new QListWidgetItem("Aucun travail planifié pour cette date");
        list->addItem(item);
    }

    // Connecter le double-clic
    connect(list, &QListWidget::itemDoubleClicked, this, &CalendarWidget::onWorkItemDoubleClicked);
}

void CalendarWidget::onWorkItemDoubleClicked(QListWidgetItem *item)
{
    QString itemType = item->data(Qt::UserRole).toString();
    QString itemText = item->text().mid(2);

    if (itemType == "event") {
        QMessageBox::information(this, "Détails Événement", "Événement: " + itemText);
    } else if (itemType == "task") {
        QMessageBox::information(this, "Détails Tâche", "Tâche: " + itemText);
    } else if (itemType == "meeting") {
        QMessageBox::information(this, "Détails Réunion", "Réunion: " + itemText);
    } else {
        QMessageBox::information(this, "Information", itemText);
    }
}

QString CalendarWidget::generateWorkSummary(const QDate &date)
{
    QMap<QString, int> stats;
    stats["events"] = getEventsForDate(date).size();
    stats["tasks"] = getTasksForDate(date).size();
    stats["meetings"] = getMeetingsForDate(date).size();

    QString summary;
    summary += QString("Événements: %1\n").arg(stats["events"]);
    summary += QString("Tâches: %1\n").arg(stats["tasks"]);
    summary += QString("Réunions: %1\n").arg(stats["meetings"]);

    return summary;
}

// ===================================================
// FONCTIONS EXISTANTES (inchangées)
// ===================================================

void CalendarWidget::refreshCalendar()
{
    loadDataForMonth(m_currentYear, m_currentMonth);
    refreshEventsList();
}

void CalendarWidget::loadDataForMonth(int year, int month)
{
    m_allEvents.clear();
    for (int day = 1; day <= QDate(year, month, 1).daysInMonth(); day++) {
        QDate currentDate(year, month, day);
        QList<QString> dayEvents = getEventsForDate(currentDate);
        for (const QString &event : dayEvents) {
            QVariantMap eventMap;
            eventMap["title"] = event;
            eventMap["date"] = currentDate;
            m_allEvents.append(eventMap);
        }
    }
}

void CalendarWidget::refreshEventsList()
{
    m_eventsList->clear();
    for (int i = 0; i < 5; i++) {
        QDate eventDate = QDate::currentDate().addDays(i);
        QString eventText = QString("📅 %1 - Événement exemple %2 [Staff] 👤 Responsable 🔵 Planifié")
                                .arg(eventDate.toString("dd/MM/yyyy"))
                                .arg(i+1);
        QListWidgetItem *item = new QListWidgetItem(eventText);
        item->setData(Qt::UserRole, eventDate);
        m_eventsList->addItem(item);
    }
}

void CalendarWidget::setupNotifications()
{
    m_deadlineTimer = new QTimer(this);
    connect(m_deadlineTimer, &QTimer::timeout, this, &CalendarWidget::checkDeadlines);
    m_deadlineTimer->start(60000);
}

void CalendarWidget::checkDeadlines()
{
    qDebug() << "Vérification IA des deadlines...";
}

// ===================================================
// FONCTIONS DE RÉCUPÉRATION DES DONNÉES (inchangées)
// ===================================================

QList<QString> CalendarWidget::getTasksForDate(const QDate &date)
{
    QList<QString> tasks;
    QSqlQuery query;
    query.prepare("SELECT DESCRIPTION, PRIORITE FROM TACHES WHERE DATE_ECHEANCE = :date");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    if (query.exec()) {
        while (query.next()) {
            tasks.append(QString("%1 [%2]").arg(query.value(0).toString()).arg(query.value(1).toString()));
        }
    }
    return tasks;
}

QList<QString> CalendarWidget::getEventsForDate(const QDate &date)
{
    QList<QString> events;
    QSqlQuery query;
    query.prepare("SELECT NOM_EVENEMENT, TYPE, HEURE_DEBUT, HEURE_FIN FROM EVENEMENTS WHERE DATE_EVENEMENT = :date");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    if (query.exec()) {
        while (query.next()) {
            QString event = QString("%1 (%2) %3-%4")
            .arg(query.value(0).toString())
                .arg(query.value(1).toString())
                .arg(query.value(2).toString())
                .arg(query.value(3).toString());
            events.append(event);
        }
    }
    return events;
}

QList<QString> CalendarWidget::getMeetingsForDate(const QDate &date)
{
    QList<QString> meetings;
    QSqlQuery query;
    query.prepare("SELECT NOM_EVENEMENT, LIEU, HEURE_DEBUT FROM EVENEMENTS WHERE DATE_EVENEMENT = :date AND TYPE LIKE '%Réunion%'");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    if (query.exec()) {
        while (query.next()) {
            meetings.append(QString("%1 - %2 (%3)")
                                .arg(query.value(0).toString())
                                .arg(query.value(1).toString())
                                .arg(query.value(2).toString()));
        }
    }
    return meetings;
}

// ... (les autres fonctions get... restent inchangées)

// ===================================================
// FONCTIONS IA (inchangées)
// ===================================================

void CalendarWidget::onGenerateAIContent() { QMessageBox::information(this, "Génération IA", "Fonction de génération de contenu IA"); }
void CalendarWidget::onAnalyzeOptimalTime() { QMessageBox::information(this, "Analyse IA", "Fonction d'analyse du temps optimal"); }
void CalendarWidget::onAutoSchedule() { QMessageBox::information(this, "Planification IA", "Fonction de planification automatique"); }
void CalendarWidget::onSmartReschedule() { QMessageBox::information(this, "Réorganisation IA", "Fonction de réorganisation intelligente"); }
void CalendarWidget::showAIAnalytics() { QMessageBox::information(this, "Analytics IA", "Fonction d'analytics intelligents"); }

// ===================================================
// AUTRES FONCTIONS (inchangées)
// ===================================================

void CalendarWidget::onViewModeChanged(int index) { Q_UNUSED(index); refreshCalendar(); }
void CalendarWidget::onFilterChanged(int index) { Q_UNUSED(index); refreshEventsList(); }
void CalendarWidget::onMonthChanged() { m_currentMonth = m_monthCombo->currentIndex() + 1; m_currentYear = m_yearCombo->currentText().toInt(); refreshCalendar(); }
void CalendarWidget::onAddEvent() { QMessageBox::information(this, "Ajouter", "Fonction d'ajout d'événement"); }
void CalendarWidget::onEditEvent() { QMessageBox::information(this, "Modifier", "Fonction de modification d'événement"); }
void CalendarWidget::onDeleteEvent() { QMessageBox::information(this, "Supprimer", "Fonction de suppression d'événement"); }

QString CalendarWidget::generateDayReport(const QDate &date)
{
    return "RAPPORT INTELLIGENT - " + date.toString("dd/MM/yyyy") + "\n\n" +
           "SUGGESTIONS INTELLIGENTES:\n" +
           generateIntelligentSuggestions(date);
}

QString CalendarWidget::generateAIAlerts(const QDate &date)
{
    Q_UNUSED(date);
    return "Aucune alerte - journée bien planifiée";
}

QString CalendarWidget::generateIntelligentSuggestions(const QDate &date)
{
    QList<QString> events = getEventsForDate(date);
    if (events.isEmpty()) {
        return "- Journée libre - Idéal pour planifier de nouveaux projets";
    }
    return "- Planning équilibré - Aucune suggestion particulière";
}

// ... (les autres fonctions restent inchangées)
*/
