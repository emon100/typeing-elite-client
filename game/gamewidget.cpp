#include "gamewidget.h"
#include "gameview.h"
#include "gamemodel.h"

#include "keyboardinput.h"
#include "networksystem.h"

#include <QGraphicsSimpleTextItem>
#include <QRandomGenerator>
#include <QLineEdit>
#include <QTransform>
#include <QLabel>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QTextBrowser>
#include <QMessageBox>
GameWidget::GameWidget(QString host, int port, QString JWT,QWidget *parent):
    QWidget(parent),
    model(new GameModel(this)),
    view(new GameView(model,this)),
    kb(new KeyboardInput(this)),
    netSys(new NetworkSystem(host,port,this))
{
    initWidget();

    requestConnect(JWT);
    dispatchNetworkActivity();
}

void GameWidget::initWidget(){
    setWindowTitle("打字精英");
    installEventFilter(kb);
    setFixedSize(1200,800);

    auto minimap = new GameView(model,this);
    minimap->setGeometry(810,0,350,350);

    QTransform matrix;
    matrix.scale(0.33,0.33);
    minimap->setTransform(matrix);


    QPushButton *BackButton = new QPushButton("退出游戏",this);

    BackButton->move(810,600);

    connect(BackButton,&QPushButton::clicked,[=](){
        emit this->GameBack();
    });

    QTextBrowser *scoreLabel = new QTextBrowser(this);
    scoreLabel->setText("当前得分:\n");
    scoreLabel->move(810,370);
    connect(netSys,&NetworkSystem::scoreUpdateCommand,[model=this->model,scoreLabel](QString id, QString name, int score){
        auto &&playerScores = model->playerScores;
        playerScores[name]=score;
        QString now("当前得分\nid:分数\n");
        for(auto it=playerScores.begin();it!=playerScores.end();++it){
            now+=it.key();
            now+=": ";
            now+=QString::number(it.value());
            now+='\n';
        }
        scoreLabel->setText(now);
    });
}

void GameWidget::requestConnect(const QString &jwt)
{
    netSys->requestConnect(jwt);
}

void highLightPlayerName(QGraphicsTextItem *item,int highlightLen){
    QString s = item->toPlainText();
    item->setHtml(QString(R"(<span style="color:blue;font-size:35px;">%1</span><span style="color:red;font-size:30px;">%2</span>)")
                            .arg(s.left(highlightLen),s.right(s.size()-highlightLen)));
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
    auto p = new QGraphicsTextItem();
    p->setVisible(false);
    p->setData(0,id);
    p->setPlainText(name);
    highLightPlayerName(p,0);
    model->addItem(p);
    players[id] = p;
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
        view->centerOn(x,y);
        QVector<int> viewSize = ViewField(p->x(),p->y(),3);
        QPen pen;
        pen.setWidth(5);
        Horizon->setPen(pen);
        Horizon->setRect(viewSize[0]-4,viewSize[2]-2,viewSize[1]-viewSize[0]+50,viewSize[3]-viewSize[2]+50);
        Horizon->setVisible(true);
    }
}

void GameWidget::killPlayer(const QString &from,const QString &id)
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
    auto it = players.find(id);
    if(it==players.end()){
        qDebug()<<"player not found."<<id;
    }
    if(id==model->myId){
        model->myself=nullptr;
        if(Horizon){
            model->removeItem(Horizon);
        }
    }
    model->removeItem(it.value());
    delete it.value();
    players.erase(it);
}


QVector<int> GameWidget::ViewField(int x,int y,int n){
    int l = model->mapTextLayer.size()*50 -50;

    int left = x-50*n <0? 0:x-50*n;
    int right = x+50*n> l?l:x+50*n;
    int up = y-50*n < 0 ? 0:y-50*n;
    int down = y+50*n > l?l:y+50*n;
    return QVector<int>{left,right,up,down};
}


void GameWidget::hit(char c,QGraphicsTextItem *player_me,int n){
    flag+=c;
    qDebug()<<flag;
    QVector<int> size = ViewField(player_me->x(),player_me->y(),n);
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
                netSys->requestMove(text[i][j]->x(),text[i][j]->y());
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
    for(auto &&it:model->players){
        QString &&pt = it->toPlainText();
        int x = it->x();
        int y = it->y();
        if(it->data(0).toString()==model->myId||
                x<size[0]||x>size[1]||
                y<size[2]||y>size[3]){
            continue;
        }
        if(flag==pt){
            flag="";
            netSys->requestKill(it->data(0).toString());
            highLightPlayerName(it,flag.length());
            wu=false;
        }if(flag==it->toPlainText().mid(0,flag.length())){
            highLightPlayerName(it,flag.length());
            wu=false;
        }else{
            highLightPlayerName(it,0);
        }
    }

    if(wu){
        flag = c;
    }
}

void GameWidget::dispatchNetworkActivity()
{
    connect(netSys,&NetworkSystem::errorOccurred,this,&GameWidget::handleNetworkError);
    connect(kb,&KeyboardInput::goodKey,this,&GameWidget::handleGameInput);
    connect(netSys,&NetworkSystem::joinPlayerCommand, this, &GameWidget::joinPlayer);
    connect(netSys,&NetworkSystem::spawnPlayerCommand, this, &GameWidget::movePlayer);
    connect(netSys,&NetworkSystem::movePlayerCommand,this, &GameWidget::movePlayer);
    connect(netSys,&NetworkSystem::killPlayerCommand,this, &GameWidget::killPlayer);
    connect(netSys,&NetworkSystem::leavePlayerCommand,this,&GameWidget::leavePlayer);
    connect(netSys,&NetworkSystem::verifyCommand,this,&GameWidget::verified);
}

void GameWidget::handleNetworkError(){
    auto err = netSys->error();
    qDebug()<<err;
    QMessageBox *box;
    if(err==NetworkSystem::RemoteHostClosedError){
        box = new QMessageBox(QMessageBox::Critical,"服务器结束","此局游戏结束",QMessageBox::Ok);
    }else{
        box = new QMessageBox(QMessageBox::Critical,"网络错误","请重新连接",QMessageBox::Ok);
    }
    box->exec();
    emit GameBack();
}

void GameWidget::handleGameInput(int keyCode){
    auto player_me = model->myself;
    if(player_me==nullptr){
        return;
    }

    hit(keyCode-('A'-'a'),player_me,3);
}

void GameWidget::verified(const QString &id)
{
    model->myId=id;

}
