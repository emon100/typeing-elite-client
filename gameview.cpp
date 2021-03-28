#include <QGraphicsSimpleTextItem>
#include <QGraphicsScene>
#include "gameview.h"

GameView::GameView(QGraphicsScene *scene,QWidget *parent):
    QGraphicsView(scene,parent),
    scene(scene)
{
    this->resize(WindowX,WindowY);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->rotate(10);
    for(int i = 10;i>=0;--i){
        auto text = scene->addSimpleText(QString("||||||||| %1").arg(i));
        text->setPos(0,i*100);
    }
    this->centerOn(0,0);
}


