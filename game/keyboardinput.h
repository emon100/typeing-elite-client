#ifndef KEYBOARDINPUT_H
#define KEYBOARDINPUT_H

#include <QObject>

class KeyboardInput : public QObject
{
    Q_OBJECT

protected:
    bool eventFilter(QObject *obj,QEvent *event);
public:
    explicit KeyboardInput(QObject *parent = nullptr);

signals:
    void goodKey(int c);
};

#endif // KEYBOARDINPUT_H
