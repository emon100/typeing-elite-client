#include <QKeyEvent>
#include "keyboardinput.h"

bool KeyboardInput::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *e = static_cast<QKeyEvent *>(event);
        emit goodKey(e->key());
        return true;
    }else{
        return QObject::eventFilter(obj, event);
    }
}

KeyboardInput::KeyboardInput(QObject *parent) : QObject(parent)
{

}
