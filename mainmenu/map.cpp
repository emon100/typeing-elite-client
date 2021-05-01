#include "map.h"

Map::Map(int mapSize)
{
    map = QVector<QVector<QString>>(mapSize, QVector<QString>(mapSize));
}

QString Map::getRandomString(unsigned seed, int minLength, int maxLength) {
    srand(seed);
    QString s;
    for (int i = 0; i < rand() % (maxLength - minLength) + minLength; i++) {
        s += char(rand() % 26 + 'a');
    }
    return s;
}


QVector<QVector<QString>> Map::getMap(){
    return map;
}

void Map::setMap(const QVector<QVector<QString>> &new_map){
    map = new_map;
}

void Map::iniRandomMap(){

    int size = map.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            QTime current_time = QTime::currentTime();
            int msec = current_time.msec();        //当前的毫秒
            map[i][j] = getRandomString(msec + i * 10 + j);
        }
    }
}
