#ifndef NETWORKSYSTEM_H
#define NETWORKSYSTEM_H

#include<QTcpSocket>

class NetworkSystem : public QObject {
    Q_OBJECT
public:
    static NetworkSystem *TcpNetworkSystemBuilder(const QString &host, const int port, QObject *parent);
    static NetworkSystem *WebsocketNetworkSystemBuilder(const QString &url, QObject *parent);

    std::function<QAbstractSocket::SocketError()> error;

    std::function<void (const QString &playerID)>requestConnect;
    std::function<void (const QString &playerID)>requestKill;
    std::function<void (int x,int y)>requestMove;

signals:
    void errorOccurred();
    void verifyCommand(QString playerId);
    void joinPlayerCommand(QString playerId,QString playerName);
    void spawnPlayerCommand(QString playerId,int x,int y);
    void movePlayerCommand(QString playerId,int x,int y);
    void killPlayerCommand(QString from,QString to);
    void leavePlayerCommand(QString playerId);
    void scoreUpdateCommand(QString playerId, QString playerName, int score);
    void remainingTimeUpdate(int remainTime);

private:
    void packageIntepreterMain(const QString &pkg);
    explicit NetworkSystem(QObject *parent = nullptr);
};

#endif // NETWORKSYSTEM_H
