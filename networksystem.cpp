#include "networksystem.h"
#include "network.h"

NetworkSystem::NetworkSystem(Network *c, QObject *parent) :
    QObject(parent),
    client(c)
{
    connect(client,&Network::OK,this,&NetworkSystem::packageIntepreterMain);
}

void NetworkSystem::requestConnect(const QString &playerID, const QString &) const
{
    client->write(playerID.toLatin1());
    client->write("\n");
}

void NetworkSystem::requestMove(int x, int y)
{
    client->write(QString("%2,%3\n").arg(x).arg(y).toLatin1());
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
