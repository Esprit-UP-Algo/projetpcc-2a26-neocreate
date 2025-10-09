#include "integ_ray_rima.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    integ_ray_rima w;
    w.show();
    return a.exec();
}
