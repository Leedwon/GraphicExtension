#include "PaletteMenu.h"


void PaletteMenu::disableAllButtons() {
	buttonNonePalette.enabled = false;
	buttonDedicatedPalette.enabled = false;
	buttonGreyPalette.enabled = false;
	buttonImposedPalette.enabled = false;
}

void PaletteMenu::enableAllButtons() {
	buttonNonePalette.enabled = true;
	buttonDedicatedPalette.enabled = true;
	buttonGreyPalette.enabled = true;
	buttonImposedPalette.enabled = true;
}

bool PaletteMenu::checkForPresses(SDL_Event* event) {
	buttonNonePalette.pressed = buttonNonePalette.checkForPress(event);
	buttonDedicatedPalette.pressed = buttonDedicatedPalette.checkForPress(event);
	buttonGreyPalette.pressed = buttonGreyPalette.checkForPress(event);
	buttonImposedPalette.pressed = buttonImposedPalette.checkForPress(event);
	return isAnyButtonPressed();
}

bool PaletteMenu::isAnyButtonPressed() {
	if (buttonNonePalette.pressed || buttonDedicatedPalette.pressed || buttonGreyPalette.pressed || buttonImposedPalette.pressed)
		return true;
	return false;
}

void PaletteMenu::draw(SDL_Renderer* renderer, TTF_Font* font) {
	buttonNonePalette.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonDedicatedPalette.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonGreyPalette.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonImposedPalette.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	enableAllButtons();
}

Constants::paletteType PaletteMenu::getPressedPalette() {
	Constants::paletteType paletteType;
	if(buttonNonePalette.pressed) {
		paletteType = Constants::none;
	} else if(buttonDedicatedPalette.pressed) {
		paletteType = Constants::dedicated;
	} else if (buttonGreyPalette.pressed) {
		paletteType = Constants::grey;
	} else if(buttonImposedPalette.pressed) {
		paletteType = Constants::imposed;
	}
	return paletteType;
}

void PaletteMenu::setAllButtonsToFalseState() {
	buttonNonePalette.pressed = false;
	buttonDedicatedPalette.pressed = false;
	buttonGreyPalette.pressed = false;
	buttonImposedPalette.pressed = false;
}

void PaletteMenu::disableMenu() {
	disableAllButtons();
	setAllButtonsToFalseState();
}

PaletteMenu::PaletteMenu() :
	buttonNonePalette(0, 0, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT, Constants::BUTTON_PALETTE_NONE),
	buttonDedicatedPalette(0, Constants::BUTTON_HEIGHT+ Constants::PADDING, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
	                       Constants::BUTTON_PALETTE_DEDICATED),
	buttonGreyPalette(0, Constants::BUTTON_HEIGHT * 2 + Constants::PADDING * 2, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
	                  Constants::BUTTON_PALETTE_GREY),
	buttonImposedPalette(0, Constants::BUTTON_HEIGHT * 3 + Constants::PADDING * 3, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
	                     Constants::BUTTON_PALETTE_IMPOSED) {

}


PaletteMenu::~PaletteMenu() {
}
