#include "SurfaceHandler.h"



SDL_Color SurfaceHandler::getPixel(const int& x, const int& y) {
	Uint8 *pixAddress = getPixelAddress(x, y);
	SDL_Color pixel = {};
	if (pixAddress) {
		Uint32 rgbColor = 0;
		memcpy(&rgbColor, pixAddress, surface->format->BytesPerPixel);
		SDL_GetRGB(rgbColor, surface->format, &pixel.r, &pixel.g, &pixel.b);
	}
	return pixel;
}

Uint8* SurfaceHandler::getPixelAddress(const int& x, const int& y) {
	int bytesPerPixel = surface->format->BytesPerPixel;
	Uint8 *pixelAddress = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x * bytesPerPixel;
	return pixelAddress;
}

void SurfaceHandler::setPixel(const int& x, const int& y, const SDL_Color& color) {
	Uint8 *pixAddress = getPixelAddress(x, y);
	Uint32 newPix = SDL_MapRGB(surface->format, color.r, color.g, color.b);
	int bytesPerPixel = surface->format->BytesPerPixel;
	switch (bytesPerPixel) {
	case 1: //8-bit
		*pixAddress = newPix;
		break;

	case 2: //16-bit
		*(Uint16 *)pixAddress = newPix;
		break;

	case 3: //24-bit
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			pixAddress[0] = (newPix >> 16) & 0xff;
			pixAddress[1] = (newPix >> 8) & 0xff;
			pixAddress[2] = newPix & 0xff;
		} else {
			pixAddress[0] = newPix & 0xff;
			pixAddress[1] = (newPix >> 8) & 0xff;
			pixAddress[2] = (newPix >> 16) & 0xff;
		}
		break;

	case 4: //32-bit
		*(Uint32 *)pixAddress = newPix;
		break;
	}
}

void SurfaceHandler::setPixel(const int& x, const int& y, int r, int g, int b) {
	Uint8 *pixAddress = getPixelAddress(x, y);
	Uint32 newPix = SDL_MapRGB(surface->format, r, g, b);
	int bytesPerPixel = surface->format->BytesPerPixel;
	switch (bytesPerPixel) {
	case 1: //8-bit
		*pixAddress = newPix;
		break;

	case 2: //16-bit
		*(Uint16 *)pixAddress = newPix;
		break;

	case 3: //24-bit
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			pixAddress[0] = (newPix >> 16) & 0xff;
			pixAddress[1] = (newPix >> 8) & 0xff;
			pixAddress[2] = newPix & 0xff;
		} else {
			pixAddress[0] = newPix & 0xff;
			pixAddress[1] = (newPix >> 8) & 0xff;
			pixAddress[2] = (newPix >> 16) & 0xff;
		}
		break;

	case 4: //32-bit
		*(Uint32 *)pixAddress = newPix;
		break;
	}
}

void SurfaceHandler::drawImage(Image *image, int startingX, int startingY) {
	if (image->getWidth() + startingX > surface->w || image->getHeight() + startingY > surface->h)
		throw TOO_SMALL_SURFACE_EXCEPTION;
	for(int height = 0; height < image->getHeight(); ++height) {
		for (int width = 0; width < image->getWidth(); ++width) 
			setPixel(width + startingX, height + startingY, image->getPixel(width, height));
	}		
}

void SurfaceHandler::drawOx(Ox* ox, int startingX, int startingY) {
	if (ox->width + startingX > surface->w || ox->height + startingY > surface->h)
		throw TOO_SMALL_SURFACE_EXCEPTION;
	for (int height = 0; height < ox->height; ++height) {
		for (int width = 0; width < ox->width; ++width) {
			Constants::oxPixel pixel = ox->getPixel(width, height);
			SDL_Color sdlFromOx;
			sdlFromOx = Converter::oxPixelToSdlColor(pixel);
			setPixel(width + startingX, height + startingY, sdlFromOx);
		}
	}
}

SurfaceHandler::~SurfaceHandler() {
	SDL_free(surface);
}
