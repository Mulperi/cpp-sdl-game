#include "actor.h"

Actor::Actor()
{
    rect.w = 16;
    rect.h = 16;
    rect.x = 100;
    rect.y = 100;
}
Actor::~Actor() {}
void Actor::render() {}
void Actor::update() {}