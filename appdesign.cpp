#include "AppDesign.h"
#include <QToolButton>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QGraphicsDropShadowEffect>
#include <QDateEdit>
#include <QListWidget>
#include <QDebug>
#include <QRadioButton>      // AJOUTER
#include <QCheckBox>         // AJOUTER
#include <QSpinBox>          // AJOUTER
#include <QTextEdit>         // AJOUTER
#include <QPlainTextEdit>    // AJOUTER
#include <QDoubleSpinBox>    // AJOUTER
#include <QScrollBar>

// ===== TES COULEURS EXACTES =====
QString AppDesign::purpleColor()      { return "#9B59B6"; }
QString AppDesign::grayColor()        { return "#BDC3C7"; }
QString AppDesign::pinkColor()        { return "#F8C8DC"; }
QString AppDesign::darkTextColor()    { return "#000000"; }
QString AppDesign::lightTextColor()   { return "#FFFFFF"; }

// ===== COULEURS PROFESSIONNELLES SUPPLÉMENTAIRES =====
QString AppDesign::lightGray()        { return "#F5F5F5"; }    // Fond des pages
QString AppDesign::mediumGray()       { return "#E0E0E0"; }    // Bordures
QString AppDesign::whiteColor()       { return "#FFFFFF"; }    // Blanc

// ===== STYLE PANEL DE NAVIGATION =====
QString AppDesign::navigationPanelStyle()
{
    return QString(
               "QGroupBox { "
               "    border: 2px solid %1; "
               "    border-radius: 15px; "
               "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
               "                               stop:0 %1, stop:1 %2); "
               "    padding: 15px; "
               "    margin-top: 10px; "
               "}"
               "QGroupBox::title { "
               "    subcontrol-origin: margin; "
               "    subcontrol-position: top center; "
               "    padding: 10px 20px; "
               "    border-radius: 15px; "
               "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
               "                               stop:0 %1, stop:1 %2); "
               "    color: %3; "
               "    font-size: 20px; "
               "    font-weight: bold; "
               "}"
               ).arg(purpleColor(), grayColor(), darkTextColor());
}

// ===== STYLE BOUTONS DE NAVIGATION =====
QString AppDesign::navigationButtonStyle()
{
    return QString(
               "QToolButton { "
               "    border: none; "
               "    border-radius: 10px; "
               "    color: %1; "
               "    padding: 12px 15px; "
               "    margin: 6px 8px; "
               "    background: transparent; "
               "    text-align: left; "
               "    font-size: 14px; "
               "    font-weight: 500; "
               "}"
               ).arg(lightTextColor());
}

QString AppDesign::navigationButtonHoverStyle()
{
    return QString(
        "QToolButton:hover { "
        "    background: rgba(255, 255, 255, 0.2); "
        "    padding-left: 18px; "  // Légère translation
        "}"
        );
}

QString AppDesign::navigationButtonActiveStyle()
{
    return QString(
               "QToolButton:checked { "
               "    background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, "
               "                               stop:0 %1, stop:1 %2); "
               "    border-left: 4px solid %3; "
               "    font-weight: bold; "
               "    color: %3; "
               "    box-shadow: 2px 0px 8px rgba(0, 0, 0, 0.2); "
               "}"
               ).arg(purpleColor(), pinkColor(), lightTextColor());
}

// ===== ÉMOJIS POUR LES BOUTONS =====
QList<QString> AppDesign::getButtonEmojis()
{
    return {
        "👨‍💼 ",  // Staff (index 0)
        "👥 ",   // Client (index 1)
        "🎥 ",   // Materiel (index 2)
        "📁 ",   // Projet (index 3)
        "🤝 ",   // Sponsor (index 4)
        "🎨 "    // Createur (index 5)
    };
}

void AppDesign::addEmojiIcons(QList<QToolButton*> buttons)
{
    QList<QString> emojis = getButtonEmojis();

    for (int i = 0; i < buttons.size() && i < emojis.size(); ++i) {
        QToolButton* button = buttons[i];
        QString emoji = emojis[i];
        QString currentText = button->text();

        // Enlever les émojis existants pour éviter les doublons
        for (const QString& existingEmoji : emojis) {
            currentText = currentText.remove(existingEmoji);
        }

        // Ajouter le nouvel émoji
        button->setText(emoji + currentText.trimmed());
    }
}

// ===== APPLIQUER LES STYLES =====
void AppDesign::styleNavigationButtons(QList<QToolButton*> buttons, int activeIndex)
{
    QString baseStyle = navigationButtonStyle() +
                        navigationButtonHoverStyle() +
                        navigationButtonActiveStyle();

    for (int i = 0; i < buttons.size(); ++i) {
        QToolButton* button = buttons[i];
        button->setStyleSheet(baseStyle);
        button->setCheckable(true);
        button->setChecked(i == activeIndex);
    }
}

void AppDesign::setActiveButton(QToolButton* button)
{
    if (button) {
        button->setChecked(true);
    }
}

void AppDesign::setInactiveButton(QToolButton* button)
{
    if (button) {
        button->setChecked(false);
    }
}

