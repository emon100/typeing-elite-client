#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

class GameWidget;

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QString JWT,QWidget *parent = nullptr);
    ~LoginWindow();
    GameWidget *gamewidget;

private slots:

    void on_Send_clicked();

    void on_Start_clicked();

    void on_Exit_clicked();

signals:
    void loginwindowback();
private:
    Ui::LoginWindow *ui;
    QString backgroud =":/Logo/Logo/BackGround.jpg";
    void paintEvent(QPaintEvent *);    //绘图事件
    void timerEvent(QTimerEvent *event);
    const int WindowX = 1200;
    const int WindowY = 800;
    QString JWT;
    int n;

};

#endif // LOGINWINDOW_H
