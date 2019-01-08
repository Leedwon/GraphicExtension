#pragma once
#include <vector>
#include <array>
#include "SDL.h"

class Image {
private:
	static const int PALETTE_SIZE = 64;
	std::string filePath;
	int width;
	int height;
	std::vector<std::vector<SDL_Color>> pixelMap; // not sure if 2d array wouldnt be better?
	std::array<SDL_Color, PALETTE_SIZE> dedicatedPalette;
	std::array<int, PALETTE_SIZE> greyPalette; // all the values in rgb will be same here but im not sure if array<RGB, 64> wouldnt be better for type consistency
	std::array<SDL_Color, PALETTE_SIZE> imposedPalette; // should we store it?
public:
	//TODO: think of needed constructors dont make them too long
	Image(std::string filePath);
	~Image();
};

