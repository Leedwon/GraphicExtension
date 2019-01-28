#include "Compressor.h"


bool Compressor::areThreeInRowSame(const std::vector<std::vector<Constants::oxPixel>>& pixels, int x, int y) {
	if (y >= pixels.size() - 1 && x >= pixels[y].size() - 2) // we can't take three pixels - outOfBounds
		return false;
	Constants::oxPixel previous = pixels[y][x];
	int index = x;
	for (int i = 0; i < 3; i++) {
		// getting 3 pixels
		if (index == pixels[y].size()) {
			index = 0;
			y++;
		}
		Constants::oxPixel current = pixels[y][index];
		index++;
		if (previous != current)
			return false;
		previous = current;
	}
	return true;
}


void Compressor::addSequenceOfDifferentSymbols(std::vector<uint8_t> &buffer, std::vector<uint8_t> &destination) {
	destination.push_back(0); // inform that we will be copying next buffer.size() amount of bits
	destination.push_back(static_cast<uint8_t>(buffer.size())); // how many to copy
	for (int i = 0; i < buffer.size(); ++i) {
		destination.push_back(buffer[i]);
	}
	buffer.clear();
}

void Compressor::addSequenceOfSameSymbols(std::vector<uint8_t>& destination, const uint8_t &symbol, const uint8_t &numberOfSymbols) {
	destination.push_back(numberOfSymbols);
	destination.push_back(symbol);
}

std::vector<uint8_t> Compressor::compressRle(const std::vector<std::vector<Constants::oxPixel>>& pixels) {
	int typeRestriction = 255; // 8 bits;
	std::vector<uint8_t> compressed;
	std::vector<uint8_t> buffer;
	uint8_t previous = pixels[0][0]; // take first pixel
	uint8_t current;
	uint8_t sameCount = 0; // in first iteration it will always increment
	bool threeInRowSame = false;
	bool wasSame = false;
	for (int y = 0; y < pixels.size(); ++y) {
		for (int x = 0; x < pixels[y].size(); ++x) {
			current = pixels[y][x];
			bool isSame = previous == current ? true : false;
			if (!threeInRowSame)
				threeInRowSame = areThreeInRowSame(pixels, x, y); // when we found that there will be 3 same in row there is no point in updating it after every iteration now we wait for different symbol / end to occur.
			if (isSame) {
				sameCount++;
				if (sameCount == typeRestriction) { // force write because max val for uint8_t is 255
					addSequenceOfSameSymbols(compressed, current, sameCount);
					sameCount = 0;
				}
			}
			if (!isSame && wasSame && sameCount >= 3) {
				addSequenceOfSameSymbols(compressed, previous, sameCount);
				sameCount = 1;
				threeInRowSame = areThreeInRowSame(pixels, x, y); // we have to check again if there will be 3 same in row
			}
			if (!threeInRowSame) {
				if (buffer.size() == typeRestriction) // force write because max val for uint8_t is 255
					addSequenceOfDifferentSymbols(buffer, compressed);
				buffer.push_back(current);
				// i.e AAABB case when we are  taking 2nd B into account, different behaviour then CABBAC
				if (isSame && sameCount == 2 && buffer.size() == 2) {
					addSequenceOfSameSymbols(compressed, current, sameCount);
					buffer.clear();
					sameCount = 1;
				}
				sameCount = 1;
			} else if (buffer.size() > 0) {
				addSequenceOfDifferentSymbols(buffer, compressed);
			}
			wasSame = isSame;
			previous = current;
		}
	}
	if (sameCount > 2) {
		addSequenceOfSameSymbols(compressed, current, sameCount);
	}
	if (buffer.size() > 0) {
		addSequenceOfDifferentSymbols(buffer, compressed);
	}
	return compressed;
}

void Compressor::addSequenceOfDifferentSymbolsByterun(std::vector<uint8_t> &buffer, std::vector<uint8_t> &destination, const uint8_t number_of_symbols) {

	destination.push_back(number_of_symbols);
	for (int i = 0; i < buffer.size(); ++i) {
		destination.push_back(buffer[i]);
	}
	buffer.clear();

}

std::vector<uint8_t> Compressor::compressByteRun(const std::vector<std::vector<Constants::oxPixel>> &pixels) {


int typeRestriction = 127; // 8 bits divided by two;
std::vector<uint8_t> compressed;
std::vector<uint8_t> buffer;
uint8_t previous = pixels[0][0]; // take first pixel
uint8_t current;
uint8_t sameCount = 0; // in first iteration it will always increment
bool threeInRowSame = false;
bool wasSame = false;
for (int y = 0; y < pixels.size(); ++y) {
	for (int x = 0; x < pixels[y].size(); ++x) {
		current = pixels[y][x];
		bool isSame = previous == current ? true : false;
		if (!threeInRowSame)
			threeInRowSame = areThreeInRowSame(pixels, x, y); // when we found that there will be 3 same in row there is no point in updating it after every iteration now we wait for different symbol / end to occur.
		if (isSame) {
			sameCount++;
			if (sameCount == typeRestriction) { // force write because max val for uint8_t is 255
				addSequenceOfSameSymbols(compressed, current, sameCount-1+128);
				sameCount = 0;
			}
		}
		if (!isSame && wasSame && sameCount >= 3) {
			addSequenceOfSameSymbols(compressed, previous, sameCount - 1 + 128);
			sameCount = 1;
			threeInRowSame = areThreeInRowSame(pixels, x, y); // we have to check again if there will be 3 same in row
		}
		if (!threeInRowSame) {
			if (buffer.size() == typeRestriction) // force write because max val for uint8_t is 255
			//	addSequenceOfDifferentSymbols(buffer, compressed);
				addSequenceOfDifferentSymbolsByterun(buffer, compressed, buffer.size() - 1);
			buffer.push_back(current);
			// i.e AAABB case when we are  taking 2nd B into account, different behaviour then CABBAC
			if (isSame && sameCount == 2 && buffer.size() == 2) {
				addSequenceOfSameSymbols(compressed, current, sameCount - 1 + 128);
				buffer.clear();
				sameCount = 1;
			}
			sameCount = 1;
		}
		else if (buffer.size() > 0) {
			addSequenceOfDifferentSymbolsByterun(buffer, compressed, buffer.size() - 1);

			//addSequenceOfDifferentSymbols(buffer, compressed);
		}
		wasSame = isSame;
		previous = current;
	}
}
if (sameCount > 2) {
	addSequenceOfSameSymbols(compressed, current, sameCount - 1 + 128);
}
if (buffer.size() > 0) {
	addSequenceOfDifferentSymbolsByterun(buffer, compressed, buffer.size() - 1);
	//addSequenceOfDifferentSymbols(buffer, compressed);
}
return compressed;


}


Compressor::Compressor() {
}


Compressor::~Compressor() {
}


Compressor::CompressedData Compressor::compress(const std::vector<std::vector<Constants::oxPixel>>& pixels) {
	CompressedData result;
	std::vector<uint8_t> compressed_rle = compressRle(pixels);

	std::vector<uint8_t> compressed_byterun = compressByteRun(pixels);
	
	if (compressed_rle.size() > compressed_byterun.size()) {
		result.pixels = compressed_byterun;
		result.compressionType = Constants::byteRun;
	} else {
		result.pixels = compressed_rle;
		result.compressionType = Constants::rle;
	}

	result.pixels = compressed_byterun;
	result.compressionType = Constants::byteRun;

	return result;
}
