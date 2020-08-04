#include "actor.h"

Actor::Actor()
{
    rect.w = 16;
    rect.h = 16;
    rect.x = 100;
    rect.y = 100;
}
Actor::~Actor() {}
int Actor::getCenterX()
{
    return rect.x + rect.w / 2;
}
int Actor::getCenterY()
{
    return rect.y + rect.h / 2;
}
