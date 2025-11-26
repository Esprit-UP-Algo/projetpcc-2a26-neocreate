#ifndef SPONSORMANAGER_H
#define SPONSORMANAGER_H

#include <QObject>
#include <QTableWidget>
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QMap>
#include <QList>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QTimer>        // Déjà présent → parfait
#include <QDateTime>     // Déjà présent → parfait
#include <QPainter>      // AJOUTÉ : obligatoire pour QPainter dans paintEvent
#include <QSystemTrayIcon>
#include  <QApplication>  // ← AJOUT 1: Pour QApplication
#include <QPropertyAnimation> // ← AJOUT 2: Pour les animations
class SponsorManager : public QObject
{
    Q_OBJECT

public:
    explicit SponsorManager(QObject *parent = nullptr);

    // === TES FONCTIONS EXISTANTES (PDF, notifications, etc.) ===
    static bool exporterPDF(QTableWidget* tableau, const QString& fichierSortie);
    static void executerExportPDF(QTableWidget* tableau, QWidget* parent = nullptr);
    static int getNombreNotifications();
    static QList<QMap<QString, QString>> getNotificationsDetail();
    static void afficherFenetreNotifications(QWidget* parent);
    static void renouvelerContrat(const QString& sponsorId, QWidget* parent);

    // ==================== AJOUT 3: NOUVELLE FONCTION PUBLIQUE ====================
    void demarrerNotificationsAutomatiques(QWidget* parentWidget); // ← AJOUT ICI

    // ================================================================
    // === NOUVELLE PARTIE STATISTIQUES MODERNE & PRO (tout static) ===
    // ================================================================

    // Récupération des données brutes
    static QMap<QString, int> getStatsContributionsLive();
    static QMap<QString, int> getStatsAnciennete();
    static QString getDerniereModification();

    // === FONCTION PRINCIPALE : DASHBOARD LIVE ULTRA MODERNE ===
    static void afficherDashboardKPI(QGroupBox* groupBox);
    void showNotification(const QString &titre, const QString &message);

private:
    QSystemTrayIcon *m_trayIcon = nullptr;

    // ==================== AJOUT 4: MEMBRES PRIVÉS POUR NOTIFICATIONS ====================
    QWidget* m_parentWidget = nullptr;        // ← AJOUT: Stocke la fenêtre parent
    QTimer* m_toastTimer = nullptr;           // ← AJOUT: Timer pour séquence
    QList<QMap<QString, QString>> m_toastQueue; // ← AJOUT: File d'attente
    QWidget* m_currentToast = nullptr;        // ← AJOUT: Toast actuellement affiché

    // ==================== AJOUT 5: FONCTIONS PRIVÉES POUR NOTIFICATIONS ====================
    void afficherProchaineNotification();     // ← AJOUT: Affiche notification suivante
    void creerEtAfficherToast(const QMap<QString, QString>& notif); // ← AJOUT: Crée le toast
    void masquerToastActuel();                // ← AJOUT: Cache le toast après 5s

    // Widget réutilisable : un seul donut moderne qui fait tout
    static QWidget* createModernDonutChart(
        const QString &title,
        const QMap<QString, int> &data,
        int total,
        const QMap<QString, QString> &colorMap,
        const QMap<QString, QString> &labelMap = QMap<QString, QString>()
        );

    // === Tu peux garder tes anciennes fonctions si tu veux compatibilité rétro ===
    static QWidget* createKPICard(const QString &title, int count, int total, const QString &color);
    static QWidget* createPieChart(const QMap<QString, int>& stats, int total);
    static QWidget* createAncienneteChart(const QMap<QString, int>& stats, int total);
};

#endif // SPONSORMANAGER_H
