#include "gamemap.h"

GameMap::GameMap(const int N){    //Generate random map by N
    const int min_len = 3;
    const int max_len = 10;
    map.reserve(N);
    for(int i=0;i<N;++i){
        map.push_back(QVector<QString>());
        map.back().reserve(N);
        for(int j=0;j<N;++j){
            map.back().push_back(QString());
            QString &s = map.back().back();

            s.reserve(max_len);

            int generated_len=QRandomGenerator::global()->bounded(min_len,max_len);
            for(int k=0;k<generated_len;++k){
                int i=QRandomGenerator::global()->bounded(26);
                s.push_back(static_cast<QChar>('a'+i));
            }
        }
    }
}

QString GameMap::getRandomString(unsigned seed, int minLength, int maxLength) {
    srand(seed);
    QString s;
    for (int i = 0; i < rand() % (maxLength - minLength) + minLength; i++) {
        s += char(rand() % 26 + 'a');
    }
    return s;
}


QVector<QVector<QString>> GameMap::getMap(){
    return map;
}

void GameMap::setMap(const QVector<QVector<QString>> &new_map){
    map = new_map;
}

void GameMap::iniRandomMap(){

    int size = map.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            QTime current_time = QTime::currentTime();
            int msec = current_time.msec();        //当前的毫秒
            map[i][j] = getRandomString(msec + i * 10 + j);
        }
    }
}
