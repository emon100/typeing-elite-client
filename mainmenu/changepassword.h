#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QWidget>
#include <QPainter>
namespace Ui {
class ChangePassword;
}

class ChangePassword : public QWidget
{
    Q_OBJECT

public:
    explicit ChangePassword(QWidget *parent = nullptr);
    ~ChangePassword();
signals:
    void changepasswordwindowback();
private slots:
    void on_BackPushButton_clicked();

    void on_ChangePushButton_clicked();

private:
    Ui::ChangePassword *ui;
    void paintEvent(QPaintEvent *);    //绘图事件
};

#endif // CHANGEPASSWORD_H
