#include "gamemodel.h"
#include <QVector>
#include <QString>
#include <QRandomGenerator>

void GameModel::makeMap()
{
    addBackground();
    addItemsGroups();
}

void GameModel::addBackground()
{

}

void GameModel::addItemsGroups()
{
    const int N=20;
    const int min_len = 3;
    const int max_len = 7;
    auto & map = mapTextLayer;
    map.reserve(N);
    for(int i=0;i<N;++i){
        map.push_back(QVector<QGraphicsSimpleTextItem *>());
        map.back().reserve(N);
        for(int j=0;j<N;++j){
            QString s;
            int generated_len=QRandomGenerator::global()->bounded(min_len,max_len);
            for(int k=0;k<generated_len;++k){
                int i=QRandomGenerator::global()->bounded(26);
                s.push_back(static_cast<QChar>('a'+i));
            }
            auto item = this->addSimpleText(s);
            item->setPos(i*50,j*50);
            map.back().push_back(item);
        }
    }
}

GameModel::GameModel(QObject *parent) : QGraphicsScene(parent){
    makeMap();
}
