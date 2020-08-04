#include <cstdio>
#include <iostream>
#include <vector>
#include "gridhandler.h"

// Mulperi2D_GridHandler::Mulperi2D_GridHandler()
// {
//     printf("LOG: Gridhandler constructor.\n");
// }
// Mulperi2D_GridHandler::~Mulperi2D_GridHandler()
// {
//     printf("LOG: Gridhandler destructor.\n");
// }
// void Mulperi2D_GridHandler::generate(int sx, int sy, int interations) {}

std::vector<std::vector<char> > Mulperi2D_GridHandler::fileRead(std::string path, int sizeY, int sizeX)
{

    if (!sizeY || !sizeX)
        printf("ERROR: Gridhandler: Check grid Y and X length!\n");

    std::cout << "LOG: Gridhandler fileread: " << path << std::endl;

    std::vector<std::vector<char> > grid(sizeY, std::vector<char>(sizeX, 0));
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

    std::cout << "LOG: " << path << " read finished." << std::endl;

    if (fclose(fp) == 0)
    {
        std::cout << "LOG: " << path << " closed." << std::endl;
    }
    else
    {
        std::cout << "LOG: " << path << "close failed." << std::endl;
    }
    return grid;
}

void Mulperi2D_GridHandler::print(std::vector<std::vector<char> >, int sizeY, int sizeX)
{

}
