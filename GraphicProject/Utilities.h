#pragma once
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>


SDL_Color operator+ (const SDL_Color &l, const SDL_Color &r);
SDL_Color operator- (const SDL_Color &l, const SDL_Color &r);
bool operator== (const SDL_Color &l, const SDL_Color &r);
bool operator!= (const SDL_Color &l, const SDL_Color &r);
void renderText(SDL_Renderer *renderer, std::string text, TTF_Font *font, SDL_Rect *background, SDL_Color textColor);