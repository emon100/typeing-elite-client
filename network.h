#ifndef NETWORK_H
#define NETWORK_H

#include<QTcpSocket>

class Network : public QTcpSocket
{
Q_OBJECT
public:
    Network(const QString &host, const int port, QObject *p=nullptr);

private:
    void GetToken(const QString &get);
    QString Having;
signals:
    void OK(QString Get_ok);
};

#endif // NETWORK_H
