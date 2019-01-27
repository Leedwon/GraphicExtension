#include "Constants.h"

const std::string Constants::APP_NAME = "Graphic Project";
const std::string Constants::BUTTON_PALETTE_MENU = "choose palette";
const std::string Constants::BUTTON_PALETTE_NONE = "no palette - raw colors";
const std::string Constants::BUTTON_PALETTE_GREY = "grey colors";
const std::string Constants::BUTTON_PALETTE_IMPOSED = "imposed palette";
const std::string Constants::BUTTON_PALETTE_DEDICATED = "dedicated palette";
const std::string Constants::BUTTON_PALETTE_BW_DITHERING = "black white dithering";
const std::string Constants::BUTTON_PALETTE_DEDICATED_DITHERING = "dedicated palette dithering";
const std::string Constants::BUTTON_FILE_INFOS = "file informations";
const std::string Constants::BUTTON_SHOW_IMAGES = "show images";
const std::string Constants::BUTTON_COMPRESS_SAVE = "compress & save";
const std::string Constants::BUTTON_BACK = "back";
const std::string Constants::BUTTON_IMAGE_ORIGINAL = "show original image";
const std::string Constants::BUTTON_IMAGE_RAW = "show in raw colors ";
const std::string Constants::BUTTON_IMAGE_DEDICATED = "show with dedicated palette (256 shades)";
const std::string Constants::BUTTON_IMAGE_GREY = "show in grey (256 shades)";
const std::string Constants::BUTTON_IMAGE_BW_DITHERING = "show with black white dithering";
const std::string Constants::BUTTON_IMAGE_DEDICATED_DITHERING = "show with dedicated palette + dithering";
const std::string Constants::EXCEPTION_TOO_SMALL_SURFACE = "too small surface, press esc to back to main menu";
const SDL_Color Constants::BUTTON_BACKGROUND = { 102, 0, 102, 1};
const SDL_Color Constants::BUTTON_FRAME = { 0, 255, 0, 1};
const SDL_Color Constants::TEXT_COLOR = {255 ,255, 255, 1};
const SDL_Color Constants::APP_BACKGROUND = {0, 0, 0, 1};

Constants::Constants() {
}


Constants::~Constants() {
}
