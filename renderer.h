#include <SDL2/SDL.h>

class Renderer
{
public:
    SDL_Renderer *renderer;

    Renderer();
    ~Renderer();
    rendererSet(SDL_Renderer *r);
};