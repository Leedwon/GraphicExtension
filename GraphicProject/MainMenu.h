#pragma once
#include "Button.h"
#include "Constants.h"
class MainMenu {
public:
	Button buttonPaletteMenu;
	void draw(SDL_Renderer *rendere, TTF_Font *font);
	void disableMenu();
	MainMenu();
	~MainMenu();
};

