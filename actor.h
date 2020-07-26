#ifndef ACTOR_H
#define ACTOR_H
#include <SDL2/SDL.h>

class Actor
{
public:
    int type;
    SDL_Texture *texture;
    SDL_Rect rect;

    Actor();
    ~Actor();
    void update();
    void render();
};
#endif