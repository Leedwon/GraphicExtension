#pragma once
#include <vector>
#include "Constants.h"
#include "Ox.h"

class Decompressor
{
	public:

		static Ox decompressRLE(const std::vector<uint8_t> &compressedPixelData);
		static Ox decopressByteRun(const std::vector<uint8_t> &compressedPixelData);

		Decompressor();
		~Decompressor();
};