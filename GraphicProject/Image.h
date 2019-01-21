#pragma once
#include <vector>
#include <array>
#include "SDL.h"

class Image {
private:
	std::string filePath;
	int width;
	int height;
	std::vector<std::vector<SDL_Color>> pixelMap;
	void initVectors(int width, int height);
public:
	Image(std::string filePath);
	Image(int width, int height, std::vector<std::vector<SDL_Color>> pixelVector);
	SDL_Color getPixel(int x, int y);
	void setPixel(int x, int y, SDL_Color color);
	~Image();
	//Getters & Setters
	int getWidth();
	int getHeight();
};