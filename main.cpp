#include "mainmenu/mainwindow.h"
#include "mainmenu/allurl.h"
#include "mainmenu/loginwindow.h"
#include "game/gamewidget.h"
#include <QtNetwork>
#include <QApplication>
#include <iostream>
#include <string>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //LoginWindow w("sdfsd");
    //GameWidget w("localhost",18888,"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2MDk1MmMwMjczMDllZTBkOThmYzRlNGEiLCJ1c2VybmFtZSI6ImFkbWluMSIsIm5pY2tuYW1lIjoiYWRtaW4xIiwicGFzc3dvcmQiOiIkMmEkMTAkOE9TVVYubXVzdjR6VEUuanhhWEQ3LnBBSWVCMlFldTlqc3BqZlAuOC8udFNpWks0QU9pL3UiLCJwaG9uZU51bWJlciI6IjEyMzQ1MSIsImVtYWlsIjoiYWRtaW4xQHFxLmNvbSIsIl9fdiI6MCwiaWF0IjoxNjIwMzg4ODgyfQ.RXPsPGFFxiBdocXuX83QKLxd4LCEZ8raGNuy6AAsCn8");
    w.show();
    return a.exec();
}
