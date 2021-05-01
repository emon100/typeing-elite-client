#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <gameview.h>
class GameWidget;

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    GameWidget *gamewidget;

private slots:
    void on_pushButton_clicked();
    void on_BeginGameButton_clicked();

signals:
    void loginwindowback();
private:
    Ui::LoginWindow *ui;
    QString backgroud =":/Logo/Logo/BackGround.jpg";
    void paintEvent(QPaintEvent *);    //绘图事件
    const int WindowX = 1200;
    const int WindowY = 800;
};

#endif // LOGINWINDOW_H
