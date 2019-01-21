#pragma once
#include <cstdint>
#include "Constants.h"
#include "Ox.h"

class Header {
private:
	// struct or separate class?
	struct FileHeader {
		char signature[Constants::SIGNATURE_SIZE];
		uint32_t size;
		uint32_t offsetToPixels;
	};
	// struct or separate class?
	struct PictureHeader {
		uint32_t width;
		uint32_t height;
		uint8_t paletteType;
	};
public:
	FileHeader fileHeader;
	PictureHeader pictureHeader;
	Header(Ox *ox);
	~Header();
};

