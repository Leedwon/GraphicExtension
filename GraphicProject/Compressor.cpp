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

//To Do
std::vector<uint8_t> Compressor::compress(const std::vector<std::vector<Constants::oxPixel>>& pixels)
{
	return Compressor::compressByteRun(pixels); 
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

	int type_restriction = 127;


	std::vector<uint8_t> compressed;
	std::vector<uint8_t> buffer;
	uint8_t previous = pixels[0][0]; // take first pixel
	uint8_t current=pixels[0][0];
	uint8_t how_many_same = 0;
	uint8_t how_many_diff = 0;
	uint8_t last_same;
	for (int y = 0; y < pixels.size(); ++y) {
		for (int x = 0; x < pixels[y].size(); ++x) {

			current = pixels[y][x];

			while (current == previous && x<pixels[y].size()-1) {

				how_many_same++;															//  increase how_many_same if two first are the same 
				previous = current;															// so we already got !(numer of same symbols) +1
				last_same = current;
				current = pixels[y][++x];
				if (how_many_same == type_restriction ) {
					addSequenceOfSameSymbols(compressed, previous, how_many_same+128);	//  add symbols if number is higher then 127
					how_many_same = 0;																	// and because it should be on minus we save it as bigger than 127
					break;																		// do break to not count same number twice time
				}
			}


			if (how_many_same == -1) {

				if (x - 4 > 0 && x < pixels[y].size() - 2 && how_many_diff<type_restriction-3) {	// we check if we wont exceed size value of vector and if we had enought space to save numbers
					if (pixels[y][x - 3] != pixels[y][x - 4] && pixels[y][x + 1] != pixels[y][x + 2]) { // we check if previous are two different 
						how_many_diff += 2;
						buffer.push_back(last_same);														// if they are we add 2 same numbers to buffer
						buffer.push_back(last_same);
						how_many_same = 0;

					}
				}
			}


			if (how_many_same > 0 && how_many_diff>0) {										// add diff numbers

				addSequenceOfDifferentSymbolsByterun(buffer, compressed,how_many_diff-1);  //need to decreas how_many_diff becaouse it is equal to the number of symbols 
				how_many_diff = 0;
			}

			if (how_many_same > 0) {

				addSequenceOfSameSymbols(compressed, previous, how_many_same+128);		// add same numbers
				how_many_same = 0;																		// and because it should be on minus we save it as bigger than 127

			}

			if (pixels[y].size() - 1 == x) {	// if it is last kolor we need to add this to list of different 
				how_many_diff += 1;
				buffer.push_back(current);
				x++;
			}


			while (current != previous && x<pixels[y].size()) {
				previous = current;
				if (x < pixels[y].size() - 2) {
					if (pixels[y][x + 1] != current) {								// need to check it to not save the first of same pixels to the different pixels 
						current = pixels[y][++x];
					}
					else {
						break;
					}
				}
				how_many_diff++;
				buffer.push_back(previous);

				if (how_many_diff == type_restriction) {
					addSequenceOfDifferentSymbolsByterun(buffer, compressed, how_many_diff - 1);		//add different numbers if how_many_diff is equal 127(type restriction)
					
					how_many_diff = 0;
				}
			}





		}

		if (how_many_diff>0) {										// add diff numbers on the end of line

			addSequenceOfDifferentSymbolsByterun(buffer, compressed, how_many_diff - 1);  //need to decreas how_many_diff becaouse it is equal to the number of symbols 
			how_many_diff = 0;
		}
	}
	
	
		return compressed;
}





Compressor::Compressor() {
}


Compressor::~Compressor() {
}


std::vector<uint8_t> Compressor::compress(const std::vector<std::vector<Constants::oxPixel>> &pixels) {

	std::vector<uint8_t> compressed_rle = compressRle(pixels);

	std::vector<uint8_t> compressed_byterun = compressByteRun(pixels);
	
	if (compressed_rle.size() > compressed_byterun.size()) {
		return  compressed_rle;
	}else{
		return  compressed_byterun;
	}

}
