#pragma once
#include "Image.h"
#include "Ox.h"

/* class for making conversions from Image to Ox pixel type
 * 
 * 
 */
class Converter {
private:
	Converter();
	static std::array<SDL_Color, Constants::PALETTE_SIZE> createDedicatedPalette(Image* image);
	static std::vector<std::vector<Constants::oxColor>> createOxPixelsFromImage(Image* image);
	static std::vector<std::vector<SDL_Color>> createSdlPixelsFromOx(Ox* ox);
	static Constants::oxColor SdlColor_to_oxPixel(SDL_Color color);
	static SDL_Color oxPixel_to_sdlColor(Constants::oxColor oxColor);
	static SDL_Color getColorFromPalette(Constants::oxColor oxColor); // ??? 
public:
	/*
	 * method creates oxPixels vector and creates dedicatedPalette if needed
	 * @param Image *image - pointer to BMP image that we want convert to ox
	 * @param Ox *ox - pointer to ox that we want to intialize
	 */
	static Ox convertImageToOx(Image* image);
	static Image convertOxToImage(Ox* ox);
	~Converter();
};
