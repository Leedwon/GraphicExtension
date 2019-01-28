#include "Ox.h"
#include "Converter.h"
#include "Utilities.h"


Ox::Ox() {
}

void Ox::setDedicatedPalette(Image *img) {
	colorPalette = Converter::createDedicatedPalette(img);
	paletteType = Constants::dedicated;
	paletteIndexes.resize(height);
	for(int i = 0; i < height; ++i) {
		paletteIndexes[i].resize(width);
	}
	for(int y = 0; y < height; ++y) {
		for(int x = 0; x < width; ++x) {
			SDL_Color currentPixel = img->getPixel(x, y);
			int smallest = distanceBetweenColors(currentPixel, colorPalette[0]);
			int smallestIndex = 0;
			for(int i = 1; i < colorPalette.size(); ++i) {
				int currentDiff = distanceBetweenColors(currentPixel, colorPalette[i]);
				if(currentDiff < smallest) {
					smallest = currentDiff;
					smallestIndex = i;
				}
			}
			paletteIndexes[y][x] = smallestIndex;
		}
	}
}

void Ox::setImposedPalette(Image *img) {
	colorPalette = Converter::createImposedPalette();
	paletteType = Constants::imposed;
	paletteIndexes.resize(height);
	for (int i = 0; i < height; ++i) {
		paletteIndexes[i].resize(width);
	}
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			SDL_Color currentPixel = img->getPixel(x, y);
			int smallest = distanceBetweenColors(currentPixel, colorPalette[0]);
			int smallestIndex = 0;
			for (int i = 1; i < colorPalette.size(); ++i) {
				int currentDiff = distanceBetweenColors(currentPixel, colorPalette[i]);
				if (currentDiff < smallest) {
					smallest = currentDiff;
					smallestIndex = i;
				}
			}
			paletteIndexes[y][x] = smallestIndex;
		}
	}
}

Uint32* Ox::getPixelsForBmp()
{
	Uint32 *bmpPixels = new Uint32[width * height];
	Uint32 temp;
	SDL_Color color;
	if (paletteType == Constants::dedicated || paletteType == Constants::dedicatedDith || paletteType == Constants::imposed)
	{
		if (paletteType == Constants::imposed)
		{
			colorPalette = Converter::createImposedPalette();
		}
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				/* SDL has a function to save to bmp file but it takes each pixels a Uint32 pack so we have to pack every component into one data chunk*/
				color = colorPalette[paletteIndexes[i][j]];
				temp = color.r << 8; // packing red component
				temp |= color.g; // packing green and shifting to appropriate position
				temp <<= 8;
				temp |= color.b; // packing blue and shifting to appropriate position
				temp <<= 8;
				temp |= 255; // packing alfa
				bmpPixels[i*width + j] = temp;
			}
		}

	} else if(paletteType == Constants::bwDith || paletteType == Constants::grey)
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				temp = pixels[i][j] << 8;
				temp |= pixels[i][j];
				temp <<= 8;
				temp |= pixels[i][j];
				temp <<= 8;
				temp |= 255; 
				bmpPixels[i*width + j] = temp;
			}
		}
	} else
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				color = Converter::oxPixelToSdlColor(pixels[i][j]);
				temp = color.r << 8;
				temp |= color.g;
				temp <<= 8;
				temp |= color.b;
				temp <<= 8;
				temp |= 255;
				bmpPixels[i*width + j] = temp;
			}
		}
	}
	return bmpPixels;
}

Ox::Ox(Constants::paletteType palType, int w, int h, std::vector<std::vector<Constants::oxPixel>> pixelsVector,
       std::array<SDL_Color, Constants::PALETTE_SIZE> paletteArr) : paletteType(palType), width(w), height(h),
                                                                    pixels(pixelsVector), colorPalette(paletteArr) {
}


Ox::Ox(int width, int height, std::vector<std::vector<Constants::oxPixel>> pixelsVector,
	Constants::paletteType paletteType) : width(width), height(height), pixels(pixelsVector),
	paletteType(paletteType) {
}

Ox::~Ox() {
}
