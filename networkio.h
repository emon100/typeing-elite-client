#ifndef NETWORKIO_H
#define NETWORKIO_H

#include <QObject>
class QTcpSocket;

class NetWorkIO : public QObject
{
    Q_OBJECT
public:
    explicit NetWorkIO(QObject *parent = nullptr);
    QTcpSocket *client;

signals:

};

#endif // NETWORKIO_H
