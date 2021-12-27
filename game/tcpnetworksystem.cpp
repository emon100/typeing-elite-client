#include <QString>
#include <QByteArray>

#include "networksystem.h"

NetworkSystem *NetworkSystem::TcpNetworkSystemBuilder(const QString &host, const int port, QObject *parent) {
    NetworkSystem *netsys = new NetworkSystem(parent);
    QTcpSocket *socket = new QTcpSocket(netsys);

    QString *having = new QString();
    connect(socket, &QTcpSocket::readyRead, netsys, [having, netsys, socket](){
        QString &Having = *having;
        Having+= QString(socket->readAll());
        QStringList list = Having.split("\n");
        int sz = list.size();
        if(sz>1){
            for(int i=0;i<sz-1;i++){
                netsys->packageIntepreterMain(list[i]);
            }
            Having = list.back();
        }
    });
    connect(socket, &QTcpSocket::errorOccurred, netsys, &NetworkSystem::errorOccurred);

    netsys->error = [socket](){
        return socket->error();
    };

    netsys->requestConnect = [socket](const QString &playerID) {
        socket->write(playerID.toUtf8().data());
        socket->write("\n",1);
    };

    netsys->requestMove = [socket](int x, int y) {
        socket->write(QString("MOVE %1 %2\n").arg(x).arg(y).toUtf8());
    };

    netsys->requestKill = [socket](const QString &playerID) {
        socket->write(QString("KILL %1\n").arg(playerID).toUtf8());
    };

    QObject::connect(netsys, &QObject::destroyed, [having](){
        delete having;
    });

    socket->connectToHost(host, port);

    return netsys;
}
