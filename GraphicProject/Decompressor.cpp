#include "Decompressor.h"

std::vector<uint8_t> Decompressor::decompressRLE(const std::vector<uint8_t> &compressedPixelData)
{
	std::vector<uint8_t> decompressedPixelData;
	int numToRepeat;
	int numToCopy;

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
				++posInVector; //Each time advance to next position to get value to copy

				decompressedPixelData.push_back(compressedPixelData[posInVector]);
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
				decompressedPixelData.push_back(compressedPixelData[posInVector]);
			}

			++posInVector;
		}
	}

	return decompressedPixelData;
}

std::vector<uint8_t> Decompressor::decopressByteRun(const std::vector<uint8_t> &compressedPixelData)
{
	std::vector<uint8_t> decompressedPixelData;
	int numToCopy;
	int numToRepeat;

	int posInVector = 0;

	while (posInVector < compressedPixelData.size())
	{
		//Copy sequence
		if (compressedPixelData[posInVector] < 128) //Value range for copy: 0-127
		{
			numToCopy = compressedPixelData[posInVector] + 1; //Copy n+1 following bytes

			for (int i = 0; i < numToCopy; ++i)
			{
				++posInVector; //Each time advance to next position to get value to copy

				decompressedPixelData.push_back(compressedPixelData[posInVector]);
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
				decompressedPixelData.push_back(compressedPixelData[posInVector]);
			}

			++posInVector;
		}
	}

	return decompressedPixelData;
}