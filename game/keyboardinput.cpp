#include <QKeyEvent>
#include "keyboardinput.h"

bool KeyboardInput::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *e = static_cast<QKeyEvent *>(event);
        if(e->key()>=0x41 && e->key()<=0x5a){
            emit goodKey(e->key());
            return true;
        }else{
            return QObject::eventFilter(obj, event);
        }

    }else{
        return QObject::eventFilter(obj, event);
    }
}

KeyboardInput::KeyboardInput(QObject *parent) : QObject(parent)
{

}
