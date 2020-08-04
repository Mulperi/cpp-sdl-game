#ifndef MULPERI2D_GRIDHANDLER_H
#define MULPERI2D_GRIDHANDLER_H
#include <string>
#include <vector>

/**
 * For handling and generating 2d grid maps.
 * */
class Mulperi2D_GridHandler
{
public:
    Mulperi2D_GridHandler()
    {
        printf("LOG: Gridhandler constructor.\n");
    };
    ~Mulperi2D_GridHandler()
    {
        printf("LOG: Gridhandler destructor.\n");
    };
    void generate(int sx, int sy, int interations);
    std::vector<std::vector<char>> fileRead(std::string, int sizeY, int sizeX)
    {

        if (!sizeY || !sizeX)
            printf("ERROR: Gridhandler: Check grid Y and X length!\n");

        std::cout << "LOG: Gridhandler fileread: " << path << std::endl;

        std::vector<std::vector<char>> grid(sizeY, std::vector<char>(sizeX, 0));
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
    };
    void print(std::vector<std::vector<char>>, int sizeY, int sizeX);
};
#endif