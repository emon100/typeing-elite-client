#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "allurl.h"

namespace Ui {
class MainWindow;
}

class LoginWindow;
class Register;
class ChangePassword;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    LoginWindow *loginwindow;
    Register *registerwindow;
    ChangePassword *changepasswordwindow;

private slots:
    void on_LogInButton_clicked();

    void on_RegisterButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_ChangePasswordPushButton_clicked();

private:
    Ui::MainWindow *ui;

    void paintEvent(QPaintEvent *);    //绘图事件
    void keyPressEvent(QKeyEvent *event);
    const int WindowX =::WindowX;
    const int WindowY =::WindowY;
    void iSlot(QString GetData);
};

#endif // MAINWINDOW_H
