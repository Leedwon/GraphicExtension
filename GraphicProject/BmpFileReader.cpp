#include "BmpFileReader.h"



BmpFileReader::BmpFileReader(std::string fileString){
	filePath = fileString;
	surface = SDL_LoadBMP(filePath.c_str());
}

SDL_Color BmpFileReader::getPixel(const int& x, const int& y) {
	Uint8 *pixAddress = getPixelAddress(x, y);
	SDL_Color pixel = {};
	if (pixAddress) {
		Uint32 rgbColor = 0;
		memcpy(&rgbColor, pixAddress, surface->format->BytesPerPixel);
		SDL_GetRGB(rgbColor, surface->format, &pixel.r, &pixel.g, &pixel.b);
	}
	return pixel;
}

Uint8 *BmpFileReader::getPixelAddress(const int & x, const int & y) const {
	const int bytesPerPixel = surface->format->BytesPerPixel;
	Uint8 *pixelAddress = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x * bytesPerPixel;
	return pixelAddress;
}
