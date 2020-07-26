#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <vector>
#include "gui.h"
#include "actor.h"
#include "engine.h"

class Game
{
public:
    Engine *engine;
    bool running;
    std::vector<Actor> enemies;
    std::vector<Actor> players;
    Gui gui;

    Game(Engine *e);
    ~Game();
    void update();
    void render();
    void init();
    void initGui();
    void quit();
    void actorCreate();
    void actorDestroy();
};
#endif