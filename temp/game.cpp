#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <math.h>
#include <string>
#include <iostream>
#include <cstdio>
#include "game.h"
#include "gui.h"
#include "engine.h"
#include "utils.h"

Game::Game(Cheesy2D *e, Logger *l) //: grid(e->config.screenHeight / e->config.tileSize, e->config.screenWidth / e->config.tileSize, e->config.tileSize)
{
    engine = e;
    logger = l;
    running = true; // Needs to be initialized true, otherwise will not go in the game loop.
    if (logger->active)
        logger->log("LOG: Game constructor.\n");

    Actor p1;
    p1.name = "jorma";
    players.push_back(p1);
}

Game::~Game()
{
    if (logger->active)
        logger->log("LOG: Game destructor called.\n");
}

void Game::update()
{
    running = engine->processEvents();
}

void Game::render()
{
    // Clear screen.
    SDL_SetRenderDrawColor(engine->renderer, 0, 0, 0, 255);
    SDL_RenderClear(engine->renderer);

    // Gui.
    // gui.render();

    // Grid.
    renderGridWalls();
    renderGridLines();

    // Players
    renderPlayers();
    renderGridEdges();
    renderPlayerRayCast();

    // Render all above.
    SDL_RenderPresent(engine->renderer);
}
void Game::renderPlayers()
{
    // for (size_t i = 0; i < players.size(); i++)
    // {
    //     SDL_Rect rect = {100, 100, grid.tileSize, grid.tileSize};
    //     SDL_SetRenderDrawColor(engine->renderer, 100, 255, 255, 255);
    //     SDL_RenderFillRect(engine->renderer, &rect);
    // }
}
void Game::renderPlayerRayCast()
{

    // for (auto &it : grid.edgeMap)
    // {
    //     // SDL_SetRenderDrawColor(engine->renderer, 255, 0, 255, 255);
    //     // SDL_RenderDrawLine(
    //     //     engine->renderer,
    //     //     players[0].getCenterX(), players[0].getCenterY(),
    //     //     it.second.start.x, it.second.start.y);
    //     // SDL_RenderDrawLine(
    //     //     engine->renderer,
    //     //     players[0].getCenterX(), players[0].getCenterY(),
    //     //     it.second.end.x, it.second.end.y);
    // }
}
void Game::renderGridTiles(int type)
{
    // for (int y = 0; y < grid.gridSizeY; y++)
    // {
    //     for (int x = 0; x < grid.gridSizeX; x++)
    //     {
    //         if (grid.matrix[y][x].typeGet() == type)
    //         {
    //             SDL_Rect rect = {x * grid.tileSize, y * grid.tileSize, grid.tileSize, grid.tileSize};
    //             SDL_SetRenderDrawColor(engine->renderer, 100, 100, 100, 255);
    //             SDL_RenderFillRect(engine->renderer, &rect);
    //         }
    //     }
    // }
}
void Game::renderGridWalls()
{
    // for (size_t i = 0; i < grid.walls.size(); i++)
    // {
    //     SDL_Rect rect = {grid.walls[i]->positionGetX(), grid.walls[i]->positionGetY(), grid.tileSize, grid.tileSize};
    //     SDL_SetRenderDrawColor(engine->renderer, 100, 100, 100, 255);
    //     SDL_RenderFillRect(engine->renderer, &rect);
    // }
}
void Game::renderGridLines()
{
    // for (int y = 0; y < grid.gridSizeY; y++)
    // {
    //     for (int x = 0; x < grid.gridSizeX; x++)
    //     {
    //         SDL_Rect rect = {x * grid.tileSize, y * grid.tileSize, grid.tileSize, grid.tileSize};
    //         SDL_SetRenderDrawColor(engine->renderer, 50, 50, 50, 255);
    //         SDL_RenderDrawRect(engine->renderer, &rect);
    //     }
    // }
}
void Game::renderGridEdges()
{
    // Edge count.
    // printf("%lu\n", grid.edgeMap.size());

    // for (auto &it : grid.edgeMap)
    // {
    //     SDL_SetRenderDrawColor(engine->renderer, 0, 255, 255, 255);
    //     SDL_RenderDrawLine(
    //         engine->renderer,
    //         it.second.start.x,
    //         it.second.start.y,
    //         it.second.end.x,
    //         it.second.end.y);

    //     SDL_SetRenderDrawColor(engine->renderer, 255, 0, 0, 255);
    //     SDL_Rect start = {it.second.start.x - 2,
    //                       it.second.start.y - 2, 4, 4};
    //     SDL_Rect end = {it.second.end.x - 2,
    //                     it.second.end.y - 2, 4, 4};
    //     SDL_RenderFillRect(
    //         engine->renderer,
    //         &start);
    //     SDL_RenderFillRect(
    //         engine->renderer,
    //         &end);

        // std::cout << it.first << it.second << std::endl;;// << ":" << it.second << std::endl;}
    // }
}
void Game::quit()
{
}
