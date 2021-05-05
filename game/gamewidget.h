#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QKeyEvent>
class Network;
class NetworkSystem;

class GameModel;
class GameView;
class KeyboardInput;
class NetworkIO;
class QGraphicsSimpleTextItem;
class QGraphicsTextItem;
class QGraphicsRectItem;

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent=nullptr);


    void handleGameInput(int keyCode);

    void joinPlayer(const QString &id, const QString &name);
    void movePlayer(const QString &id,int x,int y);
    void killPlayer(const QString &from, const QString &id);
    void leavePlayer(const QString &id);

private:
    void initWidget();
    void hit(char c, QGraphicsTextItem *player_me, int n);
    void dispatchNetworkActivity();
    void requestConnect();
    QVector<int> ViewField(int x, int y, int n);

    GameModel *model;
    GameView  *view;

    KeyboardInput *kb;
    NetworkSystem *netSys;

    QGraphicsRectItem *Horizon ;


    QString flag;
    QVector<QGraphicsSimpleTextItem *> hitText;
};

#endif // GAMEWIDGET_H
