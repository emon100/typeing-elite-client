#include <QtNetwork>
#include <QApplication>
#include <iostream>
#include <string>
#include "gamewidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bool isServer = false;

    if(isServer){

        return 0;
    }else{
        GameWidget w;
        w.show();
        return a.exec();
    }
}

