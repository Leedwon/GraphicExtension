#pragma once
#include <cstdint>
#include <vector>
#include "Constants.h"

class Compressor {
private:
	static void addSequenceOfDifferentSymbols(std::vector<uint8_t> &buffer, std::vector<uint8_t> &destination);
	static void addSequenceOfSameSymbols(std::vector<uint8_t> &destination, const uint8_t &symbol, const uint8_t &numberOfSymbols);
	static void addSequenceOfDifferentSymbolsByterun(std::vector<uint8_t> &buffer, std::vector<uint8_t> &destination, const uint8_t number_of_symbols);
	// checks for 3 following pixels starting from x and y if vector size is reached returns false
	static bool areThreeInRowSame(const std::vector<std::vector<Constants::oxPixel>> &pixels, int x, int y);
public:
	struct CompressedData {
		std::vector<uint8_t> pixels;
		Constants::compressionType compressionType;
	};
	//determines which compression is better and compress
	static CompressedData compress(const std::vector<std::vector<Constants::oxPixel>> &pixels);
	static std::vector<uint8_t> compressRle(const std::vector<std::vector<Constants::oxPixel>> &pixels);
	static std::vector<uint8_t> compressByteRun(const std::vector<std::vector<Constants::oxPixel>> &pixels);
	Compressor();
	~Compressor();
};