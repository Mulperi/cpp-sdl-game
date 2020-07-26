#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>
#include "engine.h"

Engine::Engine()
{
    printf("Engine constructor.\n");
    uptime = 1;
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();

    // Uint32 window_flags = SDL_WINDOW_ALLOW_HIGHDPI;
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window)
        printf("%s\n", SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
        printf("%s\n", SDL_GetError());
}
Engine::~Engine()
{
    printf("Engine destructor.\n");

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
bool Engine::processEvents()
{
    printf("process events\n");
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return false;
            break;

        default:
            break;
        }
    }
    return true;
}
SDL_Texture *Engine::textureLoad(std::string path)
{
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}
void Engine::textureDestroy(SDL_Texture *t)
{
    SDL_DestroyTexture(t);
}