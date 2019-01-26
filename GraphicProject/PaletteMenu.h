#pragma once
#include "Button.h"
#include "Constants.h"
class PaletteMenu {
public:
	Button buttonNonePalette;
	Button buttonDedicatedPalette;
	Button buttonGreyPalette;
	Button buttonImposedPalette;
	Button buttonBwDithPalette;
	Button buttonDedicatedDithPalette;
	void disableAllButtons();
	void enableAllButtons();
	// true if any pressed false otherwise
	bool checkForPresses(SDL_Event *event);
	bool isAnyButtonPressed();
	void draw(SDL_Renderer *renderer, TTF_Font *font);
	Constants::paletteType getPressedPalette();
	void setAllButtonsToFalseState();
	void disableMenu();
	PaletteMenu();
	~PaletteMenu();
};

