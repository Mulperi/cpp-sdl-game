#ifndef ACTOR_H
#define ACTOR_H
#include <SDL2/SDL.h>
#include <string>

class Actor
{
public:
    int type;
    std::string name;
    SDL_Rect rect;

    Actor();
    ~Actor();
    int getCenterX();
    int getCenterY();
};
#endif