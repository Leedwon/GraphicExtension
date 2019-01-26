#include "MainMenu.h"
#include "Utilities.h"


void MainMenu::disableAllButtons() {
	buttonFileInfos.enabled = false;
	buttonCompressAndSave.enabled = false;
}

void MainMenu::enableAllButtons() {
	buttonFileInfos.enabled = true;
	buttonCompressAndSave.enabled = true;
}

void MainMenu::setAllButtonsToFalseState() {
	buttonFileInfos.pressed = false;
	buttonCompressAndSave.pressed = false;
}

bool MainMenu::checkForPresses(SDL_Event* event) {
	buttonFileInfos.pressed = buttonFileInfos.checkForPress(event);
	buttonCompressAndSave.pressed = buttonCompressAndSave.checkForPress(event);
	return isAnyButtonPressed();
}


bool MainMenu::isAnyButtonPressed() {
	return (buttonFileInfos.pressed || buttonCompressAndSave.pressed);
}

Constants::menuState MainMenu::getMenuState() {
	Constants::menuState state;
	if (buttonFileInfos.pressed)
		state = Constants::fileInfosMenu;
	else if (buttonCompressAndSave.pressed)
		state = Constants::compressAndSave;
	return state;
}

void MainMenu::draw(SDL_Renderer* renderer, TTF_Font* font) {
	buttonFileInfos.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonCompressAndSave.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
}

void MainMenu::disableMenu() {
	disableAllButtons();
	setAllButtonsToFalseState();
}

MainMenu::MainMenu() :
	buttonFileInfos(Constants::WIDTH / 2 - Constants::BUTTON_WIDTH / 2, 0,
	                Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
	                Constants::BUTTON_FILE_INFOS),
	buttonCompressAndSave(Constants::WIDTH / 2 - Constants::BUTTON_WIDTH / 2,
	                      Constants::BUTTON_HEIGHT, Constants::BUTTON_WIDTH,
	                      Constants::BUTTON_HEIGHT, Constants::BUTTON_COMPRESS_SAVE) {
}


MainMenu::~MainMenu() {
}


