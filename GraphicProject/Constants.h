#pragma once
#include <cstdint>
#include <string>
#include <SDL.h>

class Constants {
private:
	Constants();
public:
	typedef uint8_t oxPixel; 
	enum paletteType { none, dedicated, grey, imposed };
	enum menuState {dropFileState, mainMenu, paletteMenu, fileInfosMenu, showImagesMenu};

    /*dimension consts*/
	static const int PADDING = 24;
	static const int BUTTON_WIDTH = 480;
	static const int BUTTON_HEIGHT = 120;
	static const int WIDTH = 1080;
	static const int HEIGHT = 960;

	/*compression type*/
	static const int COMPRESSION_RLE = 0;
	static const int COMPRESSION_BYTE_RUN = 1;

	/*colors for buttons*/
	static const SDL_Color BUTTON_BACKGROUND;
	static const SDL_Color BUTTON_FRAME;
	static const SDL_Color TEXT_COLOR;

	/*strings for buttons names*/
	static const std::string BUTTON_PALETTE_MENU;
	static const std::string BUTTON_PALETTE_NONE;
	static const std::string BUTTON_PALETTE_IMPOSED;
	static const std::string BUTTON_PALETTE_DEDICATED;
	static const std::string BUTTON_PALETTE_GREY;
	static const std::string BUTTON_FILE_INFOS;
	static const std::string BUTTON_SHOW_IMAGES;
	static const std::string BUTTON_BACK;
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

