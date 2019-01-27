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
		uint8_t compressionType;
	};
public:
	FileHeader fileHeader{};
	PictureHeader pictureHeader{};
	uint8_t static paletteTypeToInt(Constants::paletteType palette);
	Constants::paletteType static intToPaletteType(uint8_t palette);
	Header(Ox* ox, uint32_t sizeOfCompressedPixels, uint8_t compressionType);
	~Header();
};

