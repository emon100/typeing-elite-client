#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QObject>
#include <QGraphicsScene>
#include "AllHeader.h"
#include "gamemap.h"
#include "servicelogic.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene();
    QVector<QVector<QString>> gamemap;

    ServiceLogic servicelogic;
    Player Master;
    int VisionSize;
    const int MapSize = 100;

signals:
    void ListenLineEdit();


private:
    QString Male = ":/Logo/Logo/Male.png";
    GameMap *map;
    int n;
    void timerEvent(QTimerEvent *event);

};

#endif // GAMESCENE_H
