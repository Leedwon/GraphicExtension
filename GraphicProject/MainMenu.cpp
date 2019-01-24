#include "MainMenu.h"
#include "Utilities.h"


void MainMenu::draw(SDL_Renderer* renderer, TTF_Font *font){
	SDL_Rect textPlace{ Constants::WIDTH / 2 - 240, 0, 480, 120 };
	renderText(renderer, "Please drag and drop file that you want to work on", font, &textPlace , Constants::TEXT_COLOR);
	buttonPaletteMenu.draw(renderer, Constants::BUTTON_FRAME, Constants::BUTTON_BACKGROUND, font);
}

void MainMenu::disableMenu() {
	buttonPaletteMenu.enabled = false;
	buttonPaletteMenu.pressed = false;
}

MainMenu::MainMenu() : buttonPaletteMenu(0, 0, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT, Constants::BUTTON_PALETTE_MENU){
}


MainMenu::~MainMenu() {
}


