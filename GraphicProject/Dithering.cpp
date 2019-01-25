#include "Dithering.h"

std::vector<std::vector<uint8_t>> Dithering::ditheringGreyScale(const std::vector<std::vector<uint8_t>> &pixelData)
{
	//Get height and width of current image
	int height = pixelData.size();
	int width = pixelData[0].size();

	//Data of each pixel after dithering, values are 0 or 1 for black or white
	std::vector<std::vector<uint8_t>> ditheringData(height, std::vector<uint8_t>(width, 0));

	float** errorData = new float*[height + 1]; //Additional row because error is always distributed to the line underneath

	for (int i = 0; i < height + 1; ++i)
	{
		errorData[i] = new float[width + 2]; //Two additional columns because error is always distributed to the next and previous column
	}

	memset(errorData, 0, sizeof(errorData)); //All currrent errors are equal to 0

	int shift = 1; //For pixel 0,0 starting point in errorArray is 0,1 because error always spreads one element backwards
	int greyScaleValue; //Value of grey scale for the current pixel x,y
	float error; //Current error value for pixel x,y

	//Pixels are analyzed left to right, top to bottom
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			greyScaleValue = pixelData[y][x];

			if (greyScaleValue + errorData[y][x + shift] < 128) //If grey scale value for cutrrent pixel is less than 128 it is set to black (0)
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

	for (int i = 0; i < height + 1; ++i)
	{
		delete[] errorData[i];
	}

	delete[] errorData;

	return ditheringData;
}