#include "PaletteMenu.h"


void PaletteMenu::disableAllButtons() {
	buttonNonePalette.enabled = false;
	buttonDedicatedPalette.enabled = false;
	buttonGreyPalette.enabled = false;
	buttonImposedPalette.enabled = false;
	buttonBwDithPalette.enabled = false;
	buttonDedicatedDithPalette.enabled = false;
}

void PaletteMenu::enableAllButtons() {
	buttonNonePalette.enabled = true;
	buttonDedicatedPalette.enabled = true;
	buttonGreyPalette.enabled = true;
	buttonImposedPalette.enabled = true;
	buttonBwDithPalette.enabled = true;
	buttonDedicatedDithPalette.enabled = true;
}

bool PaletteMenu::checkForPresses(SDL_Event* event) {
	buttonNonePalette.pressed = buttonNonePalette.checkForPress(event);
	buttonDedicatedPalette.pressed = buttonDedicatedPalette.checkForPress(event);
	buttonGreyPalette.pressed = buttonGreyPalette.checkForPress(event);
	buttonImposedPalette.pressed = buttonImposedPalette.checkForPress(event);
	buttonBwDithPalette.pressed = buttonBwDithPalette.checkForPress(event);
	buttonDedicatedDithPalette.pressed = buttonDedicatedDithPalette.checkForPress(event);
	return isAnyButtonPressed();
}

bool PaletteMenu::isAnyButtonPressed() {
	return (buttonNonePalette.pressed || buttonDedicatedPalette.pressed || buttonGreyPalette.pressed || buttonImposedPalette.pressed || buttonBwDithPalette.pressed || buttonDedicatedDithPalette.pressed);
}

void PaletteMenu::draw(SDL_Renderer* renderer, TTF_Font* font) {
	buttonNonePalette.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonDedicatedPalette.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonGreyPalette.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonImposedPalette.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonBwDithPalette.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonDedicatedDithPalette.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	enableAllButtons();
}

Constants::paletteType PaletteMenu::getPaletteType() {
	Constants::paletteType paletteType;
	if (buttonNonePalette.pressed) {
		paletteType = Constants::none;
	} else if (buttonDedicatedPalette.pressed) {
		paletteType = Constants::dedicated;
	} else if (buttonGreyPalette.pressed) {
		paletteType = Constants::grey;
	} else if (buttonImposedPalette.pressed) {
		paletteType = Constants::imposed;
	} else if (buttonBwDithPalette.pressed) {
		paletteType = Constants::bwDith;
	} else if (buttonDedicatedDithPalette.pressed) {
		paletteType = Constants::dedicatedDith;
	}
	return paletteType;
}

void PaletteMenu::setAllButtonsToFalseState() {
	buttonNonePalette.pressed = false;
	buttonDedicatedPalette.pressed = false;
	buttonGreyPalette.pressed = false;
	buttonImposedPalette.pressed = false;
	buttonBwDithPalette.pressed = false;
	buttonDedicatedDithPalette.pressed = false;
}

void PaletteMenu::disableMenu() {
	disableAllButtons();
	setAllButtonsToFalseState();
}

PaletteMenu::PaletteMenu() :
	buttonNonePalette(Constants::WIDTH/2 - Constants::BUTTON_WIDTH / 2, 0, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT, Constants::BUTTON_PALETTE_NONE),
	buttonDedicatedPalette(Constants::WIDTH / 2 - Constants::BUTTON_WIDTH / 2, Constants::BUTTON_HEIGHT, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
	                       Constants::BUTTON_PALETTE_DEDICATED),
	buttonGreyPalette(Constants::WIDTH / 2 - Constants::BUTTON_WIDTH / 2, Constants::BUTTON_HEIGHT * 2, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
	                  Constants::BUTTON_PALETTE_GREY),
	buttonImposedPalette(Constants::WIDTH / 2 - Constants::BUTTON_WIDTH / 2, Constants::BUTTON_HEIGHT * 3, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
	                     Constants::BUTTON_PALETTE_IMPOSED), 
buttonBwDithPalette(Constants::WIDTH / 2 - Constants::BUTTON_WIDTH / 2, Constants::BUTTON_HEIGHT * 4, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
							 Constants::BUTTON_PALETTE_BW_DITHERING), 
buttonDedicatedDithPalette(Constants::WIDTH / 2 - Constants::BUTTON_WIDTH / 2, Constants::BUTTON_HEIGHT * 5, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
								 Constants::BUTTON_PALETTE_DEDICATED_DITHERING) {

}


PaletteMenu::~PaletteMenu() {
}
