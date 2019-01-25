#include "MainMenu.h"
#include "Utilities.h"


void MainMenu::disableAllButtons() {
	buttonPaletteMenu.enabled = false;
	buttonFileInfos.enabled = false;
	buttonShowImages.enabled = false;
}

void MainMenu::enableAllButtons() {
	buttonPaletteMenu.enabled = true;
	buttonFileInfos.enabled = true;
	buttonShowImages.enabled = true;
}

void MainMenu::setAllButtonsToFalseState() {
	buttonPaletteMenu.pressed = false;
	buttonFileInfos.pressed = false;
	buttonShowImages.pressed = false;
}

bool MainMenu::checkForPresses(SDL_Event* event) {
	buttonPaletteMenu.pressed = buttonPaletteMenu.checkForPress(event);
	buttonFileInfos.pressed = buttonFileInfos.checkForPress(event);
	buttonShowImages.pressed = buttonShowImages.checkForPress(event);
	return isAnyButtonPressed();
}


bool MainMenu::isAnyButtonPressed() {
	return (buttonPaletteMenu.pressed || buttonFileInfos.pressed || buttonShowImages.pressed);
}

Constants::menuState MainMenu::getMenuState() {
	Constants::menuState state;
	if (buttonPaletteMenu.pressed)
		state = Constants::paletteMenu;
	else if (buttonFileInfos.pressed)
		state = Constants::fileInfosMenu;
	else if (buttonShowImages.pressed)
		state = Constants::showImagesMenu;
	return state;
}

void MainMenu::draw(SDL_Renderer* renderer, TTF_Font* font) {
	buttonPaletteMenu.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonFileInfos.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
	buttonShowImages.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
}

void MainMenu::disableMenu() {
	disableAllButtons();
	setAllButtonsToFalseState();
}

MainMenu::MainMenu() : buttonPaletteMenu(Constants::WIDTH / 2 - Constants::BUTTON_WIDTH / 2, 0, Constants::BUTTON_WIDTH,
                                         Constants::BUTTON_HEIGHT, Constants::BUTTON_PALETTE_MENU),
                       buttonFileInfos(Constants::WIDTH / 2 - Constants::BUTTON_WIDTH / 2, Constants::BUTTON_HEIGHT,
                                       Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
                                       Constants::BUTTON_FILE_INFOS),
                       buttonShowImages(Constants::WIDTH / 2 - Constants::BUTTON_WIDTH / 2,
                                        Constants::BUTTON_HEIGHT * 2, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
                                        Constants::BUTTON_SHOW_IMAGES) {
}


MainMenu::~MainMenu() {
}


