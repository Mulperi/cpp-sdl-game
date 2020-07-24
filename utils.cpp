#include "main.h"

int random_number_get(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}