#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

/**
 *  MulperiEngine 
 *  By Mika Mulperi Lakanen
 *  www.mulperi.net
 * */

/**
 * Configuration model and enums.
 * */
typedef struct MulperiEngine_Config
{
    string title;
    int screenWidth;
    int screenHeight;
    int tileSize;
    bool fullScreen;
    bool log;
    int fps;
} MulperiEngine_Config;

typedef struct MulperiEngine_CellEdge
{
    SDL_Point start;
    SDL_Point end;
    // unordered_map<string *, Tile> tileMap;
} MulperiEngine_CellEdge;

typedef struct MulperiEngine_CellEdgeExistData
{
    string edgeIds[4];
    bool edgesExist[4]; // North, South, East, West.
    bool exist;
    string id;
} MulperiEngine_CellEdgeExistData;

enum ACTOR_TYPES
{
    ACTOR_TYPE_PLAYER,
    ACTOR_TYPE_ENEMY
};

/**
 * For handling and generating 2d grid maps.
 * */
enum EDGES
{
    EDGE_TOP,
    EDGE_RIGHT,
    EDGE_BOTTOM,
    EDGE_LEFT
};

// Constants.
#define PI 3.14159265359;

// Utility functions
int randomNumberGet(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

float radiansToAngle(float radians)
{
    return radians * 180 / PI
}

/**
 *  Tile class for individual blocks in the grid.
 *  Tiles are either empty space or solid walls that can be destroyed.
 * */
class Tile
{
public:
    SDL_Point pos;
    int type;
    float hp;
    MulperiEngine_CellEdgeExistData cell;

    Tile()
    {
        type = 0;
        hp = 0;
    };
    Tile(int tileType)
    {
        type = tileType;
        hp = 100;
    };
    ~Tile(){};
    int typeGet()
    {
        return type;
    };
    void typeSet(int t)
    {
        type = t;
    };
    float hpGet()
    {
        return hp;
    };
    void hpSet(float h)
    {
        hp = h;
    };
    void positionSet(int y, int x)
    {
        pos.y = y;
        pos.x = x;
    };
    int positionGetX()
    {
        return pos.x;
    };
    int positionGetY()
    {
        return pos.y;
    };
    void hpDecrease(float amount)
    {
        hp -= amount;
    };
};

class MulperiEngine_GridHandler
{
public:
    MulperiEngine_GridHandler()
    {
        printf("LOG: Gridhandler constructor.\n");
    };
    ~MulperiEngine_GridHandler()
    {
        printf("LOG: Gridhandler destructor.\n");
    };
    void generate(int sx, int sy, int interations);
    vector<vector<char>> fileRead(string path, int sizeY, int sizeX)
    {

        if (!sizeY || !sizeX)
            printf("ERROR: Gridhandler: Check grid Y and X length!\n");

        cout << "LOG: Gridhandler fileread: " << path << endl;

        vector<vector<char>> grid(sizeY, vector<char>(sizeX, 0));
        FILE *fp;
        fp = fopen(path.c_str(), "r");
        rewind(fp);
        for (int y = 0; y < sizeY; y++)
        {

            for (int x = 0; x < sizeX; x++)
            {

                char c = fgetc(fp);
                if (c == EOF)
                {
                    // Should not come here.
                    printf("\nError: EOF\n");
                }
                if (c == '\n')
                {
                    c = fgetc(fp);
                }

                grid[y][x] = c;
            }
        }

        cout << "LOG: " << path << " read finished." << endl;

        if (fclose(fp) == 0)
        {
            cout << "LOG: " << path << " closed." << endl;
        }
        else
        {
            cout << "LOG: " << path << "close failed." << endl;
        }
        return grid;
    };
    void print(vector<vector<char>>, int sizeY, int sizeX);
};

class MulperiEngine_Grid
{
public:
    MulperiEngine_GridHandler *gridHandler;
    int gridSizeY;
    int gridSizeX;
    int tileSize;
    vector<vector<Tile>> matrix;
    vector<Tile *> walls;
    unordered_map<string, MulperiEngine_CellEdge> edgeMap;

    // vector<vector<EdgeCell> > edgeCells;

    MulperiEngine_Grid()
    {
        printf("LOG: Grid constructor.\n");
    };
    ~MulperiEngine_Grid()
    {
        printf("LOG: Grid destructor.\n");
    };
    void init(int lengthY, int lengthX, int size)
    {
        // Init grid size and load tile information.
        gridSizeY = lengthY;
        gridSizeX = lengthX;
        tileSize = size;
        matrix = tilesConvert(gridHandler->fileRead("map.txt", gridSizeY, gridSizeX));
        tilesWallsGet(matrix);
        edgeCellsExistCheck();
        edgeCellsCheck();
    };
    vector<vector<Tile>> tilesConvert(vector<vector<char>> charGrid)
    {
        vector<vector<Tile>> tileGrid(30, vector<Tile>(40, 0));
        for (int y = 0; y < gridSizeY; y++)
        {
            for (int x = 0; x < gridSizeX; x++)
            {
                // Assume grid made of numbers.
                tileGrid[y][x].typeSet((int)charGrid[y][x] - 48);
                tileGrid[y][x].positionSet(y * tileSize, x * tileSize);
                tileGrid[y][x].cell.edgesExist[EDGE_TOP] = false;
                tileGrid[y][x].cell.edgesExist[EDGE_RIGHT] = false;
                tileGrid[y][x].cell.edgesExist[EDGE_BOTTOM] = false;
                tileGrid[y][x].cell.edgesExist[EDGE_LEFT] = false;

                // If not empty, the tile "cell" exists and will cut rays.

                tileGrid[y][x].cell.exist = false;
            }
        }
        return tileGrid;
    };
    void tilesWallsGet(vector<vector<Tile>> tileGrid)
    {
        for (int y = 0; y < 30; y++)
        {
            for (int x = 0; x < 40; x++)
            {
                if (tileGrid[y][x].typeGet() == 1)
                    walls.push_back(&matrix[y][x]);
            }
        }
    };
    void edgeCellsCheck()
    {
        for (int y = 0; y < gridSizeY; y++)
        {
            for (int x = 0; x < gridSizeX; x++)
            {
                // Cell exist, need to check if it needs edges
                if (matrix[y][x].cell.exist)
                {
                    // Neighbours
                    Tile *current = &matrix[y][x];
                    Tile *top = y > 0 ? &matrix[y - 1][x] : NULL;
                    Tile *right = x < gridSizeX ? &matrix[y][x + 1] : NULL;
                    Tile *bottom = y < gridSizeY ? &matrix[y + 1][x] : NULL;
                    Tile *left = x > 0 ? &matrix[y][x - 1] : NULL;

                    if (top)
                    {
                        if (!top->cell.exist)
                        {
                            if (left)
                            {
                                if (left->cell.edgesExist[EDGE_TOP])
                                {
                                    edgeMap[left->cell.edgeIds[EDGE_TOP]].end.x += tileSize;
                                    current->cell.edgeIds[EDGE_TOP] = left->cell.edgeIds[EDGE_TOP];
                                    current->cell.edgesExist[EDGE_TOP] = true;
                                }
                                else
                                {
                                    string id = to_string(y).append(to_string(x)).append("-").append(to_string(EDGE_TOP));
                                    edgeMap[id].start.x = current->pos.x;
                                    edgeMap[id].start.y = current->pos.y;
                                    edgeMap[id].end.x = current->pos.x + tileSize;
                                    edgeMap[id].end.y = current->pos.y;
                                    current->cell.edgesExist[EDGE_TOP] = true;
                                    current->cell.edgeIds[EDGE_TOP] = id;
                                }
                            }
                        }
                    }
                    if (right)
                    {
                        if (!right->cell.exist)
                        {
                            if (top)
                            {
                                if (top->cell.edgesExist[EDGE_RIGHT])
                                {
                                    edgeMap[top->cell.edgeIds[EDGE_RIGHT]].end.y += tileSize;
                                    current->cell.edgeIds[EDGE_RIGHT] = top->cell.edgeIds[EDGE_RIGHT];
                                    current->cell.edgesExist[EDGE_RIGHT] = true;
                                }
                                else
                                {
                                    string id = to_string(y).append(to_string(x)).append("-").append(to_string(EDGE_RIGHT));
                                    edgeMap[id].start.x = current->pos.x + tileSize;
                                    edgeMap[id].start.y = current->pos.y;
                                    edgeMap[id].end.x = current->pos.x + tileSize;
                                    edgeMap[id].end.y = current->pos.y + tileSize;
                                    current->cell.edgesExist[EDGE_RIGHT] = true;
                                    current->cell.edgeIds[EDGE_RIGHT] = id;
                                }
                            }
                        }
                    }
                    if (bottom)
                    {
                        if (!bottom->cell.exist)
                        {
                            if (left)
                            {
                                if (left->cell.edgesExist[EDGE_BOTTOM])
                                {
                                    edgeMap[left->cell.edgeIds[EDGE_BOTTOM]].end.x += tileSize;
                                    current->cell.edgeIds[EDGE_BOTTOM] = left->cell.edgeIds[EDGE_BOTTOM];
                                    current->cell.edgesExist[EDGE_BOTTOM] = true;
                                }
                                else
                                {
                                    string id = to_string(y).append(to_string(x)).append("-").append(to_string(EDGE_BOTTOM));
                                    edgeMap[id].start.x = current->pos.x;
                                    edgeMap[id].start.y = current->pos.y + tileSize;
                                    edgeMap[id].end.x = current->pos.x + tileSize;
                                    edgeMap[id].end.y = current->pos.y + tileSize;
                                    current->cell.edgesExist[EDGE_BOTTOM] = true;
                                    current->cell.edgeIds[EDGE_BOTTOM] = id;
                                }
                            }
                        }
                    }
                    if (left)
                    {
                        if (!left->cell.exist)
                        {
                            if (top)
                            {
                                if (top->cell.edgesExist[EDGE_LEFT])
                                {
                                    // Top neighbour has LEFT EDGE -> extend it.
                                    edgeMap[top->cell.edgeIds[EDGE_LEFT]].end.y += tileSize;

                                    // Set current cell LEFT EDGE id to match top cell LEFT EDGE id.
                                    current->cell.edgeIds[EDGE_LEFT] = top->cell.edgeIds[EDGE_LEFT];
                                    current->cell.edgesExist[EDGE_LEFT] = true;
                                }
                                else
                                {
                                    // Create edge with id, eg. 1010-1
                                    string id = to_string(y).append(to_string(x)).append("-").append(to_string(EDGE_LEFT));
                                    edgeMap[id].start.x = current->pos.x;
                                    edgeMap[id].start.y = current->pos.y;
                                    edgeMap[id].end.x = current->pos.x;
                                    edgeMap[id].end.y = current->pos.y + tileSize;
                                    current->cell.edgesExist[EDGE_LEFT] = true;
                                    current->cell.edgeIds[EDGE_LEFT] = id;
                                }
                            }
                        }
                    }
                }
            }
        }
    };
    void edgeCellsExistCheck()
    {
        for (int y = 0; y < gridSizeY; y++)
        {
            for (int x = 0; x < gridSizeX; x++)
            {
                if (matrix[y][x].type != 0)
                {
                    matrix[y][x].cell.exist = true;
                }
                else
                {
                    matrix[y][x].cell.exist = false;
                }
            }
        }
    };

    // void tilesRender(int type);
};

class Logger
{
public:
    bool active;

    Logger()
    {
        printf("LOG: Logger constructor.\n");
    };
    ~Logger()
    {
        printf("LOG: Logger destructor.\n");
    };
    void log(string str)
    {
        if (active)
        {
            cout << str << endl;
        }
    };
};

class MulperiEngine_Sprite
{
public:
    SDL_Texture *texture;
    SDL_Rect clip;
    SDL_Rect hitbox;

    MulperiEngine_Sprite(){};
    MulperiEngine_Sprite(string path, int w, int h)
    {
        // printf("%d %d\n", w, h);
        clip.x = 0;
        clip.y = 0;
        clip.w = w;
        clip.h = h;
    };
    ~MulperiEngine_Sprite(){};
};

class MulperiEngine_TextureManager
{
public:
    SDL_Renderer *renderer;
    MulperiEngine_TextureManager()
    {
        printf("LOG: TextureManager constructor.\n");
    };
    ~MulperiEngine_TextureManager()
    {
        printf("LOG: TextureManager destructor.\n");
    };
    void Init(SDL_Renderer *r)
    {
        renderer = r;
    };
    SDL_Texture *LoadTexture(string path)
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

    void RenderTexture(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dest)
    {
        SDL_RenderCopy(renderer, texture, src, dest);
    };
    void DestroyTexture(SDL_Texture *t)
    {
        SDL_DestroyTexture(t);
    }
};

class MulperiEngine_Actor
{
public:
    int type;
    string name;
    SDL_Rect rect;
    MulperiEngine_Sprite sprite;

    MulperiEngine_Actor(){};
    MulperiEngine_Actor(MulperiEngine_Sprite sprite, int x, int y){};
    ~MulperiEngine_Actor(){};
    int getCenterX()
    {
        return rect.x + rect.w / 2;
    };
    int getCenterY()
    {
        return rect.y + rect.h / 2;
    };
};

/**
 *  Engine class.
 * */
class MulperiEngine
{
public:
    // Config and SDL.
    MulperiEngine_Config config;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Event event;
    Logger logger;
    MulperiEngine_TextureManager textureManager;

    void *updateCallback;

    // Grid
    MulperiEngine_GridHandler gridHandler;
    MulperiEngine_Grid grid;

    // Actors (players, enemies).
    vector<MulperiEngine_Actor> actors;

    // Scenes.

    // Variables.
    bool running;
    bool debug;

    // Constructor and initialization.
    MulperiEngine(MulperiEngine_Config conf)
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

    ~MulperiEngine()
    {
        if (logger.active)
            logger.log("LOG: Engine destructor.");

        textureManager.Init(renderer);
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
    };

    // Start and stop engine.
    void Init();
    void Run(bool debugModeActive)
    {
        {
            debug = debugModeActive;
            running = true;
            while (running)
            {
                Update();
                Render();
                Sleep(1000 / config.fps);
            }
        };
    };
    void Stop()
    {
        running = false;
    };

    // Update and render.
    bool ProcessEvents()
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
    };
    void Update() { ProcessEvents(); };
    void Render()
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

        printf("%lu\n", actors.size());

        if (actors.size() > 0)
        {
            textureManager.RenderTexture(actors[0].sprite.texture, NULL, &actors[0].sprite.clip);
            printf("actors 0 sprite.clip x y w h : %d %d\n", actors[0].sprite.clip.x, actors[0].sprite.clip.y);
        }

        // Render all above.
        SDL_RenderPresent(renderer);
    }

    // Utils.
    void Sleep(Uint32 ms)
    {
        SDL_Delay(ms);
    };

    // Actors.
    void CreateActor(string path, int x, int y, int width, int height)
    {
        int index = (int)actors.size();
        MulperiEngine_Sprite s(path, width, height);
        MulperiEngine_Actor a(s, x, y);
        actors.push_back(a);
        // printf("%d\n", actors[1].sprite.clip.w);
    };
};

#endif