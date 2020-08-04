#ifndef TILE_H
#define TILE_H
#include <SDL2/SDL.h>
#include "celledge.h"

class Tile
{
public:
    SDL_Point pos;
    int type;
    float hp;
    CellEdgeExistData cell;

    Tile();
    Tile(int tileType);
    ~Tile();
    int typeGet();
    void typeSet(int t);
    float hpGet();
    void hpSet(float h);
    void positionSet(int y, int x);
    int positionGetX();
    int positionGetY();
    void hpDecrease(float amount);
};

#endif