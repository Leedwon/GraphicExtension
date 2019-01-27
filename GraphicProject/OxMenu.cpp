#include "OxMenu.h"


void OxMenu::disableMenu() {
	disableAllButtons();
	setAllButtonsFalse();
}

void OxMenu::enableAllButtons() {
	buttonConvertToBmpAndSave.enabled = true;
	buttonShowOx.enabled = true;
}

void OxMenu::disableAllButtons() {
	buttonConvertToBmpAndSave.enabled = false;
	buttonShowOx.enabled = false;
}

void OxMenu::setAllButtonsFalse() {
	buttonConvertToBmpAndSave.pressed = false;
	buttonShowOx.pressed = false;
}

bool OxMenu::checkForPresses(SDL_Event *event) {
	buttonConvertToBmpAndSave.pressed = buttonConvertToBmpAndSave.checkForPress(event);
	buttonShowOx.pressed = buttonShowOx.checkForPress(event);
	return isAnyButtonPressed();
}

bool OxMenu::isAnyButtonPressed() {
	return (buttonConvertToBmpAndSave.pressed || buttonShowOx.pressed);
}

void OxMenu::draw(SDL_Renderer* renderer, TTF_Font* font) {
	buttonConvertToBmpAndSave.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonShowOx.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
}

Constants::menuState OxMenu::getMenuState() {
	Constants::menuState result;
	if (buttonConvertToBmpAndSave.pressed)
		result = Constants::convertAndSaveOxMenu;
	else if (buttonShowOx.pressed)
		result = Constants::showingImageOxMenu;
	return result;
}

OxMenu::~OxMenu()
{
}
