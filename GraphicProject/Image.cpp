#include "Image.h"
#include "BmpFileReader.h"


void Image::initVectors(int width, int height)
{
	pixelMap.resize(width); // init vectors
	for (int i = 0; i < width; ++i) {
		pixelMap[i].resize(height); // init vectors
	}
}

Image::Image(std::string filePath) {
	// TODO:: refactor constructor move each init to separate function
	this->filePath = filePath;
	BmpFileReader fileReader(this->filePath);
	this->height = fileReader.getHeight();
	this->width = fileReader.getWidth();
	initVectors(width, height);
	for(int i = 0; i < width; ++i) {
		for (int j = 0; j < height; j++)
			pixelMap[i][j] = fileReader.getPixel(i, j);
	}
}

Image::Image(int width, int height)
{
	setImageDimensions(width, height);
}

void Image::setImageDimensions(int width, int height)
{
	this->width = width;
	this->height = height;
	initVectors(width, height);
}


int Image::getWidth()
{
	return width;
}

int Image::getHeight()
{
	return height;
}


Image::~Image(){

}

SDL_Color Image::getPixel(int x, int y)
{
	return pixelMap[x][y];
}

void Image::setPixel(int x, int y,SDL_Color color)
{
	pixelMap[x][y] = color;
}
