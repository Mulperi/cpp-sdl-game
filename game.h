#include "SDL2/SDL.h"

class Game
{
public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    int running;

    Game();
    ~Game();
    void processEvents();
    void update();
    void render();
    void init();
    void quit();
};