#include "de_info_aprobada.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    de_info_aprobada w;
    w.show();
    return a.exec();
}
