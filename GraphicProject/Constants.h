#pragma once
#include <cstdint>

class Constants {
private:
	Constants();
public:
	/*
	 * not sure if store it here or in Ox.h but this is definiately making code cleaner,
	 * name changed to oxPixel because we don't store colors always sometimes it is index in palette
	 */
	typedef uint8_t oxPixel; 
	enum PALETTE_TYPES {none, dedicated, grey, imposed }; // when paletteType = none we store each pixel as oxPixel 
	static const int SIGNATURE_SIZE = 2;
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

