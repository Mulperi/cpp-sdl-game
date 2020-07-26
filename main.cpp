#include <iostream>
#include <ctime>
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "engine.h"
#include "game.h"

/**
 * Mac install: brew install sdl2
 * Mac compile: g++ main.cpp game.cpp utils.cpp grid.cpp text.cpp actor.cpp gui.cpp engine.cpp -I/usr/local/include -L/usr/local/lib -lSDL2 -lSDL2_ttf -lSDL2_image -o main
 **/
int main(int argc, char *argv[])
{
    Engine engine;
    Game game(&engine);
    while (game.running)
    {
        game.update();
        game.render();
    }
    return EXIT_SUCCESS;
}
