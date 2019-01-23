#include "Image.h"
#include "BmpFileReader.h"


void Image::initVectors(int width, int height) {
	pixelMap.resize(height); // init vectors
	for (int i = 0; i < height; ++i) {
		pixelMap[i].resize(width); // init vectors
	}
}

Image::Image(std::string filePath) {
	// TODO:: refactor constructor move each init to separate function
	this->filePath = filePath;
	BmpFileReader fileReader(this->filePath);
	this->height = fileReader.getHeight();
	this->width = fileReader.getWidth();
	initVectors(width, height);
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x)
			pixelMap[y][x] = fileReader.getPixel(x, y);
	}
}

Image::Image(int w, int h,
             std::vector<std::vector<SDL_Color>> pixelVector) : width(w), height(h), pixelMap(pixelVector) {

}


int Image::getWidth() {
	return width;
}

int Image::getHeight() {
	return height;
}


Image::~Image() {

}

SDL_Color Image::getPixel(int x, int y) {
	return pixelMap[y][x];
}

void Image::setPixel(int x, int y, SDL_Color color) {
	pixelMap[y][x] = color;
}
