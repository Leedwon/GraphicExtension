#pragma once
#include <string>
#include <SDL.h>
#include "SurfaceHandler.h"


class BmpFileReader {
private:
	std::string filePath;
	SDL_Surface *surface;
	SurfaceHandler *handler;
public:
	BmpFileReader(std::string file);
	SDL_Color getPixel(const int &x, const int &y) { return handler->getPixel(x, y); }
	~BmpFileReader();
	int getWidth() const { return surface->w; } 
	int getHeight() const { return surface->h; }
};