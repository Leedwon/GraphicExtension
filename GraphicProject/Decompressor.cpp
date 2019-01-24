#include "Decompressor.h"

Ox Decompressor::decompressRLE(const std::vector<uint8_t> &compressedPixelData)
{
	Ox imageData;
	int numToRepeat;
	int numToCopy;

	int row = 0;
	int col = 0;

	int posInVector = 0;

	while (posInVector < compressedPixelData.size())
	{
		//Copy sequence
		if (compressedPixelData[posInVector] == 0)
		{
			++posInVector; //Advance to next position and chceck how many items to copy
			numToCopy = compressedPixelData[posInVector];

			for (int i = 0; i < numToCopy; ++i)
			{
				if (col < imageData.width)
				{
					++posInVector;

					imageData.pixels[row][col] = compressedPixelData[posInVector];
					++col;
				}
				else //If col index is greater than width of image advance to next row
				{
					++row;
					col = 0;

					++posInVector;

					imageData.pixels[row][col] = compressedPixelData[posInVector];
					++col;
				}
			}

			++posInVector;
		}

		//Repeat sequence
		if (compressedPixelData[posInVector] != 0)
		{
			numToRepeat = compressedPixelData[posInVector];
			++posInVector; //Stay at this position until for loop ends

			for (int i = 0; i < numToRepeat; ++i)
			{
				if (col < imageData.width)
				{
					imageData.pixels[row][col] = compressedPixelData[posInVector];
					++col;
				}
				else //If col index is greater than width of image advance to next row
				{
					++row;
					col = 0;

					imageData.pixels[row][col] = compressedPixelData[posInVector];
					++col;
				}
			}

			++posInVector;
		}
	}

	return imageData;
}

Ox Decompressor::decopressByteRun(const std::vector<uint8_t> &compressedPixelData)
{
	Ox imageData;
	int numToCopy;
	int numToRepeat;

	int row = 0;
	int col = 0;

	int posInVector = 0;

	while (posInVector < compressedPixelData.size())
	{
		//Copy sequence
		if (compressedPixelData[posInVector] < 128) //Value range for copy: 0-127
		{
			numToCopy = compressedPixelData[posInVector] + 1; //Copy n+1 following bytes

			for (int i = 0; i < numToCopy; ++i)
			{
				if (col < imageData.width)
				{
					++posInVector;

					imageData.pixels[row][col] = compressedPixelData[posInVector];
					++col;
				}
				else //If col index is greater than width of image advance to next row
				{
					++row;
					col = 0;

					++posInVector;

					imageData.pixels[row][col] = compressedPixelData[posInVector];
					++col;
				}
			}

			++posInVector;
		}

		//Repeat sequence
		if (compressedPixelData[posInVector] >= 128) //Value range for repeat: 128-255
		{
			numToRepeat = (compressedPixelData[posInVector] - 128) + 1; //Scale repeat value and repeat following byte n+1 times
			++posInVector; //Stay at this position until for loop ends

			for (int i = 0; i < numToRepeat; ++i)
			{
				if (col < imageData.width)
				{
					imageData.pixels[row][col] = compressedPixelData[posInVector];
					++col;
				}
				else //If col index is greater than width of image advance to next row
				{
					++row;
					col = 0;

					imageData.pixels[row][col] = compressedPixelData[posInVector];
					++col;
				}
			}

			++posInVector;
		}
	}

	return imageData;
}