#ifndef SERVICELOGIC_H
#define SERVICELOGIC_H

#include <QVector>
#include <QString>
class ServiceLogic
{
public:
    ServiceLogic();
    void SetMap(QVector<QVector<QString>> Map);
    QVector<QVector<QString>> getMap();
private:
    QVector<QVector<QString>> map;
};

#endif // SERVICELOGIC_H
