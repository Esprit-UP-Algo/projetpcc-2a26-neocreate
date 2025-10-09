#include "integ_abir_login.h"
#include "ui_integ_abir_login.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// This slot name matches the objectName from the UI: toolButton_seConnecter
void MainWindow::on_toolButton_seConnecter_clicked()
{
    // Read the id and password from the UI (lineEdit, lineEdit_2)
    const QString id = ui->lineEdit->text();
    const QString pwd = ui->lineEdit_2->text();

    // Check credentials: admin / admin123
    if (id == QLatin1String("admin") && pwd == QLatin1String("admin123")) {
        // switch to the staff page in the stacked widget
        ui->stackedWidget->setCurrentWidget(ui->staff);
    } else {
        QMessageBox::warning(this, tr("Authentification"), tr("Identifiant ou mot de passe incorrect."));
    }
}

void MainWindow::on_toolButton_7_clicked()
{
    // Try to find a page named "materiel" in the widget tree (created by the .ui)
    QWidget *materielPage = this->findChild<QWidget *>("materiel");
    if (materielPage) {
        ui->stackedWidget->setCurrentWidget(materielPage);
    } else {
        QMessageBox::information(this, tr("Navigation"), tr("Page 'materiel' introuvable. Regénérez l'UI si nécessaire."));
    }
}

void MainWindow::on_toolButton_3_clicked()
{
    // switch back to staff page (ui->staff exists in generated UI)
    if (ui->staff)
        ui->stackedWidget->setCurrentWidget(ui->staff);
    else
        QMessageBox::information(this, tr("Navigation"), tr("Page 'staff' introuvable."));
}
