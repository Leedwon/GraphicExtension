#include "Converter.h"


Converter::Converter() {
}

void Converter::sort_by_color(std::vector<SDL_Color> &allPixels, int begin, int end, int which_sort) {

	std::vector<SDL_Color >sorto[256];
	
	int a;

	switch (which_sort) {
	case 0:								//  sort by red values

		for (int i = begin;i < end;i++) {
			a = allPixels[i].r;
			sorto[a].push_back(allPixels[i]);
		}
		break;
	case 1:								//  sort by green values

		for (int i = begin;i < end;i++) {
			a = allPixels[i].g;
			sorto[a].push_back(allPixels[i]);
		}
		break;
	case 2:								//  sort by blue values

		for (int i = begin;i < end;i++) {
			a = allPixels[i].b;
			sorto[a].push_back(allPixels[i]);
		}
		break;

	}

	int indeks = begin;

	for (int counter = 0;counter<256;counter++) {
		while (sorto[counter].empty() == 0) {
			allPixels[indeks++] = sorto[counter].back();
			sorto[counter].pop_back();	
		}
	}

}




void Converter::biggest_color_range(std::vector<SDL_Color> &allPixels, int begin, int end) {

	
	int minir, minig, minib;
	minir = allPixels[begin].r;
	minig = allPixels[begin].g;
	minib = allPixels[begin].b;
	int maxir, maxig, maxib;
	maxir = allPixels[begin].r;
	maxig = allPixels[begin].g;
	maxib = allPixels[begin].b;


	for (int i = begin;i<end;i++) {

		if (allPixels[i].r<minir) {
			minir = allPixels[i].r;
		}
		if (allPixels[i].g<minig) {
			minig = allPixels[i].g;
		}
		if (allPixels[i].b<minib) {
			minib = allPixels[i].b;
		}
		if (allPixels[i].r>maxir) {
			maxir = allPixels[i].r;
		}
		if (allPixels[i].g>maxig) {
			maxig = allPixels[i].g;
		}
		if (allPixels[i].b>maxib) {
			maxib = allPixels[i].b;
		}
	}

	int r, g, b;
	int which_sort;  // 0 -sort by red , 1- sort by green , 2- sort by blue
	int biggest_range;
	r = maxir - minir;// 0- range of red
	g = maxig - minig;// 1 - range of green
	b = maxib - minib;// 2- range of blue

	which_sort = 0;
	biggest_range = r;

	if (g > biggest_range) {
		which_sort = 1;
		biggest_range = g;
	}

	if (b > biggest_range) {
		which_sort = 2;
		biggest_range = b;
	}

	sort_by_color(allPixels, begin, end, which_sort);

}


// just temporary solution pallete should be created based on image TODO :: 
std::array<SDL_Color, Constants::PALETTE_SIZE> Converter::createDedicatedPalette(Image* img) {

	std::array<SDL_Color, Constants::PALETTE_SIZE> palette;
	const int how_many_colors_in_palette = Constants::PALETTE_SIZE;
	int numer_of_all_pix = 0;
	std::vector<SDL_Color> allPixels;
	int width=img->getWidth();
	int height = img->getHeight();
	allPixels.resize(width*height);
	


	for (int i = 0;i < width; i++) {
		for (int j = 0;j < height;j++) {

			allPixels[numer_of_all_pix++] = img->getPixel(i,j);	//add all pixels to vector

		}
	}

	int divider = 1;
	int begin;
	int end;
	int range;

	for (int i = 0;i <= 8;i++) {				// 8 because 256 = 2^8
		begin = 0;
		end = 0;
		range = numer_of_all_pix / divider;
		for (int j = 0;j < divider;j++) {

			biggest_color_range(allPixels, begin, end + range);
			begin += range;
			end += range;

		}
		divider *= 2;
	}

	int range_of_one_color = numer_of_all_pix / how_many_colors_in_palette; // one color will be from that range of colors

	int R, G, B;
	int tempr, tempg, tempb;
	int temp_indeks = 0;
	for (int i = 0;i < how_many_colors_in_palette;i++) {
		R = 0;
		G = 0;
		B = 0;
		for (int j = 0;j < range_of_one_color;j++) {

			tempr=allPixels[temp_indeks].r;
			tempg = allPixels[temp_indeks].g;
			tempb = allPixels[temp_indeks].b;
			R += tempr;
			G += tempg;											//adding all variables of each color
			B += tempb;
			temp_indeks++;
			
		}
		palette[i].r = R / range_of_one_color;
		palette[i].g = G / range_of_one_color;					// dividing by number of colors used in addition
		palette[i].b = B / range_of_one_color;

	}
	return palette;

}

std::vector<std::vector<Constants::oxPixel>> Converter::createOxPixelsFromImage(Image* image) {
	std::vector<std::vector<Constants::oxPixel>> pixels;
	pixels.resize(image->getHeight()); // init vector
	for (int i = 0; i < image->getHeight(); ++i) {
		pixels[i].resize(image->getWidth()); // init vector
	}
	for (int y = 0; y < image->getHeight(); ++y) {
		for (int x = 0; x < image->getWidth(); ++x) {
			pixels[y][x] = sdlColorToOxPixel(image->getPixel(x, y));
		}
	}
	return pixels;
}

std::vector<std::vector<SDL_Color>> Converter::createSdlPixelsFromOx(Ox* ox) {
	std::vector<std::vector<SDL_Color>> pixels;
	pixels.resize(ox->height); // init vector
	for (int i = 0; i < ox->width; ++i) {
		pixels[i].resize(ox->height); // init vector
	}
	for (int y = 0; y < ox->height; ++y) {
		for (int x = 0; x < ox->width; ++x) {
			pixels[x][y] = oxPixelToSdlColor(ox->getPixel(x, y));
		}
	}
	return pixels;
}


uint8_t Converter::sdlColorToOxPixel(SDL_Color color) {
	uint8_t oxColor = 0;
	oxColor |= (color.r & Constants::MASK_FIRST_3_BITS);
	oxColor |= (color.g & Constants::MASK_FIRST_3_BITS) >> 3;
	oxColor |= (color.b & Constants::MASK_FIRST_2_BITS) >> 6;
	return oxColor;
}


SDL_Color Converter::oxPixelToSdlColor(Constants::oxPixel oxColor) {
	SDL_Color color;
	color.r = (oxColor & Constants::MASK_BITS_RED);
	color.g = (oxColor & Constants::MASK_BITS_GREEN) << 3;
	color.b = (oxColor & Constants::MASK_BITS_BLUE) << 6;
	color.a = 255;
	return color;
}


Ox Converter::convertImageToOx(Image* image) {
	int width = image->getWidth();
	int height = image->getHeight();
	int paletteType = 0; // refactor later
	std::vector<std::vector<Constants::oxPixel>> pixels = createOxPixelsFromImage(image);
	std::array<SDL_Color, Constants::PALETTE_SIZE> palette = createDedicatedPalette(image);
	return Ox(paletteType, width, height, pixels, palette);
}

Image Converter::convertOxToImage(Ox* ox) {
	std::vector<std::vector<SDL_Color>> pixels = createSdlPixelsFromOx(ox);
	int width = ox->width;
	int height = ox->height;
	return Image(width, height, pixels);
}


Converter::~Converter() {
}