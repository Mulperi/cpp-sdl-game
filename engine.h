#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <string>
#include "gridhandler.h"

class Engine
{
public:
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Event event;
    int uptime;
    GridHandler gridHandler; 

    Engine();
    ~Engine();
    void init();
    bool processEvents();
    SDL_Texture *textureLoad(std::string path);
    void textureRender(SDL_Texture *texture);
    void textureDestroy(SDL_Texture *t);
};
#endif