#ifndef CELL_H
#define CELL_H

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include "tile.h"

using namespace std;

enum EDGES
{
    EDGE_TOP,
    EDGE_RIGHT,
    EDGE_BOTTOM,
    EDGE_LEFT
};

typedef struct CellEdge
{
    SDL_Point start;
    SDL_Point end;
    // unordered_map<string *, Tile> tileMap;
} CellEdge;

typedef struct CellEdgeExistData
{
    string edgeIds[4];
    bool edgesExist[4]; // North, South, East, West.
    bool exist;
    std::string id;
} CellEdgeExistData;

#endif