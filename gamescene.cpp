#include "gamescene.h"

GameScene::GameScene():VisionSize(100)
{
    //框线
    QGraphicsRectItem *Horizon = new QGraphicsRectItem(150,50,500,500);
    this->addItem(Horizon);

    QGraphicsLineItem *WightLine1 = new QGraphicsLineItem(150,150,650,150);
    this->addItem(WightLine1);

    QGraphicsLineItem *WightLine2 = new QGraphicsLineItem(150,250,650,250);
    this->addItem(WightLine2);

    QGraphicsLineItem *WightLine3 = new QGraphicsLineItem(150,350,650,350);
    this->addItem(WightLine3);

    QGraphicsLineItem *WightLine4 = new QGraphicsLineItem(150,450,650,450);
    this->addItem(WightLine4);

    QGraphicsLineItem *HeightLine1 = new QGraphicsLineItem(250,50,250,550);
    this->addItem(HeightLine1);

    QGraphicsLineItem *HeightLine2 = new QGraphicsLineItem(350,50,350,550);
    this->addItem(HeightLine2);

    QGraphicsLineItem *Heightine3 = new QGraphicsLineItem(450,50,450,550);
    this->addItem(Heightine3);

    QGraphicsLineItem *HeightLine4 = new QGraphicsLineItem(550,50,550,550);
    this->addItem(HeightLine4);


    //地图
    map = new GameMap(MapSize);
    gamemap = map->getMap();

    for(int i=0;i<100;++i){
        for (int j=0;j<100 ;++j ) {
            qDebug()<<gamemap[i][j];
        }
    }

    for (int i = 0; i < VisionSize; ++i) {
        for (int j = 0; j < VisionSize; ++j) {
           QString BlockText = gamemap[i][j];
           auto simpleTextItem = new QGraphicsSimpleTextItem(BlockText);
           QFont font = simpleTextItem->font();
           font.setPixelSize(15);
           simpleTextItem->setFont(font);
           simpleTextItem->setX(160+j*100);
           simpleTextItem->setY(60+i*100);
           this->addItem(simpleTextItem);
        }
    }


    //人物
    QGraphicsPixmapItem *pItem = new QGraphicsPixmapItem();
    QPixmap image(Male);
    pItem->setPixmap(image.scaled(50, 50));
    pItem->setX(375);
    pItem->setY(275);
    this->addItem(pItem);


    n=startTimer(50);

}

void GameScene::timerEvent(QTimerEvent *event)   //每隔一段时间循环一次
{
    emit this->ListenLineEdit();
}
