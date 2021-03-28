#include "networkio.h"
#include <QtNetwork>

NetWorkIO::NetWorkIO(QObject *parent) : QObject(parent),
   client(new QTcpSocket(this))
{
    client->connectToHost("localhost",8888);
}
