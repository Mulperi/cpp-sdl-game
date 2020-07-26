#ifndef GRIDHANDLER_H
#define GRIDHANDLER_H

class GridHandler
{
public:
    int sizeY;
    int sizeX;
    int tileSize;
    // std::vector<std::vector<int> > matrix;
    int matrix[30][40];

    GridHandler();
    ~GridHandler();
    void generate(int sx, int sy, int interations);
    void readFile();
    void print();
    int getSizeY();
    int getSizeX();
    int getTileSize();
};
#endif