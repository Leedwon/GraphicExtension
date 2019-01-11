#pragma once
#include <vector>
#include <array>
#include <SDL.h>
#include "Constants.h"

class Ox
{
private:
public:
	int paletteType;
	int width;
	int height;
	std::vector<std::vector<uint8_t>> pixels;
	std::array<SDL_Color, Constants::PALETTE_SIZE> colorPalette;
	SDL_Color getSdlColor(int x, int y);
	Ox();
	~Ox();
};
