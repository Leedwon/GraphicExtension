#pragma once
#include <vector>
#include <array>
#include <SDL.h>
#include "Constants.h"

class Ox {
private:
	int paletteType;
	int width;
	int height;
public:
	std::vector<std::vector<Constants::oxColor>> pixels;
	std::array<SDL_Color, Constants::PALETTE_SIZE> colorPalette;
	Constants::oxColor getPixel(int x, int y) { return pixels[x][y]; }
	Ox(int paletteType, int width, int height, std::vector<std::vector<Constants::oxColor>> pixelsVector,
	   std::array<SDL_Color, Constants::PALETTE_SIZE> paletteArr);
	Ox();
	~Ox();
	int getWidth() const { return width; }
	int getHeight() const { return height; }
};
