#include "ImageInfosMenu.h"
#include "Constants.h"
#include "Utilities.h"
#include <allocators>


void ImageInfosMenu::enableAllButtons() {
	buttonBack.enabled = true;
	buttonOriginalImage.enabled = true;
	buttonRawColors.enabled = true;
	buttonDedicatedPalette.enabled = true;
	buttonGreyScale.enabled = true;
	buttonBwDithering.enabled = true;
	buttonDedicatedDithering.enabled = true;
}

void ImageInfosMenu::disableAllButtons() {
	buttonBack.enabled = false;
	buttonOriginalImage.enabled = false;
	buttonRawColors.enabled = false;
	buttonDedicatedPalette.enabled = false;
	buttonGreyScale.enabled = false;
	buttonBwDithering.enabled = false;
	buttonDedicatedDithering.enabled = false;
}

void ImageInfosMenu::setAllButtonsToFalse() {
	buttonBack.pressed = false;
	buttonOriginalImage.pressed = false;
	buttonRawColors.pressed = false;
	buttonDedicatedPalette.pressed= false;
	buttonGreyScale.pressed = false;
	buttonBwDithering.pressed = false;
	buttonDedicatedDithering.pressed = false;
}

void ImageInfosMenu::disableMenu() {
	setAllButtonsToFalse();
	disableAllButtons();
}

ImageInfosMenu::ImageInfosMenu(Image* img) :
	buttonBack(0, 0, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT, Constants::BUTTON_BACK),
	buttonOriginalImage(Constants::WIDTH - Constants::BUTTON_WIDTH, 0, Constants::BUTTON_WIDTH,
	                    Constants::BUTTON_HEIGHT, Constants::BUTTON_IMAGE_ORIGINAL),
	buttonDedicatedPalette(Constants::WIDTH - Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
		Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT, Constants::BUTTON_IMAGE_DEDICATED),
	buttonRawColors(Constants::WIDTH - Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT * 2, Constants::BUTTON_WIDTH,
	                Constants::BUTTON_HEIGHT, Constants::BUTTON_IMAGE_RAW),
	buttonGreyScale(Constants::WIDTH - Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT * 3, Constants::BUTTON_WIDTH,
	                Constants::BUTTON_HEIGHT, Constants::BUTTON_IMAGE_GREY),
	buttonBwDithering(Constants::WIDTH - Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT * 4, Constants::BUTTON_WIDTH,
	                  Constants::BUTTON_HEIGHT, Constants::BUTTON_IMAGE_BW_DITHERING),
	buttonDedicatedDithering(Constants::WIDTH - Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT * 5, Constants::BUTTON_WIDTH,
		Constants::BUTTON_HEIGHT, Constants::BUTTON_IMAGE_DEDICATED_DITHERING), img(img) {
}

void ImageInfosMenu::draw(SDL_Renderer* renderer, TTF_Font* font) {
	std::string width = "width = " + std::to_string(img->getWidth());
	std::string height = "height = " + std::to_string(img->getHeight());
	std::string filePath = "filePath = " + img->getFilePath();
	SDL_Rect background{0, Constants::BUTTON_HEIGHT, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT};
	renderText(renderer, width, font, &background, Constants::TEXT_COLOR);
	background.y += Constants::BUTTON_HEIGHT;
	renderText(renderer, height, font, &background, Constants::TEXT_COLOR);
	background.y = Constants::HEIGHT - Constants::BUTTON_HEIGHT;
	background.w += Constants::BUTTON_WIDTH;
	renderText(renderer, filePath, font, &background, Constants::TEXT_COLOR);
	buttonBack.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonOriginalImage.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonDedicatedPalette.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonRawColors.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonGreyScale.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonBwDithering.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonDedicatedDithering.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
}


bool ImageInfosMenu::isBackButtonPressed(SDL_Event* event) {
	return buttonBack.checkForPress(event);
}

bool ImageInfosMenu::isAnyImageButtonPressed(SDL_Event* event) {
	buttonBwDithering.pressed = buttonBwDithering.checkForPress(event);
	buttonRawColors.pressed = buttonRawColors.checkForPress(event);
	buttonOriginalImage.pressed = buttonOriginalImage.checkForPress(event);
	buttonDedicatedPalette.pressed = buttonDedicatedPalette.checkForPress(event);
	buttonGreyScale.pressed = buttonGreyScale.checkForPress(event);
	buttonDedicatedDithering.pressed = buttonDedicatedDithering.checkForPress(event);
	return isImgBtnPressed();
}

bool ImageInfosMenu::isImgBtnPressed() {
	return (buttonRawColors.pressed || buttonOriginalImage.pressed || buttonGreyScale.pressed || buttonDedicatedPalette.pressed || buttonBwDithering.pressed || buttonDedicatedDithering.pressed);
}

Constants::imageDrawType ImageInfosMenu::getImageDrawType() {
	// initialized here just to get rid of compilator error normally exception should be thrown
	Constants::imageDrawType result = Constants::original;
	if (buttonOriginalImage.pressed)
		result = Constants::original;
	else if (buttonDedicatedPalette.pressed)
		result = Constants::dedicatedPalette;
	else if (buttonRawColors.pressed)
		result = Constants::rawColors;
	else if (buttonGreyScale.pressed)
		result = Constants::greyScale;
	else if (buttonBwDithering.pressed)
		result = Constants::bwDithering;
	else if (buttonDedicatedDithering.pressed)
		result = Constants::dedicatedDithering;
	return result;
}

ImageInfosMenu::~ImageInfosMenu() {
}
