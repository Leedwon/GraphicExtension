#pragma once
#include <vector>
#include <array>
#include <SDL.h>
#include "Constants.h"
#include "Image.h"

class Ox {
public:
	Constants::paletteType paletteType;
	unsigned int width;
	unsigned int height;
	// pixells stored as followed pixels[height][width]
	std::vector<std::vector<Constants::oxPixel>> paletteIndexes;
	std::vector<std::vector<Constants::oxPixel>> pixels;
	std::array<SDL_Color, Constants::PALETTE_SIZE> colorPalette;
	void setDedicatedPalette(Image* img);
	SDL_Color getPixelFromPalette(int x, int y) { return colorPalette[paletteIndexes[y][x]]; }
	Constants::oxPixel getPixel(int x, int y) { return pixels[y][x]; }
	std::vector<std::vector<Constants::oxPixel>> getPixelsVector() { return pixels; }
	Ox(Constants::paletteType paletteType, int width, int height, std::vector<std::vector<Constants::oxPixel>> pixelsVector,
		std::array<SDL_Color, Constants::PALETTE_SIZE> paletteArr);

	Ox(int width, int height, std::vector<std::vector<Constants::oxPixel>> pixelsVector,
		Constants::paletteType paletteType);
	Ox();
	~Ox();
};
