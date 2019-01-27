#pragma once
#include <cstdint>
#include <string>
#include <SDL.h>

class Constants {
private:
	Constants();
public:
	typedef uint8_t oxPixel; 
	enum paletteType { none, dedicated, grey, imposed, bwDith, dedicatedDith };
	enum menuState {dropFileState, mainMenu, paletteMenu, fileInfosMenu, compressAndSave, showingImage, showingImageOxMenu, convertAndSaveOxMenu, oxMenu };
	enum fileExtension {bmp, ox, notKnown};
	enum imageDrawType {original, rawColors, dedicatedPalette, greyScale, bwDithering, dedicatedDithering, imposedPalette};
	enum compressionType {rle, byteRun};

    /*dimension consts*/
	static const int PADDING = 24;
	static const int BUTTON_WIDTH = 480;
	static const int BUTTON_HEIGHT = 120;
	static const int WIDTH = 1080;
	static const int HEIGHT = 960;

	/*compression type delete later*/
	static const int COMPRESSION_RLE = 0;
	static const int COMPRESSION_BYTE_RUN = 1;

	/*colors for buttons*/
	static const SDL_Color BUTTON_BACKGROUND;
	static const SDL_Color BUTTON_FRAME;
	static const SDL_Color TEXT_COLOR;

	static const SDL_Color APP_BACKGROUND;

	/*strings for buttons names*/
	static const std::string BUTTON_PALETTE_MENU;
	static const std::string BUTTON_PALETTE_NONE;
	static const std::string BUTTON_PALETTE_IMPOSED;
	static const std::string BUTTON_PALETTE_DEDICATED;
	static const std::string BUTTON_PALETTE_DEDICATED_DITHERING;
	static const std::string BUTTON_PALETTE_BW_DITHERING;
	static const std::string BUTTON_PALETTE_GREY;
	static const std::string BUTTON_FILE_INFOS;
	static const std::string BUTTON_SHOW_IMAGES;
	static const std::string BUTTON_COMPRESS_SAVE;
	static const std::string BUTTON_IMAGE_ORIGINAL;
	static const std::string BUTTON_IMAGE_RAW;
	static const std::string BUTTON_IMAGE_DEDICATED;
	static const std::string BUTTON_IMAGE_GREY;
	static const std::string BUTTON_IMAGE_BW_DITHERING;
	static const std::string BUTTON_IMAGE_DEDICATED_DITHERING;
	static const std::string BUTTON_CONVERT_TO_BMP_AND_SAVE;
	static const std::string BUTTON_SHOW_OX;
	static const std::string BUTTON_BACK;
	static const std::string EXCEPTION_TOO_SMALL_SURFACE;
	static const std::string WRONG_FILE_EXTENSION;
	static const std::string APP_NAME;

	static const int SIGNATURE_SIZE = 2;
	static const int PALETTE_TYPE_BYTE_SHIFT = 3;
	static const int PALETTE_SIZE = 256;
	static const int PALETTE_BITS_SHIFT = 0;
	static const int MASK_FIRST_2_BITS = 0b11000000;
	static const int MASK_FIRST_3_BITS = 0b11100000;
	static const int MASK_BITS_RED = 0b11100000;
	static const int MASK_BITS_GREEN = 0b00011100;
	static const int MASK_BITS_BLUE = 0b0000011;
	~Constants();
};

