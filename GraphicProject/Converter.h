#pragma once
#include "Image.h"
#include "Ox.h"

class Converter
{
private:
	Converter();
	static void createPalette(Ox *ox);
	static uint8_t reduceTo6Bits(SDL_Color color);
	static SDL_Color bits_to_sdl_color(uint8_t oxColor);
	static SDL_Color getColorFromPalette(uint8_t oxColor);
public:
	static void convertImageToOxShiftBits(Image *image, Ox *ox);
	static void convertOxToImage(Image *image, Ox *ox);
	~Converter();
};

