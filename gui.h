#ifndef GUI_H
#define GUI_H
#include <SDL2/SDL.h>
#include "text.h"

class Gui
{
public:
    Text menuPlay;
    Text menuQuit;
    SDL_Renderer *renderer;

    Gui();
    ~Gui();
    void init(SDL_Renderer *r);
    void render();
    void update();
};

#endif