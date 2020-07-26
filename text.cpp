#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <string>
#include "text.h"

Text::Text(){};
Text::Text(std::string str, int ppt, int posX, int posY, int r, int g, int b, int a, SDL_Renderer *renderer)
{
    phrase = str;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    TTF_Font *roboto = TTF_OpenFont("assets/roboto.ttf", 16);
    SDL_Surface *text = TTF_RenderText_Blended(font, str.c_str(), color);
    texture = SDL_CreateTextureFromSurface(renderer, text);
    SDL_FreeSurface(text);
};

Text::~Text()
{
    // TTF_CloseFont(font);
    // SDL_DestroyTexture(texture);
};

void Text::render()
{
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}