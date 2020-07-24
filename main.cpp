#include "main.h"

/**
 * Mac install: brew install sdl2
 * Mac compile: g++ main.cpp game.cpp utils.cpp -o main -I/usr/local/include -L/usr/local/lib -lSDL2
 **/
int main(int argc, char *argv[])
{
    Game game;
    while (game.running)
    {
        game.render();
        game.update();
        SDL_Delay(1000 / 60);
    }

    return EXIT_SUCCESS;
}