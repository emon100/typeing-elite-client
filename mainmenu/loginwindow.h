#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QStandardItem>
#include "allurl.h"
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

    void on_Help_clicked();

    void on_FinishChangeNameButton_clicked();

    void on_ChangeNameButton_clicked();

signals:
    void loginwindowback();
private:
    Ui::LoginWindow *ui;
    QString backgroud =":/Logo/Logo/BackGround.jpg";
    void paintEvent(QPaintEvent *);    //绘图事件
    void timerEvent(QTimerEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    const int WindowX = ::WindowX;
    const int WindowY = ::WindowY;
    QString JWT;
    int n;
    void UpdateInformation();
    bool flag = true;
    QStandardItemModel *rankitem;

};

#endif // LOGINWINDOW_H
