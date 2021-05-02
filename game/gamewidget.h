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
    void killPlayer(const QString &id);
    void leavePlayer(const QString &id);

private:
    void initWidget();
    void hit(char c, QGraphicsSimpleTextItem *player_me, int n);
    void dispatchNetworkActivity();
    void requestConnect();

    GameModel *model;
    GameView  *view;

    KeyboardInput *kb;
    NetworkSystem *netSys;

    QGraphicsRectItem *Horizon ;

    QVector<int> ViewField(QGraphicsSimpleTextItem *player_me,int size);

    QString flag;
    QVector<QGraphicsSimpleTextItem *> hitText;
};

#endif // GAMEWIDGET_H
