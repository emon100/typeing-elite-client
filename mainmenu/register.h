#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>

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
    const int WindowX = 1200;
    const int WindowY = 800;
    void keyPressEvent(QKeyEvent *event);
};

#endif // REGISTER_H
