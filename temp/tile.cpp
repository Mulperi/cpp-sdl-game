#include <cstdio>
#include "tile.h"

Tile::Tile()
{
    type = 0;
    hp = 0;
}
Tile::Tile(int tileType)
{
    type = tileType;
    hp = 100;
}
Tile::~Tile() {}
int Tile::typeGet()
{
    return type;
}
void Tile::typeSet(int t)
{
    type = t;
}
float Tile::hpGet()
{
    return hp;
}
void Tile::hpSet(float h)
{
    hp = h;
}
void Tile::positionSet(int y, int x)
{
    pos.y = y;
    pos.x = x;
}
int Tile::positionGetY()
{
    return pos.y;
}
int Tile::positionGetX()
{
    return pos.x;
}
void Tile::hpDecrease(float amount)
{
    hp -= amount;
}