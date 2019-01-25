#pragma once
#include <vector>
#include "Constants.h"

class Dithering
{
	public:

		std::vector<std::vector<uint8_t>> ditheringGreyScale(const std::vector<std::vector<uint8_t>> &pixelData);

		Dithering();
		~Dithering();
};