#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <vector>
#include "gui.h"
#include "actor.h"
#include "engine.h"
#include "logger.h"
#include "tile.h"
#include "grid.h"

class Game
{
public:
    Mulperi2D *engine;
    Logger *logger;
    bool running;
    std::vector<Actor> enemies;
    std::vector<Actor> players;
    Gui gui;
    // Grid grid;

    Game(Mulperi2D *e, Logger *l);
    ~Game();
    void update();
    void render();
    void renderGridTiles(int type);
    void renderGridLines();
    void renderGridWalls();
    void renderGridEdges();
    void renderPlayers();
    void renderPlayerRayCast();


    // void init();
    // void initGui();
    void quit();
};
#endif