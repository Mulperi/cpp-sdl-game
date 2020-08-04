#include <iostream>
#include <ctime>
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "engine.h"

/**
 * Mac install: brew install sdl2
 * Mac compile: g++ -std=c++11 main.cpp -I/usr/local/include -L/usr/local/lib -lSDL2 -lSDL2_ttf -lSDL2_image -o main
 **/
int main(int argc, char *argv[])
{
    MulperiEngine_Config conf = {"Game Title", 640, 480, 16, false, true, 60};
    MulperiEngine myGame(conf);
    myGame.CreateActor("assets/player.png", 100, 100, 32, 32);
    myGame.Run(false);


    return EXIT_SUCCESS;
}
