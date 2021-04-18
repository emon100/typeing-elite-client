#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QGraphicsScene>
#include <QVector>
#include <QHash>

class QGraphicsScene;
class QGraphicsSimpleTextItem;

class GameModel : public QGraphicsScene
{
    Q_OBJECT
public:

    explicit GameModel(QObject *parent = nullptr);

    void makeMap();

    QVector<QVector<QGraphicsSimpleTextItem *>> mapTextLayer;
    QHash<QString,QGraphicsSimpleTextItem *> players;

    QGraphicsSimpleTextItem *myself=nullptr;
    QString myName;

    void addBackground();
    void addItemsGroups();
};

#endif // GAMEMODEL_H
