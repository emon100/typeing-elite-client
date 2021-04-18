#include "gamewidget.h"
#include "gameview.h"
#include "gamemodel.h"

#include "keyboardinput.h"
#include "network.h"
#include "networksystem.h"

#include <QGraphicsSimpleTextItem>
#include <QRandomGenerator>
#include <QTimer>



GameWidget::GameWidget(QWidget *parent):
    QWidget(parent),
    model(new GameModel(this)),
    view(new GameView(model,this)),
    kb(new KeyboardInput(this)),
    netSys(new NetworkSystem(new Network("localhost", 8888,this),this))
{
    initWidget();

    auto &player_Name = model->myName = QString("p%1").arg(QRandomGenerator::global()->bounded(1,100000));
    addMyself(player_Name);

    connect(kb,&KeyboardInput::goodKey,this,&GameWidget::handleGameInput);

    connect(netSys,&NetworkSystem::addPlayerCommand, this, &GameWidget::addPlayer);
    connect(netSys,&NetworkSystem::movePlayerCommand,this, &GameWidget::movePlayer);
}

void GameWidget::initWidget(){
    setWindowTitle("打字精英");
    installEventFilter(kb);
}

void GameWidget::addMyself(const QString &playerName)
{
    netSys->requestConnect(playerName,playerName);
}

void GameWidget::addPlayer(const QString &id, const QString &name, int x, int y)
{
    auto &players = model->players;
    auto it = players.constFind(id);
    if(it!=players.cend()){
        qDebug()<<id<<' '<<name<<' '<<x<<' '<<y;
    }
    auto p = players[id] = model->addSimpleText(name);
    p->setPos(x,y);
}

void GameWidget::movePlayer(const QString &id, int x, int y)
{
    auto &players = model->players;
    auto it = players.find(id);
    if(it==players.end()){
        qDebug()<<id<<' '<<x<<' '<<y;
    }
    it.value()->setPos(x,y);
    if(model->myself){
        view->centerOn(model->myself->pos());
    }
}

void GameWidget::handleGameInput(int keyCode)
{
    auto player_me = model->myself;
    if(player_me==nullptr){
        model->myself = player_me = model->players[model->myName];
        if(player_me==nullptr){
            return ;
        }
    }
    auto pos = player_me->pos();
    switch(keyCode){
    case Qt::Key_W:
            pos.ry()-=10;
            break;
    case Qt::Key_A:
            pos.rx()-=10;
            break;
    case Qt::Key_S:
            pos.ry()+=10;
            break;
    case Qt::Key_D:
            pos.rx()+=10;
            break;
    default: return;
    }
    netSys->requestMove(int(pos.x()),int(pos.y()));
}
