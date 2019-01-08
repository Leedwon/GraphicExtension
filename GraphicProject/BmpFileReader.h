#pragma once
#include <string>
#include <SDL.h>

class BmpFileReader {
private:
	std::string filePath;
	SDL_Surface *surface;
public:
	BmpFileReader(SDL_Surface *surf) : filePath(""), surface(surf) {}
	BmpFileReader(std::string file);
	SDL_Color getPixel(const int &x, const int &y);
	Uint8 *getPixelAddress(const int &x, const int &y) const;
	~BmpFileReader() = default;
	int getWidth() const { return surface->w; } 
	int getHeight() const { return surface->h; }
};

