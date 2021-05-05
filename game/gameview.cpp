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
    this->setInteractive(false);
    this->centerOn(0,0);
}


