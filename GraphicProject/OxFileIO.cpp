#include "OxFileIO.h"
#include "Compressor.h"
#include "Decompressor.h"


Ox* OxFileIO::readOx(std::string fileName)
{
	std::ifstream is(fileName, std::ios::in | std::ios::binary);
	Ox *ox = new Ox();
	try
	{

			uint32_t size;
			uint32_t offsetToPixels;
			uint8_t compressionType;
			uint8_t palette;
			is >> palette;
			is >> palette; //droping signature
			is.read((char*)&size, sizeof(size));
			is.read((char*)&offsetToPixels, sizeof(offsetToPixels));
			is.read((char*)&ox->width, sizeof(ox->width));
			is.read((char*)&ox->height, sizeof(ox->height));
			is.read((char*)&palette, sizeof(palette));
			ox->paletteType = Header::intToPaletteType(palette);
			is.read((char*)&compressionType, sizeof(compressionType));
			switch (ox->paletteType)
			{
			case Constants::paletteType::dedicated:
			case Constants::dedicatedDith:
				for (int i = 0; i < Constants::PALETTE_SIZE; i++)
				{
					is.read((char*)&ox->colorPalette[i].r, sizeof(ox->colorPalette[i].r));
					is.read((char*)&ox->colorPalette[i].g, sizeof(ox->colorPalette[i].g));
					is.read((char*)&ox->colorPalette[i].b, sizeof(ox->colorPalette[i].b));
				}
				break;
			}
			std::vector<uint8_t> compressedPixels;
			compressedPixels.resize(size - offsetToPixels);
			for (int i = 0; i < compressedPixels.size(); i++)
			{
				is.read((char*)&compressedPixels[i], sizeof(compressedPixels[i]));
			}
			std::vector<uint8_t> decompressedPixels;
			switch(compressionType)
			{
			case Constants::COMPRESSION_RLE:
				decompressedPixels = Decompressor::decompressRLE(compressedPixels);
				break;
			case Constants::COMPRESSION_BYTE_RUN:
				decompressedPixels = Decompressor::decopressByteRun(compressedPixels);
				break;
			}
			if (ox->paletteType == Constants::dedicated || ox->paletteType == Constants::dedicatedDith || ox->paletteType == Constants::imposed) {
				ox->paletteIndexes.resize(ox->height);
				for (int i = 0; i < ox->height; i++)
				{
					ox->paletteIndexes[i].resize(ox->width);
					for (int j = 0; j < ox->width; j++)
					{
						ox->paletteIndexes[i][j] = decompressedPixels[i*ox->width + j];
					}
				}
			} else
			{
				ox->pixels.resize(ox->height);
				for (int i = 0; i < ox->height; i++)
				{
					ox->pixels[i].resize(ox->width);
					for (int j = 0; j < ox->width; j++)
					{
						ox->pixels[i][j] = decompressedPixels[i*ox->width + j];
					}
				}
			}
	}catch (std::exception& e)
	{
		
	}
	is.close();
	return ox;
}

bool OxFileIO::saveOx(std::string fileName, Ox *ox)
{
	std::ofstream os(fileName, std::ios::out | std::ios::binary);
	if(!os.is_open())
	{
		return false;
	}
	try
	{
	Compressor:Compressor::CompressedData compressedData;
		if (ox->paletteType == Constants::dedicated || ox->paletteType == Constants::dedicatedDith || ox->paletteType == Constants::imposed) {
			compressedData = Compressor::compress(ox->paletteIndexes);
		} else
		{
			compressedData = Compressor::compress(ox->pixels);
		}
		std::vector<uint8_t> compressedPixels = compressedData.pixels;
		uint8_t compressionType = compressedData.compressionType;
		Header header(ox, compressedPixels.size(), compressionType);
		os << header.fileHeader.signature[0];
		os << header.fileHeader.signature[1];
		//os << header.fileHeader.size;
		os.write((char*)&header.fileHeader.size, sizeof(header.fileHeader.size));
		os.write((char*)&header.fileHeader.offsetToPixels, sizeof(header.fileHeader.offsetToPixels));
		os.write((char*)&header.pictureHeader.width, sizeof(header.pictureHeader.width));
		os.write((char*)&header.pictureHeader.height, sizeof(header.pictureHeader.height));
		os.write((char*)&header.pictureHeader.paletteType, sizeof(header.pictureHeader.paletteType));
		os.write((char*)&header.pictureHeader.compressionType, sizeof(header.pictureHeader.compressionType));
		switch (ox->paletteType) {
		case Constants::paletteType::dedicated:
		case Constants::dedicatedDith:
			for (int i = 0; i < ox->colorPalette.size(); i++)
			{
				os.write((char*)&ox->colorPalette[i].r, sizeof(ox->colorPalette[i].r));
				os.write((char*)&ox->colorPalette[i].g, sizeof(ox->colorPalette[i].g));
				os.write((char*)&ox->colorPalette[i].b, sizeof(ox->colorPalette[i].b));
			}
			break;
		}
		for(int i = 0; i < compressedPixels.size(); i++)
		{
			os.write((char*)&compressedPixels[i], sizeof(compressedPixels[i]));
		}
		
	} catch (std::exception& e)
	{
		return false;
	}
	os.close();
	return true;
}
