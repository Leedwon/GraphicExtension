#include "Constants.h"

const std::string Constants::APP_NAME = "Graphic Project";
const std::string Constants::BUTTON_PALETTE_MENU = "Palette Menu";
const std::string Constants::BUTTON_PALETTE_NONE = "no palette - raw colors";
const std::string Constants::BUTTON_PALETTE_GREY = "grey colors";
const std::string Constants::BUTTON_PALETTE_IMPOSED = "imposed palette";
const std::string Constants::BUTTON_PALETTE_DEDICATED = "dedicated palette";
const std::string Constants::BUTTON_FILE_INFOS = "file informations";
const std::string Constants::BUTTON_SHOW_IMAGES = "show images";
const std::string Constants::BUTTON_BACK = "back";
const SDL_Color Constants::BUTTON_BACKGROUND = {0,100, 0, 1};
const SDL_Color Constants::BUTTON_FRAME = {0, 0, 0, 1};
const SDL_Color Constants::TEXT_COLOR = {255 ,255, 255, 1};

Constants::Constants() {
}


Constants::~Constants() {
}
