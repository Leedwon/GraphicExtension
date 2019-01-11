#include "Ox.h"


SDL_Color Ox::getSdlColor(int x, int y)
{
	return colorPalette[pixels[x][y]];
}

Ox::Ox()
{
}


Ox::~Ox()
{
}
