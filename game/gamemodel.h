#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QVector>

class QGraphicsScene;

class GameModel : public QGraphicsScene
{
    Q_OBJECT
public:

    explicit GameModel(QObject *parent = nullptr);

    void makeMap();

    QVector<QVector<QGraphicsSimpleTextItem *>> mapTextLayer;
    QMap<QString,QGraphicsSimpleTextItem *> players;


    QGraphicsSimpleTextItem *myself=nullptr;
    QString myName;

    void addBackground();
    void addItemsGroups();
};

#endif // GAMEMODEL_H
