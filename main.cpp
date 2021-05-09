#include "mainmenu/mainwindow.h"
#include "mainmenu/allurl.h"
#include "game/gamewidget.h"
#include <QtNetwork>
#include <QApplication>
#include <iostream>
#include <string>
const QString signupurl = "http://1.116.238.196:3000/api/signup";
const QString signinurl = "http://1.116.238.196:3000/api/signin";
const QString chaturl = "http://1.116.238.196:3000/api/chat";
const QString starturl = "http://1.116.238.196:3000/api/startGame";
const QString scoreurl = "http://1.116.238.196:3000/api/score";
const QString changepasswordurl = "http://1.116.238.196:3000/api/changepassword";
const QString getRankListurl = "http://1.116.238.196:3000/api/getRankList";
const QString changenicknameurl = "http://1.116.238.196:3000/api/changeNickName";
const int WindowX = 1200;
const int WindowY = 800;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //GameWidget w("localhost",18888,"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2MDk1MmMwMjczMDllZTBkOThmYzRlNGEiLCJ1c2VybmFtZSI6ImFkbWluMSIsIm5pY2tuYW1lIjoiYWRtaW4xIiwicGFzc3dvcmQiOiIkMmEkMTAkOE9TVVYubXVzdjR6VEUuanhhWEQ3LnBBSWVCMlFldTlqc3BqZlAuOC8udFNpWks0QU9pL3UiLCJwaG9uZU51bWJlciI6IjEyMzQ1MSIsImVtYWlsIjoiYWRtaW4xQHFxLmNvbSIsIl9fdiI6MCwiaWF0IjoxNjIwMzg4ODgyfQ.RXPsPGFFxiBdocXuX83QKLxd4LCEZ8raGNuy6AAsCn8");
    w.show();
    return a.exec();
}
