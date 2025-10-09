#include "integ_ray_rima.h"
#include "ui_integ_ray_rima.h"
#include <QDebug>

integ_ray_rima::integ_ray_rima(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::integ_ray_rima)
{
    ui->setupUi(this);
    // Connect navigation buttons to their handlers. The UI tool buttons are named
    // toolButton_3 (Projet) and toolButton_2 (Sponsor) in the .ui file, so we
    // connect them explicitly to the slots defined in the header.
    // This fixes cases where Qt's auto-connect (on_<objectName>_clicked)
    // doesn't match because the buttons have generic names.
    connect(ui->toolButton_3, &QToolButton::clicked, this, &integ_ray_rima::on_projet_clicked);
    connect(ui->toolButton_2, &QToolButton::clicked, this, &integ_ray_rima::on_sponsor_clicked);
    // Also connect duplicate buttons that appear in other pages (some pages
    // include their own navigation buttons with different object names).
    // For example toolButton_9 (another "Projet") and toolButton_8 (another "Sponsor").
    // Guard with if(...) in case those widgets are not present in some builds.
    if (ui->toolButton_9) {
        connect(ui->toolButton_9, &QToolButton::clicked, this, &integ_ray_rima::on_projet_clicked);
    }
    if (ui->toolButton_8) {
        connect(ui->toolButton_8, &QToolButton::clicked, this, &integ_ray_rima::on_sponsor_clicked);
    }
}

integ_ray_rima::~integ_ray_rima()
{
    delete ui;
}
void integ_ray_rima :: on_projet_clicked()
{
    // show the "acceuil" page in the stacked widget
    qDebug() << "on_projet_clicked: switching to projet page";
    ui->stackedWidget->setCurrentWidget(ui->projet);
}
void integ_ray_rima :: on_sponsor_clicked()
{
    // show the "statistiques" page in the stacked widget
    qDebug() << "on_sponsor_clicked: switching to sponsor page";
    ui->stackedWidget->setCurrentWidget(ui->sponsor);
}
