#include "ImageInfosMenu.h"
#include "Constants.h"
#include "Utilities.h"


ImageInfosMenu::ImageInfosMenu(Image img) : img(img), backButton(0, 0, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT, Constants::BUTTON_BACK){
}

void ImageInfosMenu::draw(SDL_Renderer *renderer, TTF_Font *font) {
	std::string width = "width = " + std::to_string(img.getWidth());
	std::string height = "height = " + std::to_string(img.getHeight());
	std::string filePath = "filePath = " + img.getFilePath();
	SDL_Rect background{ 0, Constants::BUTTON_HEIGHT, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT };
	renderText(renderer, width, font, &background, Constants::TEXT_COLOR);
	background.y += Constants::BUTTON_HEIGHT;
	renderText(renderer, height, font, &background, Constants::TEXT_COLOR);
	background.y += Constants::BUTTON_HEIGHT;
	background.x = Constants::WIDTH;
	renderText(renderer, filePath, font, &background, Constants::TEXT_COLOR);
	backButton.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
}


bool ImageInfosMenu::isBackButtonPressed(SDL_Event* event) {
	bool result = backButton.checkForPress(event);
	backButton.pressed = false;
	backButton.enabled = false;
	return result;
}

ImageInfosMenu::~ImageInfosMenu()
{
}
