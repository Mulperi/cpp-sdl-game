#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>
#include "engine.h"

MulperiEngine::MulperiEngine(MulperiEngine_Config conf)
{
    config = conf;
    running = true;

    grid.init(config.screenHeight / config.tileSize, config.screenWidth / config.tileSize, config.tileSize);

    logger.active = config.log;
    if (logger.active)
        logger.log("LOG: Engine constructor.");

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();

    // Uint32 window_flags = SDL_WINDOW_ALLOW_HIGHDPI;
    window = SDL_CreateWindow(config.title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, config.screenWidth, config.screenHeight, SDL_WINDOW_SHOWN);
    if (!window)
        printf("%s\n", SDL_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
        printf("%s\n", SDL_GetError());
}
MulperiEngine::~MulperiEngine()
{
    if (logger.active)
        logger.log("LOG: Engine destructor.");

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
bool MulperiEngine::processEvents()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            return false;
            break;

        default:
            break;
        }
    }
    return true;
}
void MulperiEngine::update()
{
    processEvents();
}
void MulperiEngine::render()
{

    // Clear screen.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render grid walls.
    for (size_t i = 0; i < grid.walls.size(); i++)
    {
        SDL_Rect rect = {grid.walls[i]->positionGetX(), grid.walls[i]->positionGetY(), grid.tileSize, grid.tileSize};
        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderFillRect(renderer, &rect);
    }

    if (debug)
    {
        // Render grid lines.
        for (int y = 0; y < grid.gridSizeY; y++)
        {
            for (int x = 0; x < grid.gridSizeX; x++)
            {
                SDL_Rect rect = {x * grid.tileSize, y * grid.tileSize, grid.tileSize, grid.tileSize};
                SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
    }

    // Render grid edges
    for (auto &it : grid.edgeMap)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderDrawLine(
            renderer,
            it.second.start.x,
            it.second.start.y,
            it.second.end.x,
            it.second.end.y);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect start = {it.second.start.x - 4,
                          it.second.start.y - 4, 8, 8};
        SDL_Rect end = {it.second.end.x - 4,
                        it.second.end.y - 4, 8, 8};
        SDL_RenderFillRect(
            renderer,
            &start);
        SDL_RenderFillRect(
            renderer,
            &end);
    }

    // Render all above.
    SDL_RenderPresent(renderer);
}
void MulperiEngine::run(bool debugModeActive)
{
    debug = debugModeActive;
    running = true;
    while (running)
    {
        update();
        render();
        sleep(1000 / config.fps);
    }
}
void MulperiEngine::stop()
{
    running = false;
}
void MulperiEngine::sleep(Uint32 ms)
{
    SDL_Delay(ms);
}

SDL_Texture *MulperiEngine::textureLoad(std::string path)
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
void MulperiEngine::textureDestroy(SDL_Texture *t)
{
    SDL_DestroyTexture(t);
}
