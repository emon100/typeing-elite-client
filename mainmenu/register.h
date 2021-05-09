#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include "allurl.h"
#include <QPainter>
namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_RegisterButton_clicked();

    void on_BackButton_clicked();

signals:
    void RegisterWindowBack();
private:
    Ui::Register *ui;
    const int WindowX = ::WindowX;
    const int WindowY = ::WindowY;
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *);    //绘图事件
};

#endif // REGISTER_H
