#include "gamewidget.h"
#include "gameview.h"
#include "gamemodel.h"

#include "keyboardinput.h"

#include <QGraphicsSimpleTextItem>
#include <QtNetwork>
#include <QLineEdit>



GameWidget::GameWidget(QWidget *parent):
    QWidget(parent),
    model(new GameModel(this)),
    view(new GameView(model,this)),
    kb(new KeyboardInput(this))//,client(new QTcpSocket(this))
{
   // client->connectToHost("localhost",8888);
    auto scene = model;
    auto player_me = scene->addSimpleText("aaa");
    player_me->setPos(10,10);
    player_me->setRotation(100);

    auto player_other = scene->addSimpleText("bbb");
    player_other->setPos(20,20);

    connect(kb,&KeyboardInput::goodKey,[player_me,nowPos=QPoint{20,20},this]() mutable {
        this->model->update();
        auto oldPos = player_me->pos();

        oldPos.rx()+=50;
        oldPos.ry()+=50;
        qDebug()<<oldPos;
        player_me->setPos(oldPos);

        nowPos.rx()+=50;
        nowPos.ry()+=50;
        this->view->centerOn(nowPos.x(),nowPos.y());
    });
    /*
    connect(client,&QTcpSocket::readyRead,[player_me=player_other,this](){
        this->client->write("sjadk\n");
        qDebug()<<QString(this->client->readAll());
            auto oldPos = player_me->pos();
            oldPos.rx()+=50;
            oldPos.ry()+=50;
            player_me->setPos(oldPos);
    });
    */
}

void GameWidget::initWidget(){
    setWindowTitle("打字精英");
    installEventFilter(kb);
}

