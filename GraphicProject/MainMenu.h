#pragma once
#include "Button.h"
#include "Constants.h"
class MainMenu {
public:
	Button buttonPaletteMenu;
	Button buttonFileInfos;
	Button buttonCompressAndSave;
	void disableAllButtons();
	void enableAllButtons();
	void setAllButtonsToFalseState();
	// true if any pressed false otherwise
	bool checkForPresses(SDL_Event *event);
	bool isAnyButtonPressed();
	Constants::menuState getMenuState();
	void draw(SDL_Renderer *rendere, TTF_Font *font);
	void disableMenu();
	
	MainMenu();
	~MainMenu();
};

