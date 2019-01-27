#include "Header.h"


uint8_t Header::paletteTypeToInt(Constants::paletteType palette)
{
	switch (palette)
	{
	case Constants::paletteType::none:
		return 0;
	case Constants::paletteType::dedicated:
		return 1;
	case Constants::paletteType::grey:
		return 2;
	case Constants::paletteType::imposed:
		return 3;
	case Constants::paletteType::bwDith:
		return 4;
	case Constants::paletteType::dedicatedDith:
		return 5;
	}
}

Constants::paletteType Header::intToPaletteType(uint8_t palette)
{
	switch (palette)
	{
	case 0:
		return Constants::paletteType::none;
	case 1:
		return Constants::paletteType::dedicated;
	case 2:
		return Constants::paletteType::grey;
	case 3:
		return Constants::paletteType::imposed;
	case 4:
		return Constants::paletteType::bwDith;
	case 5:
		return Constants::paletteType::dedicatedDith;
	}
}

Header::Header(Ox *ox, uint32_t sizeOfCompressedPixels, uint8_t compressionType) {
	pictureHeader.width = ox->width;
	pictureHeader.height = ox->height;
	pictureHeader.paletteType = paletteTypeToInt(ox->paletteType);
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
	offset += sizeof(pictureHeader.compressionType);
	//+pallete
	switch(ox->paletteType) {
	case Constants::paletteType::dedicated:
	case Constants::paletteType::dedicatedDith:
		offset += Constants::PALETTE_SIZE * sizeof(uint8_t) * 3;
		break;
	}
	fileHeader.offsetToPixels = offset;
	fileHeader.size = offset + sizeOfCompressedPixels;
}


Header::~Header()
{
}
