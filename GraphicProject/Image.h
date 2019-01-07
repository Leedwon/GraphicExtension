#pragma once
#include <vector>
#include <array>
#include "Structures.h"

class Image {
private:
	static const int PALETTE_SIZE = 64;
	int width;
	int height;
	std::vector<std::vector<RGB>> pixelMap; // not sure if 2d array wouldnt be better?
	std::array<RGB, PALETTE_SIZE> dedicatedPalette;
	std::array<int, PALETTE_SIZE> greyPalette; // all the values in rgb will be same here but im not sure if array<RGB, 64> wouldnt be better for type consistency
	std::array<RGB, PALETTE_SIZE> imposedPalette; // should we store it?
public:
	//TODO: think of needed constructors dont make them too long
	Image();
	~Image();
};

