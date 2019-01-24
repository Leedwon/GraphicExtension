#pragma once
#include <vector>
#include "Constants.h"
#include "Ox.h"

class Decompressor
{
	public:

		static std::vector<uint8_t> decompressRLE(const std::vector<uint8_t> &compressedPixelData);
		static std::vector<uint8_t> decopressByteRun(const std::vector<uint8_t> &compressedPixelData);
		Decompressor();
		~Decompressor();
};