#include <cstdio>
#include "gridhandler.h"

GridHandler::GridHandler()
{
    printf("Grid constructor called.\n");
    tileSize = 16;
    sizeY = 30;
    sizeX = 40;
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            matrix[y][x] = 0;
        }
    }
}
GridHandler::~GridHandler()
{
    printf("Grid deconstructor called.\n");
}
void GridHandler::generate(int sx, int sy, int interations) {}
void GridHandler::readFile() {}
void GridHandler::print() {}
int GridHandler::getSizeY() { return sizeY; }
int GridHandler::getSizeX() { return sizeX; }
int GridHandler::getTileSize() { return tileSize; }