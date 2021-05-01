#include <QString>
#include "networksystem.h"
#include <QByteArray>

NetworkSystem::NetworkSystem(const QString &host, const int port, QObject *parent) :
    QTcpSocket(parent)
{
    this->connectToHost(host,port);
    connect(this,&QTcpSocket::readyRead,[this](){
        GetToken(QString(this->readAll()));
    });
}

void NetworkSystem::requestConnect(const QString &playerID, const QString &)
{
    write(playerID.toLatin1().data());
    write("\n",1);
}

void NetworkSystem::requestMove(int x, int y)
{
    write(QString("%2,%3\n").arg(x).arg(y).toLatin1());
}

void NetworkSystem::packageIntepreterMain(const QString &msg)
{//TODO: interpreter
    qDebug()<<"NetworkSystem: "<<msg;
    auto sl =  msg.split(':');
    if(sl.size()<2){
        return;
    }
    auto &&sender = sl[0];
    auto &&instruction = sl[1];
    if(instruction.contains("Hello")){
        auto pos = instruction.split(' ')[1].split(',');
        emit addPlayerCommand(sender, sender, pos[0].toInt(),pos[1].toInt());
    }else if (instruction.contains("left")){
       //TODO: emit deletePlayer(sender);
    }else{
        auto pos = instruction.split(',');
        emit movePlayerCommand(sl[0],pos[0].toInt(),pos[1].toInt());
    }
}

void NetworkSystem::GetToken(const QString &get){
    Having+=get;
    QStringList list = Having.split("\n");
    int sz = list.size();
    if(sz>1){
        for(int i=0;i<sz-1;i++){
            packageIntepreterMain(list[i]);
        }
        Having = list.back();
    }
}
