#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <cstdio>
#include "game.h"
#include "gui.h"
#include "engine.h"

Game::Game(Engine *e)
{
    printf("Game constructor called.\n");
    engine = e;
    running = true;
}

Game::~Game()
{
    printf("Game destructor called.\n");
    // engine = NULL;
}

void Game::update()
{
    running = engine->processEvents();
}

void Game::render()
{
    // Clear screen.
    SDL_SetRenderDrawColor(engine->renderer, 0, 0, 255, 255);
    SDL_RenderClear(engine->renderer);

    SDL_Rect rect = {0, 0, 100, 100};
    SDL_SetRenderDrawColor(engine->renderer, 255, 0, 255, 255);
    SDL_RenderFillRect(engine->renderer, &rect);

    // Gui.
    // gui.render();

    // Render.
    SDL_RenderPresent(engine->renderer);
}
void Game::quit()
{
    // engine = nullptr;
}