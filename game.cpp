#include "main.h"

Game::Game()
{
    printf("Game constructor called.\n");
    SDL_Init(SDL_INIT_VIDEO);
    // Uint32 window_flags = SDL_WINDOW_ALLOW_HIGHDPI;
    window = NULL;
    renderer = NULL;
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    running = 1;
}
Game::~Game()
{
    printf("Game deconstructor called.\n");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
void Game::processEvents()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = 0;
            break;

        default:
            break;
        }
    }
}
void Game::update()
{
    processEvents();
}
void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect = {0, 0, 100, 100};
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}
