#ifndef GRID_H
#define GRID_H

#include <SDL2/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>
#include "tile.h"
#include "gridhandler.h"
#include "celledge.h"

using namespace std;

class Grid
{
public:
    Mulperi2D_GridHandler *gridHandler;
    int gridSizeY;
    int gridSizeX;
    int tileSize;
    vector<vector<Tile> > matrix;
    vector<Tile *> walls;
    unordered_map<string, CellEdge> edgeMap;

    // vector<vector<EdgeCell> > edgeCells;

    Grid();
    ~Grid();
    void init(int lengthY, int lengthX, int size);
    vector<vector<Tile> > tilesConvert(vector<vector<char> > charGrid);
    void tilesWallsGet(vector<vector<Tile> > tileGrid);
    void edgeCellsCheck();
    void edgeCellsExistCheck();

    // void tilesRender(int type);
};
#endif