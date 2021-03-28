#include <QtNetwork>
#include <QApplication>
#include <iostream>
#include <string>
#include "gamewidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWidget w;
    w.show();
    return a.exec();
}
