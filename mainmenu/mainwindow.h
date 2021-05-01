#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwindow.h"
#include "network.h"
#include "register.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    LoginWindow *loginwindow;
    Register *registerwindow;

private slots:
    void on_LogInButton_clicked();



    void on_RegisterButton_clicked();

private:
    Ui::MainWindow *ui;
    const QString Logo=":/Logo/Logo/TypeMaster.jpg";
    void paintEvent(QPaintEvent *);    //绘图事件
    const int WindowX = 1200;
    const int WindowY = 800;
    void iSlot(QString GetData);
};

#endif // MAINWINDOW_H
