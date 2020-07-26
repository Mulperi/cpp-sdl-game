#ifndef TEXT_H
#define TEXT_H
#include <SDL2/SDL_ttf.h>
#include <string>
#include "text.h"

class Text
{
public:
    std::string phrase;
    int size, x, y;
    TTF_Font *font;
    SDL_Rect rect;
    SDL_Texture *texture;
    SDL_Color color;
    SDL_Renderer *renderer;

    Text();
    Text(std::string str, int ppt, int posX, int posY, int r, int g, int b, int a, SDL_Renderer *renderer);
    ~Text();
    void updateTexture();
    void phraseGet(std::string str);
    void phraseSet(std::string str);
    void colorGet(std::string str);
    void colorSet(std::string str);
    void render();
};
#endif