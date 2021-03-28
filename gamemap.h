#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QVector>
#include <QString>
#include <QTime>
#include <QRandomGenerator>

class GameMap
{
public:
    GameMap(int mapSize);
    QVector<QVector<QString>> getMap();
    void setMap(const QVector<QVector<QString>> &new_map);
    void iniRandomMap();


private:
    QVector<QVector<QString>> map;
    QString getRandomString(unsigned seed, int minLength = 3, int maxLength = 8);
};

#endif // GAMEMAP_H
