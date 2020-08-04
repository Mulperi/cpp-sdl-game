#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#define PI 3.14159265359;

int randomNumberGet(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

float radiansToAngle(float radians)
{
    return radians * 180 / PI
}

#endif