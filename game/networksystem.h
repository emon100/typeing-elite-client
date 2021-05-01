#ifndef NETWORKSYSTEM_H
#define NETWORKSYSTEM_H

#include <QObject>

class QString;
class Network;

class NetworkSystem : public QObject
{
    Q_OBJECT

    Network *client;
    void packageIntepreterMain(const QString &pkg);

public:
    explicit NetworkSystem(Network *client, QObject *parent = nullptr);

    void requestConnect(const QString &playerID, const QString &playerName) const;
    void requestMove(int x,int y);


signals:
    void addPlayerCommand(QString playerId,QString playerName,int x,int y);
    void movePlayerCommand(QString playerId,int x,int y);

};

#endif // NETWORKSYSTEM_H
