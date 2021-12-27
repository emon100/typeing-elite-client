#include "networksystem.h"
#include <QString>
#include <QByteArray>
#include <QtWebSockets/QWebSocket>

NetworkSystem *NetworkSystem::WebsocketNetworkSystemBuilder(const QString &url, QObject *parent)
{
    NetworkSystem *sys = new NetworkSystem(parent);
    QWebSocket *socket = new QWebSocket();
    socket->setParent(sys);

    connect(socket, &QWebSocket::textMessageReceived,
            sys, &NetworkSystem::packageIntepreterMain);

    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), sys, &NetworkSystem::errorOccurred);
    sys->requestConnect = [socket](const QString & id){ socket->sendTextMessage(id);};
    sys->requestMove = [socket](int x, int y) {
        socket->sendTextMessage(QString("MOVE %1 %2\n").arg(x).arg(y));
    };
    sys->requestKill =  [socket](const QString &playerID) {
        socket->sendTextMessage(QString("KILL %1\n").arg(playerID));
    };

    socket->open(url);
    return sys;
}

/*
WebsocketNetworkSystem::WebsocketNetworkSystem(const QString &host, const int port, QObject *parent) :
   NetworkSystem(parent),
   socket(new QWebSocket())
{
    socket->setParent(this);
    socket->open(QString("ws://%1:%2").arg(host).arg(port));
    connect(socket, &QWebSocket::textMessageReceived,
            this, &WebsocketNetworkSystem::packageIntepreterMain);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, [this](){
      emit errorOccurred();
    });
}

void WebsocketNetworkSystem::requestConnect(const QString &playerID)
{
    socket->sendTextMessage(playerID.toUtf8().data());
}

void  WebsocketNetworkSystem::requestMove(int x, int y)
{
    socket->sendTextMessage(QString("MOVE %2 %3\n").arg(x).arg(y));
}

void  WebsocketNetworkSystem::requestKill(const QString &playerID)
{
    socket->sendTextMessage(QString("KILL %1\n").arg(playerID));
}

QAbstractSocket::SocketError WebsocketNetworkSystem::error(){
    return socket->error();
}
*/
