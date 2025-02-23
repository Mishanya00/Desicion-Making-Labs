#include "simplewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimpleWindow w;
    w.show();
    return a.exec();
}
