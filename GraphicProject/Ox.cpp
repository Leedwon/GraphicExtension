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
