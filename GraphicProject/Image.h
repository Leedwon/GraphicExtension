#pragma once
#include <vector>
#include <array>
#include "SDL.h"

class Image {
private:
	std::string filePath;
	int width;
	int height;
	std::vector<std::vector<SDL_Color>> pixelMap; // not sure if 2d array wouldnt be better?
	void initVectors(int width, int height);
public:
	//TODO: think of needed constructors dont make them too long
	Image(std::string filePath);
	Image(int width, int height);
	void setImageDimensions(int width, int height);
	~Image();
	SDL_Color getPixel(int x, int y);
	void setPixel(int x, int y, SDL_Color color);
	//Getters & Setters
	int getWidth();
	int getHeight();
};