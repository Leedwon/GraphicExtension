#include "Ox.h"


Ox::Ox() {
}

Ox::Ox(int palType, int w, int h, std::vector<std::vector<Constants::oxPixel>> pixelsVector,
       std::array<SDL_Color, Constants::PALETTE_SIZE> paletteArr) : paletteType(palType), width(w), height(h),
                                                                    pixels(pixelsVector), colorPalette(paletteArr) {
}

Ox::~Ox() {
}
