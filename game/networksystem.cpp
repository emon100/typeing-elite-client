#include "networksystem.h"

NetworkSystem::NetworkSystem(QObject *parent):QObject(parent) { }

void NetworkSystem::packageIntepreterMain(const QString &msg)
{
    qDebug()<<"NetworkSystem: "<<msg;
    auto sl =  msg.split(':');
    if(sl.size()<2){
        return;
    }
    auto &&target = sl[0];
    auto &&instructions = sl[1].split(' ');
    if(instructions[0]=="VERIFY"){
        emit verifyCommand(instructions[1]);
    }else if(instructions[0]=="JOIN"){
        emit joinPlayerCommand(target, instructions[1]);
    }else if (instructions[0] =="SPAWN"){
        emit spawnPlayerCommand(target, instructions[1].toInt(),instructions[2].toInt());
    }else if(instructions[0]=="MOVE"){
        emit movePlayerCommand(sl[0],instructions[1].toInt(),instructions[2].toInt());
    }else if (instructions[0] =="KILL"){
        emit killPlayerCommand(target,instructions[1]);
    }else if (instructions[0] =="LEAVE"){
        emit leavePlayerCommand(target);
    }else if (instructions[0] =="NOWSCORE"){
        emit scoreUpdateCommand(target, instructions[1],instructions[2].toInt());
    }else if(instructions[0] =="REMAININGTIME"){
        emit remainingTimeUpdate(instructions[1].toInt());
    }else{
        qDebug()<<"Bad msg: "<<msg;
    }
}
