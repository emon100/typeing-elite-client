#ifndef PLAYER_H
#define PLAYER_H
#include <QString>

class Player
{
public:
    Player();
    int getStepLength();
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
private:
    int X,Y;
    int Blood;
    QString Name;
    int StepLength;
};

#endif // PLAYER_H
