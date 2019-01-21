#pragma once
#include <SDL.h>


SDL_Color operator+ (const SDL_Color &l, const SDL_Color &r);
SDL_Color operator- (const SDL_Color &l, const SDL_Color &r);
bool operator== (const SDL_Color &l, const SDL_Color &r);
bool operator!= (const SDL_Color &l, const SDL_Color &r);
