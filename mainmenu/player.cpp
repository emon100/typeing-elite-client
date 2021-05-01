#include "player.h"

Player::Player()
{
    StepLength = 1;
    X = 3;
    Y = 3;
    Blood = 100;
}
int Player::getStepLength(){return StepLength;}
int Player::getX(){return X;}
int Player::getY(){return Y;}
void Player::setX(int x){X=x;}
void Player::setY(int y){Y=y;}
