#include "network.h"

Network::Network(const QString &host, const int port, QObject *parent):
    QTcpSocket(parent)
{
    this->connectToHost(host,port);
    connect(this,&QTcpSocket::connected,[](){
        qDebug()<<"connected";
    });
    connect(this,&QTcpSocket::errorOccurred,[](const QAbstractSocket::SocketError &error){
        qDebug()<<error;
    });
    connect(this,&QTcpSocket::readyRead,[this](){
        GetToken(QString(this->readAll()));
    });
}

void Network::GetToken(const QString &get){
    Having+=get;
    QStringList list = Having.split("\n");
    int sz = list.size();
    if(sz>1){
        for(int i=0;i<sz-1;i++){
            emit this->OK(list[i]);
        }
        Having = list.back();
    }
}
