#pragma once
#include <cstdint>

class Constants {
private:
	Constants();
public:
	typedef uint8_t oxColor; // not sure if store it here or in Ox.h but this is definiately making code cleaner
	static const int PALETTE_TYPE_BYTE_SHIFT = 3;
	static const int PALETTE_SIZE = 64;
	static const int PALETTE_BITS_SHIFT = 0;
	static const int MASK_FIRST_2_BITS = 0b11000000;
	static const int MASK_FIRST_3_BITS = 0b11100000;
	static const int MASK_BITS_RED = 0b11100000;
	static const int MASK_BITS_GREEN = 0b00011100;
	static const int MASK_BITS_BLUE = 0b0000011;
	~Constants();
};

