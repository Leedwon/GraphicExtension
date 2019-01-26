#include "Utilities.h"

SDL_Color operator+(const SDL_Color& l, const SDL_Color& r) {
	SDL_Color result;
	result.r = l.r + r.r;
	result.g = l.g + r.g;
	result.b = l.b + r.b;
	return result;
}

SDL_Color operator-(const SDL_Color& l, const SDL_Color& r) {
	SDL_Color result;
	result.r = l.r - r.r;
	result.g = l.g - r.g;
	result.b = l.b - r.b;
	return result;

}

bool operator==(const SDL_Color& l, const SDL_Color& r) {
	if (l.r == r.r) {
		if (l.g == r.g) {
			if (l.b == r.b)
				return true;
		}
	}
	return false;
}

bool operator!=(const SDL_Color& l, const SDL_Color& r) {
	if (l.r != r.r) {
		if (l.g != r.g) {
			if (l.b != r.b)
				return true;
		}
	}
	return false;
}

void renderText(SDL_Renderer* renderer, std::string text, TTF_Font* font, SDL_Rect* background, SDL_Color textColor) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(renderer, textTexture, NULL, background);
	SDL_RenderPresent(renderer);
}

int distanceBetweenColors(const SDL_Color& imageColor, const SDL_Color& paletteColor) {
	return (pow(imageColor.r - paletteColor.r, 2) + pow(imageColor.g - paletteColor.g, 2) + pow(
		imageColor.b - paletteColor.b, 2));
}

std::vector<std::vector<uint8_t>> ditheringGreyScale(const std::vector<std::vector<uint8_t>>& pixelData) {
	//Get height and width of current image
	int height = pixelData.size();
	int width = pixelData[0].size();

	//Data of each pixel after dithering, values are 0 or 1 for black or white
	std::vector<std::vector<uint8_t>> ditheringData(height, std::vector<uint8_t>(width, 0));

	float** errorData = new float*[height + 1];
	//Additional row because error is always distributed to the line underneath

	for (int i = 0; i < height + 1; ++i) {
		errorData[i] = new float[width + 2];
		//Two additional columns because error is always distributed to the next and previous column
	}

	//Initialize all error values to 0
	for (int i = 0; i < height + 1; ++i)
	{
		for (int j = 0; j < width + 2; ++j)
		{
			errorData[i][j] = 0;
		}
	}

	int shift = 1;
	//For pixel 0,0 starting point in errorArray is 0,1 because error always spreads one element backwards
	int greyScaleValue; //Value of grey scale for the current pixel x,y
	float error; //Current error value for pixel x,y

	//Pixels are analyzed left to right, top to bottom
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			greyScaleValue = pixelData[y][x];

			if (greyScaleValue + errorData[y][x + shift] < 128)
				//If grey scale value for cutrrent pixel is less than 128 it is set to black (0)
			{
				ditheringData[y][x] = 0;
				error = greyScaleValue + errorData[y][x + shift];
			}
			else //If grey scale value for current pixel is greater or equal 128 it is set to white (255)
			{
				ditheringData[y][x] = 255;
				error = greyScaleValue + errorData[y][x + shift] - 255;
			}

			//Spread the error to all neighbors
			errorData[y][x + shift + 1] += (error * 7.0 / 16.0);
			errorData[y + 1][x + shift + 1] += (error * 1.0 / 16.0);
			errorData[y + 1][x + shift] += (error * 5.0 / 16.0);
			errorData[y + 1][x + shift - 1] += (error * 3.0 / 16.0);
		}
	}

	for (int i = 0; i < height + 1; ++i) {
		delete[] errorData[i];
	}

	delete[] errorData;

	return ditheringData;
}

std::vector<std::vector<uint8_t>> ditheringColor(const std::vector<std::vector<SDL_Color>> &pixelMap, Ox &targetImage)
{
	//Get height and width of current image
	int height = pixelMap.size();
	int width = pixelMap[0].size();

	//Data of each pixel after dithering, unknown at the beginig thus values are 0
	std::vector<std::vector<uint8_t>> ditheringData(height, std::vector<uint8_t>(width, 0));

	//Additional row because error is always distributed to the line underneath
	float** errorDataRed = new float*[height + 1];
	float** errorDataGreen = new float*[height + 1];
	float** errorDataBlue = new float*[height + 1];

	for (int i = 0; i < height + 1; ++i) {
		//Two additional columns because error is always distributed to the next and previous column
		errorDataRed[i] = new float[width + 2];
		errorDataGreen[i] = new float[width + 2];
		errorDataBlue[i] = new float[width + 2];
	}

	//Initialize all error values to 0
	for (int i = 0; i < height + 1; ++i)
	{
		for (int j = 0; j < width + 2; ++j)
		{
			errorDataRed[i][j] = 0;
			errorDataGreen[i][j] = 0;
			errorDataBlue[i][j] = 0;
		}
	}

	//For pixel 0,0 starting point in errorArray is 0,1 because error always spreads one element backwards
	int shift = 1;

	SDL_Color currentPixelValue;

	//Error value variables for each color
	float errorRed;
	float errorGreen;
	float errorBlue;

	//Variables used to save index and distance of closest color form palete to current pixel from image
	int closestColorIndex;
	unsigned long long int closestColor;
	unsigned long long int currentClosestColor;

	//Auxiliary loop variable
	int i;

	//Pixels are analyzed left to right, top to bottom
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			currentPixelValue = pixelMap[y][x];

			//Find distance between current pixel from image and first color from palete
			closestColor = static_cast<unsigned long long int>(
				(currentPixelValue.r + errorDataRed[y][x + shift] - targetImage.colorPalette[0].r)*(currentPixelValue.r + errorDataRed[y][x + shift] - targetImage.colorPalette[0].r)
				+ (currentPixelValue.g + errorDataGreen[y][x + shift] - targetImage.colorPalette[0].g)*(currentPixelValue.g + errorDataGreen[y][x + shift] - targetImage.colorPalette[0].g)
				+ (currentPixelValue.b + errorDataBlue[y][x + shift] - targetImage.colorPalette[0].b)*(currentPixelValue.b + errorDataBlue[y][x + shift] - targetImage.colorPalette[0].b) );

			i = 0;

			//Check wether other colors in palete are closer to current pixel than the first one
			for (i = 1; i < Constants::PALETTE_SIZE; ++i)
			{
				currentClosestColor = static_cast<unsigned long long int>(
					(currentPixelValue.r + errorDataRed[y][x + shift] - targetImage.colorPalette[i].r)*(currentPixelValue.r + errorDataRed[y][x + shift] - targetImage.colorPalette[i].r)
					+ (currentPixelValue.g + errorDataGreen[y][x + shift] - targetImage.colorPalette[i].g)*(currentPixelValue.g + errorDataGreen[y][x + shift] - targetImage.colorPalette[i].g)
					+ (currentPixelValue.b + errorDataBlue[y][x + shift] - targetImage.colorPalette[i].b)*(currentPixelValue.b + errorDataBlue[y][x + shift] - targetImage.colorPalette[i].b) );

				//If so set the closer color as current closest and save it's index
				if (currentClosestColor < closestColor)
				{
					closestColor = currentClosestColor;

					closestColorIndex = i;
				}
			}

			//Save index of closest color from palete in dithered image data array
			ditheringData[y][x] = closestColorIndex;

			//Calculate current error value for each color
			errorRed = currentPixelValue.r - targetImage.colorPalette[closestColorIndex].r;
			errorGreen = currentPixelValue.g - targetImage.colorPalette[closestColorIndex].g;
			errorBlue = currentPixelValue.b - targetImage.colorPalette[closestColorIndex].b;


			//Spread the error to all neighbors for each color
			errorDataRed[y][x + shift + 1] += (errorRed * 7.0 / 16.0);
			errorDataRed[y + 1][x + shift + 1] += (errorRed * 1.0 / 16.0);
			errorDataRed[y + 1][x + shift] += (errorRed * 5.0 / 16.0);
			errorDataRed[y + 1][x + shift - 1] += (errorRed * 3.0 / 16.0);

			errorDataGreen[y][x + shift + 1] += (errorGreen * 7.0 / 16.0);
			errorDataGreen[y + 1][x + shift + 1] += (errorGreen * 1.0 / 16.0);
			errorDataGreen[y + 1][x + shift] += (errorGreen * 5.0 / 16.0);
			errorDataGreen[y + 1][x + shift - 1] += (errorGreen * 3.0 / 16.0);

			errorDataBlue[y][x + shift + 1] += (errorBlue * 7.0 / 16.0);
			errorDataBlue[y + 1][x + shift + 1] += (errorBlue * 1.0 / 16.0);
			errorDataBlue[y + 1][x + shift] += (errorBlue * 5.0 / 16.0);
			errorDataBlue[y + 1][x + shift - 1] += (errorBlue * 3.0 / 16.0);
		}
	}

	for (int i = 0; i < height + 1; ++i)
	{
		delete[] errorDataRed[i];
		delete[] errorDataGreen[i];
		delete[] errorDataBlue[i];
	}

	delete[] errorDataRed;
	delete[] errorDataGreen;
	delete[] errorDataBlue;

	return ditheringData;
}

void tooSmallSurfaceExceptionHandle(SDL_Renderer* renderer, TTF_Font* font) {
	SDL_SetRenderDrawColor(renderer, Constants::APP_BACKGROUND.r, Constants::APP_BACKGROUND.g, Constants::APP_BACKGROUND.b, Constants::APP_BACKGROUND.a);
	SDL_RenderClear(renderer);
	SDL_Rect exceptionRect{ 0, 0, Constants::WIDTH, Constants::BUTTON_HEIGHT };
	renderText(renderer, Constants::EXCEPTION_TOO_SMALL_SURFACE, font, &exceptionRect, { 255, 255, 255, 1 });
}
