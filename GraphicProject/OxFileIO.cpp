#include "OxFileIO.h"
#include "Compressor.h"
#include "Decompressor.h"


Ox* OxFileIO::readOx(std::string fileName)
{
	std::ifstream is(fileName);
	Ox *ox = new Ox();
	try
	{
		char signature[Constants::SIGNATURE_SIZE];
		is >> signature;
		if (strcmp(signature, "OX") == 0)
		{
			uint32_t size;
			uint32_t offsetToPixels;
			uint8_t compressionType;
			uint8_t palette;
			is >> size;
			is >> offsetToPixels;
			is >> ox->width;
			is >> ox->height;
			is >> palette;
			ox->paletteType = Header::intToPaletteType(palette);
			is >> compressionType;
			switch (ox->paletteType)
			{
			case Constants::paletteType::dedicated:
				for (int i = 0; i < Constants::PALETTE_SIZE; i++)
				{
					is >> ox->colorPalette[i].r;
					is >> ox->colorPalette[i].g;
					is >> ox->colorPalette[i].b;
				}
				break;
			}
			std::vector<uint8_t> compressedPixels;
			compressedPixels.resize(size - offsetToPixels);
			for (int i = 0; i < compressedPixels.size(); i++)
			{
				is >> compressedPixels[i];
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
	return ox;
}

bool OxFileIO::saveOx(std::string fileName, Ox *ox)
{
	std::ofstream os(fileName);
	if(!os.is_open())
	{
		return false;
	}
	try
	{
	Compressor:Compressor::CompressedData compressedData = Compressor::compress(ox->pixels);
		std::vector<uint8_t> compressedPixels = compressedData.pixels;
		uint8_t compressionType = compressedData.compressionType;
		Header header(ox, compressedPixels.size(), compressionType);
		os << header.fileHeader.signature;
		os << header.fileHeader.size;
		os << header.fileHeader.offsetToPixels;
		os << header.pictureHeader.width;
		os << header.pictureHeader.height;
		os << header.pictureHeader.paletteType;
		os << header.pictureHeader.compressionType;
		switch (ox->paletteType) {
		case Constants::paletteType::dedicated:
			for (int i = 0; i < ox->colorPalette.size(); i++)
			{
				os << ox->colorPalette[i].r;
				os << ox->colorPalette[i].g;
				os << ox->colorPalette[i].b;
			}
			break;
		}
		for(int i = 0; i < compressedPixels.size(); i++)
		{
			os << compressedPixels[i];
		}
		
	} catch (std::exception& e)
	{
		return false;
	}
	return true;
}
