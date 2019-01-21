#pragma once

class Constants
{
private:
	Constants();
public:
	static const int PALETTE_TYPE_BYTE_SHIFT = 3;
	static const int PALETTE_SIZE = 64;
	static const int PALETTE_BITS_SHIFT = 0;
	static const int MASK_6_BITS = 0b11000000;
	static const int MASK_6_BITS_RED = 0b00110000;
	static const int MASK_6_BITS_GREEN = 0b00001100;
	static const int MASK_6_BITS_BLUE = 0b00000011;
	~Constants();
};

