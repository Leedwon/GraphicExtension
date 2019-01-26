#include "Header.h"



Header::Header(Ox *ox, uint32_t sizeOfCompressedPixels, uint8_t compressionType) {
	pictureHeader.width = ox->width;
	pictureHeader.height = ox->height;
	pictureHeader.paletteType = ox->paletteType;
	pictureHeader.dithering = ox->dithering;
	pictureHeader.compressionType = compressionType;
	fileHeader.signature[0] = 'O';
	fileHeader.signature[1] = 'X';
	uint32_t offset = 0;
	offset += sizeof(fileHeader.signature);
	offset += sizeof(fileHeader.size);
	offset += sizeof(fileHeader.offsetToPixels);
	offset += sizeof(pictureHeader.width);
	offset += sizeof(pictureHeader.height);
	offset += sizeof(pictureHeader.paletteType);
	offset += sizeof(pictureHeader.dithering);
	//+pallete
	switch(ox->paletteType) {
	case Constants::paletteType::dedicated:
		offset += Constants::PALETTE_SIZE * sizeof(uint8_t) * 3;
		break;
	}
	fileHeader.offsetToPixels = offset;
	fileHeader.size = offset + sizeOfCompressedPixels;
}


Header::~Header()
{
}
