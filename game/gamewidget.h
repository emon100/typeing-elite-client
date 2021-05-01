#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QGraphicsRectItem>
class Network;
class NetworkSystem;

class GameModel;
class GameView;
class KeyboardInput;
class NetworkIO;

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent=nullptr);

    void addMyself(const QString &playerName);

    void handleGameInput(int keyCode);
private:
    void initWidget();

    GameModel *model;
    GameView  *view;

    KeyboardInput *kb;
    NetworkSystem *netSys;

    QGraphicsRectItem *Horizon ;

    void addPlayer(const QString &id,const QString &name,int x,int y);
    void movePlayer(const QString &name,int x,int y);

    QVector<int> ViewField(QGraphicsSimpleTextItem *player_me,int size);

    QString flag;
    QVector<QGraphicsSimpleTextItem *> hitText;
    void hit(char c, QGraphicsSimpleTextItem *player_me, int n);
};

#endif // GAMEWIDGET_H
