#include "Converter.h"


Converter::Converter() {
}

// just temporary solution pallete should be created based on image TODO :: 
std::array<SDL_Color, Constants::PALETTE_SIZE> Converter::createDedicatedPalette(Image* img) {
	std::array<SDL_Color, Constants::PALETTE_SIZE> result;
	return result;
}

std::vector<std::vector<Constants::oxColor>> Converter::createOxPixelsFromImage(Image* image) {
	std::vector<std::vector<Constants::oxColor>> pixels;
	pixels.resize(image->getWidth()); // init vector
	for (int i = 0; i < image->getWidth(); ++i) {
		pixels[i].resize(image->getHeight()); // init vector
	}
	for (int y = 0; y < image->getHeight(); ++y) {

		for (int x = 0; x < image->getWidth(); ++x) {
			pixels[x][y] = SdlColor_to_oxPixel(image->getPixel(x, y));
		}
	}
	return pixels;
}

std::vector<std::vector<SDL_Color>> Converter::createSdlPixelsFromOx(Ox* ox) {
	std::vector<std::vector<SDL_Color>> pixels;
	pixels.resize(ox->getWidth()); // init vector
	for (int i = 0; i < ox->getWidth(); ++i) {
		pixels[i].resize(ox->getHeight()); // init vector
	}
	for (int y = 0; y < ox->getHeight(); ++y) {
		for (int x = 0; x < ox->getWidth(); ++x) {
			pixels[x][y] = oxPixel_to_sdlColor(ox->getPixel(x, y));
		}
	}
}


uint8_t Converter::SdlColor_to_oxPixel(SDL_Color color) {
	uint8_t oxColor = 0;
	oxColor |= (color.r & Constants::MASK_FIRST_3_BITS) << 5;
	oxColor |= (color.g & Constants::MASK_FIRST_3_BITS) << 2;
	oxColor |= (color.b & Constants::MASK_FIRST_2_BITS);
	return oxColor;
}


SDL_Color Converter::oxPixel_to_sdlColor(Constants::oxColor oxColor) {
	SDL_Color color;
	color.r = oxColor & Constants::MASK_BITS_RED;
	color.g = oxColor & Constants::MASK_BITS_GREEN;
	color.b = oxColor & Constants::MASK_BITS_BLUE;
	color.a = 1;
	return color;
}


Ox Converter::convertImageToOx(Image* image) {
	int width = image->getWidth();
	int height = image->getHeight();
	int paletteType = 0; // refactor later
	std::vector<std::vector<Constants::oxColor>> pixels = createOxPixelsFromImage(image);
	std::array<SDL_Color, Constants::PALETTE_SIZE> palette = createDedicatedPalette(image);
	return Ox(paletteType, width, height, pixels, palette);
}

Image Converter::convertOxToImage(Ox* ox) {
	std::vector<std::vector<SDL_Color>> pixels = createSdlPixelsFromOx(ox);
	int width = ox->getWidth();
	int height = ox->getHeight();
	return Image(width, height, pixels);
}


Converter::~Converter() {
}
