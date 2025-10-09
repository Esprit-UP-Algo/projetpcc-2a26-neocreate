#ifndef INTEG_ABIR_LOGIN_H
#define INTEG_ABIR_LOGIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
            Q_OBJECT

        public:
            MainWindow(QWidget *parent = nullptr);
            ~MainWindow();

        private slots:
            // auto-connected slot for the login button (objectName: toolButton_seConnecter)
            void on_toolButton_seConnecter_clicked();
            // auto-connected slots for navigation in the staff panel
            void on_toolButton_7_clicked(); // Materiel
            void on_toolButton_3_clicked(); // Staff technique

        private:
            Ui::MainWindow *ui;
};
#endif // INTEG_ABIR_LOGIN_H
