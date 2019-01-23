#pragma once
#include <vector>
#include <array>
#include <SDL.h>
#include "Constants.h"

class Ox {
public:
	int paletteType;
	unsigned int width;
	unsigned int height;
	// pixells stored as followed pixels[height][width]
	std::vector<std::vector<Constants::oxPixel>> pixels;
	std::array<SDL_Color, Constants::PALETTE_SIZE> colorPalette;
	Constants::oxPixel getPixel(int x, int y) { return pixels[y][x]; }
	std::vector<std::vector<Constants::oxPixel>> getPixelsVector() { return pixels; }
	Ox(int paletteType, int width, int height, std::vector<std::vector<Constants::oxPixel>> pixelsVector,
	   std::array<SDL_Color, Constants::PALETTE_SIZE> paletteArr);
	Ox();
	~Ox();
};
