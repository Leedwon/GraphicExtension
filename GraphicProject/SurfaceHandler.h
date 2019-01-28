#pragma once
#include <SDL.h>
#include <cstring>
#include "Image.h"
#include "Ox.h"
#include "Converter.h"

class SurfaceHandler
{
private:
	void resizeSurface(int width, int height);
public:
	enum SurfaceHandlerExceptions {
		TOO_SMALL_SURFACE_EXCEPTION
	};
	SDL_Surface *surface;
	SDL_Color getPixel(const int &x, const int &y);
	Uint8 *getPixelAddress(const int &x, const int &y);
	void setPixel(const int &x, const int &y, const SDL_Color &color);
	void setPixel(const int &x, const int &y, int r, int g, int b);
	/* for this function to show results SDL_UpdateWindowSurface(window) must be called after
	 */
	void drawImage(Image *image, int startingX, int startingY);
	void drawOx(Ox *ox, int startingX, int startingY);
	void drawOxFromPalette(Ox *ox, int startingX, int startingY);
	// pixels stored in following manner pixels[height][width]
	void drawPixels(std::vector<std::vector<Constants::oxPixel>> pixels, int startingx, int startingY);
	SurfaceHandler(SDL_Surface *surf) : surface(surf) {}
	~SurfaceHandler();
};

