#include "Converter.h"



Converter::Converter()
{
}

void Converter::createPalette(Ox *ox)
{
	for(int i = 0; i < Constants::PALETTE_SIZE; ++i)
	{
		ox->colorPalette[i] = bits_to_sdl_color(i);
	}
}



uint8_t Converter::reduceTo6Bits(SDL_Color color)
{
	uint8_t oxColor = 0;
	oxColor |= (color.r & Constants::MASK_6_BITS) << 4;
	oxColor |= (color.g & Constants::MASK_6_BITS) << 2;
	oxColor |= (color.b & Constants::MASK_6_BITS);
	return oxColor;
}

SDL_Color Converter::bits_to_sdl_color(uint8_t oxColor)
{
	SDL_Color color;
	color.r = oxColor & Constants::MASK_6_BITS_RED;
	color.g = oxColor & Constants::MASK_6_BITS_GREEN;
	color.b = oxColor & Constants::MASK_6_BITS_BLUE;
	color.a = 1;
	return color;
}


void Converter::convertImageToOxShiftBits(Image* image, Ox* ox)
{
	ox->width = image->getWidth();
	ox->height = image->getHeight();
	for(int y = 0; y < image->getHeight(); ++y)
	{

		for (int x = 0; x < image->getWidth(); ++x)
		{
			ox->pixels[x][y] = reduceTo6Bits(image->getPixel(x, y));
		}
	}
	createPalette(ox);
	ox->paletteType = Constants::PALETTE_TYPE_BYTE_SHIFT;
}

void Converter::convertOxToImage(Image* image, Ox* ox)
{
	image->setImageDimensions(ox->width, ox->height);
	for(int y = 0; y < ox->height; ++y)
	{
		for (int x = 0; x < ox->width; ++x)
		{
			image->setPixel(x, y, ox->getSdlColor(x, y));
		}	
	}
}


Converter::~Converter()
{
}
