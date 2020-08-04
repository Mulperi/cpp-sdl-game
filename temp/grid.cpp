#include "grid.h"
#include "celledge.h"

using namespace std;

Grid::Grid()
{
}
Grid::~Grid() {}
void Grid::init(int lengthY, int lengthX, int size)
{
    // Init grid size and load tile information.
    gridSizeY = lengthY;
    gridSizeX = lengthX;
    tileSize = size;
    matrix = tilesConvert(gridHandler->fileRead("map.txt", gridSizeY, gridSizeX));
    tilesWallsGet(matrix);
    edgeCellsExistCheck();
    edgeCellsCheck();
}

// Get wall tiles pointers from matrix to walls vector.
void Grid::tilesWallsGet(vector<vector<Tile> > tilesGrid)
{
    for (int y = 0; y < 30; y++)
    {
        for (int x = 0; x < 40; x++)
        {
            if (tilesGrid[y][x].typeGet() == 1)
                walls.push_back(&matrix[y][x]);
        }
    }
}

void Grid::edgeCellsCheck()
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
}

// Convert char matrix to tile matrix.
vector<vector<Tile> > Grid::tilesConvert(vector<vector<char> > charGrid)
{
    vector<vector<Tile> > tileGrid(30, vector<Tile>(40, 0));
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
}
void Grid::edgeCellsExistCheck()
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
}