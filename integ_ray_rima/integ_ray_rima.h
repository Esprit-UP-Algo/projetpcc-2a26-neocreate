#ifndef INTEG_RAY_RIMA_H
#define INTEG_RAY_RIMA_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class integ_ray_rima;
}
QT_END_NAMESPACE

class integ_ray_rima : public QMainWindow
{
            Q_OBJECT

        public:
            integ_ray_rima(QWidget *parent = nullptr);
            ~integ_ray_rima();

        private slots:
            void on_projet_clicked();
            void on_sponsor_clicked();

        private:
            Ui::integ_ray_rima *ui;
};
#endif // INTEG_RAY_RIMA_H
