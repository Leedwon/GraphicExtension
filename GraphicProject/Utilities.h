#pragma once
#include <SDL.h>
#include <string>
#include <string.h>
#include <SDL_ttf.h>
#include <vector>
#include "Ox.h"
#include <fstream>


SDL_Color operator+ (const SDL_Color &l, const SDL_Color &r);
SDL_Color operator- (const SDL_Color &l, const SDL_Color &r);
bool operator== (const SDL_Color &l, const SDL_Color &r);
bool operator!= (const SDL_Color &l, const SDL_Color &r);
void renderText(SDL_Renderer *renderer, std::string text, TTF_Font *font, SDL_Rect *background, SDL_Color textColor);
int distanceBetweenColors(const SDL_Color &imageColor, const SDL_Color &paletteColor);
std::vector<std::vector<uint8_t>> ditheringGreyScale(const std::vector<std::vector<uint8_t>> &pixelData);
std::vector<std::vector<uint8_t>> ditheringColor(const std::vector<std::vector<SDL_Color>> &pixelMap, Ox &targetImage);
void tooSmallSurfaceExceptionHandle(SDL_Renderer *renderer, TTF_Font *font);
Constants::fileExtension checkFile(std::string fileName);