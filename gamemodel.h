#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QVector>

class QGraphicsScene;

class GameModel : public QGraphicsScene
{
    Q_OBJECT


    void makeMap();
    void addBackground();
    void addItemsGroups();

    QVector<QVector<QGraphicsSimpleTextItem *>> mapTextLayer;


public:

    explicit GameModel(QObject *parent = nullptr);
signals:
};

#endif // GAMEMODEL_H
