#ifndef GAMEVIEW_H
#define GAMEVIEW_H


#include <QObject>
#include <QGraphicsView>
#include "servicelogic.h"
#include "player.h"

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    GameView(QGraphicsScene *scene,QWidget *parent=nullptr);
private:
    QGraphicsScene *scene;//GameScene is the representation of model.

    QString Set = ":/Logo/Logo/Set.png";
    const int WindowX = 800;
    const int WindowY = 600;

signals:
    void GameBack();

};

#endif // GAMEVIEW_H
