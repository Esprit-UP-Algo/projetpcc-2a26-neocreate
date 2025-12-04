/*#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include <QCalendarWidget>
#include <QGroupBox>
#include <QListWidget>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QTimer>
#include <QSqlQuery>
#include <QMap>

class CalendarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalendarWidget(QWidget *parent = nullptr);
    ~CalendarWidget();

    void connectToCalendarWidget(QCalendarWidget *calendarWidget);
    void connectToDetailsGroupBox(QGroupBox *detailsGroupBox);
    void connectToGroupBox5(QGroupBox *groupBox_5);

private slots:
    void onCalendarDateSelected();
    void onViewModeChanged(int index);
    void onFilterChanged(int index);
    void onMonthChanged();
    void onAddEvent();
    void onEditEvent();
    void onDeleteEvent();

    // Fonctions IA
    void onGenerateAIContent();
    void onAnalyzeOptimalTime();
    void onAutoSchedule();
    void onSmartReschedule();
    void showAIAnalytics();
    void checkDeadlines();

private:
    void setupUI();
    void setupConnections();
    void setupAIFeatures();
    void setupNotifications();
    void refreshCalendar();
    void loadDataForMonth(int year, int month);
    void refreshEventsList();

    // Fonctions pour groupBox_5
    void updateGroupBox5Content(const QDate &date);
    void populateWorkList(QListWidget *list, const QDate &date);
    void onWorkItemDoubleClicked(QListWidgetItem *item);
    QString generateWorkSummary(const QDate &date);

    // Fonctions existantes
    void updateCalendarDetails(const QDate &date);
    QString generateDayReport(const QDate &date);
    QString generateAIAlerts(const QDate &date);
    QList<QString> detectSchedulingConflicts(const QDate &date);
    QString generateIntelligentSuggestions(const QDate &date);
    QList<QString> predictPotentialDelays();
    QMap<QString, int> analyzeResourceUsage(const QDate &date);

    // Récupération des données
    QList<QString> getTasksForDate(const QDate &date);
    QList<QString> getEventsForDate(const QDate &date);
    QList<QString> getMeetingsForDate(const QDate &date);
    QList<QString> getProjectsForDate(const QDate &date);
    QList<QString> getStaffForDate(const QDate &date);
    QList<QString> getEquipmentForDate(const QDate &date);
    QList<QString> getClientsForDate(const QDate &date);
    QList<QString> getSponsorsForDate(const QDate &date);

    // Fonctions IA
    QString generateAIContentIdeas(const QString &theme, const QString &targetAudience);
    QDateTime analyzeOptimalPostingTime(const QString &contentType, const QString &targetAudience);
    QList<QDate> autoSchedulePosts(const QList<QVariantMap> &posts, int month, int year);
    void smartRescheduleConflicts();
    QMap<QString, QVariant> getAIAnalytics();

    // Membres UI
    QCalendarWidget *m_mainCalendarWidget;
    QGroupBox *m_detailsGroupBox;
    QGroupBox *m_groupBox5;

    QListWidget *m_eventsList;  // Liste de tous les événements
    QComboBox *m_viewModeCombo;
    QComboBox *m_filterCombo;
    QComboBox *m_monthCombo;
    QComboBox *m_yearCombo;

    QPushButton *m_addButton;
    QPushButton *m_editButton;
    QPushButton *m_deleteButton;

    // Boutons IA
    QPushButton *m_aiGenerateButton;
    QPushButton *m_aiAnalyzeButton;
    QPushButton *m_aiScheduleButton;
    QPushButton *m_aiRescheduleButton;
    QPushButton *m_aiAnalyticsButton;

    // Données
    QList<QVariantMap> m_allEvents;
    int m_currentYear;
    int m_currentMonth;
    QTimer *m_deadlineTimer;
};

#endif // CALENDARWIDGET_H
*/
