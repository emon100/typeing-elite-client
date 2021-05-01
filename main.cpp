#include "mainwindow.h"
#include "gamewidget.h"
#include <QtNetwork>
#include <QApplication>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    GameWidget w;
    w.show();
    return a.exec();
}
