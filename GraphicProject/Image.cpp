#include "Image.h"
#include "BmpFileReader.h"


Image::Image(std::string filePath) {
	// TODO:: refactor constructor move each init to separate function
	this->filePath = filePath;
	BmpFileReader fileReader(this->filePath);
	this->height = fileReader.getHeight();
	this->width = fileReader.getWidth();
	pixelMap.resize(width); // init vectors
	for(int i = 0; i < width; ++i) {
		pixelMap[i].resize(height); // init vectors
	}
	for(int i = 0; i < width; ++i) {
		for (int j = 0; j < height; j++)
			pixelMap[i][j] = fileReader.getPixel(i, j);
	}
}

Image::~Image(){

}
