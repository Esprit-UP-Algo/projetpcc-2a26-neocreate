#ifndef APPDESIGN_H
#define APPDESIGN_H

#include <QString>
#include <QWidget>
#include <QToolButton>
#include <QTableWidget>

class AppDesign
{
public:
    // ===== COULEURS =====
    static QString purpleColor();
    static QString grayColor();
    static QString pinkColor();
    static QString darkTextColor();
    static QString lightTextColor();
    static QString lightGray();
    static QString mediumGray();
    static QString whiteColor();

    // ===== STYLES DE BASE =====
    static QString navigationPanelStyle();
    static QString navigationButtonStyle();
    static QString navigationButtonHoverStyle();
    static QString navigationButtonActiveStyle();

    static QString lineEditStyle();
    static QString pushButtonStyle();
    static QString comboBoxStyle();
    static QString groupBoxStyle();
    static QString labelStyle();
    static QString pageBackgroundStyle();
    static QString quitButtonStyle();

    // ===== STYLES DE FORMULAIRE AMÉLIORÉS =====


    // ===== FONCTIONS UTILITAIRES =====
    static QList<QString> getButtonEmojis();
    static void addEmojiIcons(QList<QToolButton*> buttons);
    static void styleNavigationButtons(QList<QToolButton*> buttons, int activeIndex);
    static void setActiveButton(QToolButton* button);
    static void setInactiveButton(QToolButton* button);

    static void applyPageDesign(QWidget *page);

    // ===== FONCTION POUR STYLISER LES FORMULAIRES =====

};

#endif // APPDESIGN_H
