#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QVector>

class QGraphicsScene;

class GameModel : public QGraphicsScene
{
    Q_OBJECT
public:

    explicit GameModel(QObject *parent = nullptr);

    void makeMap();

    QVector<QVector<QGraphicsSimpleTextItem *>> mapTextLayer;
    QMap<QString,QGraphicsTextItem *> players;


    QGraphicsTextItem *myself=nullptr;
    QString myId;

    void addBackground();
    void addItemsGroups();
};

#endif // GAMEMODEL_H
