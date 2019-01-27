#pragma once
#include "Button.h"
#include "Constants.h"

class OxMenu {
public:
	Button buttonShowOx;
	Button buttonConvertToBmpAndSave;
	OxMenu() : buttonShowOx(Constants::WIDTH / 2 - Constants::BUTTON_WIDTH / 2, 0, Constants::BUTTON_WIDTH,
	                        Constants::BUTTON_HEIGHT, Constants::BUTTON_CONVERT_TO_BMP_AND_SAVE),
	                 buttonConvertToBmpAndSave(Constants::WIDTH / 2 - Constants::BUTTON_WIDTH / 2, Constants::BUTTON_HEIGHT,
	                                     Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
	                                     Constants::BUTTON_CONVERT_TO_BMP_AND_SAVE) {
	}

	void disableMenu();
	void enableAllButtons();
	void disableAllButtons();
	void setAllButtonsFalse();
	bool checkForPresses(SDL_Event *event);
	bool isAnyButtonPressed();
	void draw(SDL_Renderer* renderer, TTF_Font* font);
	Constants::menuState getMenuState();
	~OxMenu();
};
