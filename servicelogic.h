#ifndef SERVICELOGIC_H
#define SERVICELOGIC_H

#include <QVector>
#include <QString>
#include "player.h"
class ServiceLogic
{
public:
    ServiceLogic();
    QVector<int> StringMatch(QString InputText,Player player);   //获取输入框数据执行移动
    void SetMap(QVector<QVector<QString>> Map);
    QVector<QVector<QString>> getMap();
private:
    QVector<QVector<QString>> map;
};

#endif // SERVICELOGIC_H
