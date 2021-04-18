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

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent=nullptr);

signals:


private:
    void initWidget();

    GameModel *model;
    GameView  *view;

    KeyboardInput *kb;
    Network *client;
    NetworkSystem *netSys;


    void addMyself(const QString &playerName);
    void addPlayer(const QString &id,const QString &name,int x,int y);
    void movePlayer(const QString &name,int x,int y);
    void handleGameInput(int keyCode);
};

#endif // GAMEWIDGET_H
