#include "gamewidget.h"
#include "gameview.h"
#include "gamemodel.h"

#include "keyboardinput.h"
#include "networksystem.h"

#include <QGraphicsSimpleTextItem>
#include <QRandomGenerator>
#include <QLineEdit>

#include <QPropertyAnimation>

GameWidget::GameWidget(QWidget *parent):
    QWidget(parent),
    model(new GameModel(this)),
    view(new GameView(model,this)),
    kb(new KeyboardInput(this)),
    netSys(new NetworkSystem("localhost",8888,this))
{
    initWidget();

    model->myId= QString("p%1").arg(QRandomGenerator::global()->bounded(1,100000));
    requestConnect();

    dispatchNetworkActivity();
}

void GameWidget::initWidget(){
    setWindowTitle("打字精英");
    installEventFilter(kb);
}

void GameWidget::requestConnect()
{
    netSys->requestConnect(model->myId);
}

void GameWidget::joinPlayer(const QString &id, const QString &name)
{
    qDebug()<<"joinPlayer "<<id<<' '<<name;
    auto &players = model->players;
    auto it = players.constFind(id);
    if(it!=players.cend()){
        qDebug()<<"player exists!"<<id;
        return;
    }
    auto p = players[id] = model->addSimpleText(name);
    p->setVisible(false);
    if(id==model->myId){
        model->myself=p;
        Horizon = model->addRect(0,0,0,0);
        Horizon->setVisible(false);
    }
}

void GameWidget::movePlayer(const QString &id, int x,int y)
{
    auto &players = model->players;
    auto it = players.find(id);
    if(it==players.end()){
        qDebug()<<"player not found."<<id;
        return;
    }
    auto p = it.value();
    p->setVisible(true);
    p->setPos(x,y);
    if(id==model->myId){
        QVector<int> viewSize = ViewField(p,3);
        Horizon->setRect(viewSize[0],viewSize[2],viewSize[1]-viewSize[0]+50,viewSize[3]-viewSize[2]+50);
        Horizon->setVisible(true);
    }
}

void GameWidget::killPlayer(const QString &id)
{
    qDebug()<<"killPlayer "<<id;
    auto &players = model->players;
    auto it = players.constFind(id);
    if(it==players.cend()){
        qDebug()<<"player not found."<<id;
    }
    it.value()->setVisible(false);
}

void GameWidget::leavePlayer(const QString &id)
{
    qDebug()<<"leavePlayer "<<id;
    auto &players = model->players;
    auto it = players.constFind(id);
    if(it==players.cend()){
        qDebug()<<"player not found."<<id;
    }
    if(id==model->myId){
        model->myself=nullptr;
    }
    model->removeItem(it.value());
    players.erase(it);
}


QVector<int> GameWidget::ViewField(QGraphicsSimpleTextItem *player_me,int n){
    int x=player_me->x();
    int y=player_me->y();
    int left = x-50*n <0? 0:x-50*n;
    int right = x+50*n;
    int up = y-50*n < 0 ? 0:y-50*n;
    int down = y+50*n;
    return QVector<int>{left,right,up,down};
}

void GameWidget::hit(char c,QGraphicsSimpleTextItem *player_me,int n){
    flag+=c;
    qDebug()<<flag;
    QVector<int> size = ViewField(player_me,n);
    for (int i=0;i<hitText.size();i++) {
        model->removeItem(hitText[i]);
    }
    hitText.resize(0);
    auto &text=model->mapTextLayer;
    int left=size[0]/50;
    int right=size[1]/50;
    int up=size[2]/50;
    int down=size[3]/50;
    bool wu = true;
    for (int i=left;i<=right;i++) {
        for(int j=up;j<=down;j++){
            if(flag==text[i][j]->text()){
                flag ="";
                netSys->requestMove(text[i][j]->x(),text[i][j]->y()+10);
                return;
            }
            if(flag == text[i][j]->text().mid(0,flag.length())){
                QGraphicsSimpleTextItem *t = model->addSimpleText(flag);
                t->setBrush(QBrush(QColor(220, 20, 60)));
                t->setPos(text[i][j]->x(),text[i][j]->y());
                hitText.push_back(t);
                wu = false;
            }
        }
    }
    if(wu){
        flag ="";
    }
}

void GameWidget::dispatchNetworkActivity()
{
    connect(kb,&KeyboardInput::goodKey,this,&GameWidget::handleGameInput);
    //TODO connect(netSys,&NetworkSystem::disconnected)
    connect(netSys,&NetworkSystem::joinPlayerCommand, this, &GameWidget::joinPlayer);
    connect(netSys,&NetworkSystem::spawnPlayerCommand, this, &GameWidget::movePlayer);//TODO
    connect(netSys,&NetworkSystem::movePlayerCommand,this, &GameWidget::movePlayer);
    connect(netSys,&NetworkSystem::killPlayerCommand,this, &GameWidget::killPlayer);
    connect(netSys,&NetworkSystem::leavePlayerCommand,this,&GameWidget::leavePlayer);

}

void GameWidget::handleGameInput(int keyCode){
    auto player_me = model->myself;
    if(player_me==nullptr){
        return;
    }

    hit(keyCode-('A'-'a'),player_me,3);
}
