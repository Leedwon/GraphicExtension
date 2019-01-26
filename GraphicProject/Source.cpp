#include <SDL.h>
#include <string>
#include "Image.h"
#include "SurfaceHandler.h"
#include "Compressor.h"
#include "Ox.h"
#include "Converter.h"
#include "Button.h"
#include "Utilities.h"
#include "MainMenu.h"
#include "PaletteMenu.h"
#include "ImageInfosMenu.h"
#include <allocators>

int main(int argc, char* args[]) {
	SDL_Window* window;
	SDL_Surface* bmpSurface = nullptr;
	SDL_Surface* screenSurface;
	SurfaceHandler* screenHandler;
	SDL_Texture *tx = nullptr;
	SDL_Event event; // Declare event handle
	char* dropped_filedir = nullptr; // Pointer for directory of dropped file
	Image* image = nullptr;
	Constants::paletteType palette;
	Ox *ox = nullptr;
	Constants::menuState menuState = Constants::dropFileState;
	bool fileDropped = false;
	SDL_Init(SDL_INIT_VIDEO); // SDL2 initialization
	TTF_Init();
	window = SDL_CreateWindow( // Create a window
		Constants::APP_NAME.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		Constants::WIDTH,
		Constants::HEIGHT,
		SDL_WINDOW_OPENGL
	);

	// Check that the window was successfully made
	if (window == NULL) {
		// In the event that the window could not be made...
		SDL_Log("Could not create window: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	TTF_Font* font = TTF_OpenFont("font/OpenSans-Regular.ttf", 128);
	if (!font) {
		printf("TTF_OpenFont: %s\n", TTF_GetError());
		// handle error
	}

	screenSurface = SDL_GetWindowSurface(window);
	screenHandler = new SurfaceHandler(screenSurface);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 255, 255, 255));
	SDL_UpdateWindowSurface(window);
	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
	SDL_bool done = SDL_FALSE;
	SDL_bool test = SDL_FALSE;
	MainMenu mainMenu;
	PaletteMenu paletteMenu;
	ImageInfosMenu *imageInfosMenu = nullptr;
	SDL_Rect textPlace{ Constants::WIDTH / 2 - 240, 0, 480, 120 };
	renderText(renderer, "Please drag and drop file that you want to work on", font, &textPlace, Constants::TEXT_COLOR);
	textPlace.y += Constants::BUTTON_WIDTH;
	renderText(renderer, "Loading file can take a while, sorry", font, &textPlace, Constants::TEXT_COLOR);

	while (!done) {
		// Program loop
		while (!done && SDL_PollEvent(&event)) {
			switch (event.type) {
			case (SDL_QUIT):
				// In case of exit
				done = SDL_TRUE;
				break;

			case (SDL_DROPFILE):
				dropped_filedir = event.drop.file;
				image = new Image(dropped_filedir);
				ox = new Ox(Converter::convertImageToOx(image));
				ox->setDedicatedPalette(image);
				bmpSurface = SDL_LoadBMP(dropped_filedir);
				tx = SDL_CreateTextureFromSurface(renderer, bmpSurface);
				SDL_FreeSurface(bmpSurface);
				imageInfosMenu = new ImageInfosMenu(*image);
				// TODO:: do some things with iamge
				SDL_free(dropped_filedir); // Free dropped_filedir memory
				fileDropped = true;
				SDL_RenderClear(renderer);
				mainMenu.draw(renderer, font);
				mainMenu.enableAllButtons();
				// when file loaded navigate to main menu
				menuState = Constants::mainMenu;
				break;
			case (SDL_MOUSEBUTTONDOWN):
				switch (menuState) {
				case(Constants::mainMenu):
					if (mainMenu.checkForPresses(&event)) {
						menuState = mainMenu.getMenuState();
						//when pressed
						SDL_RenderClear(renderer);
						if (menuState == Constants::paletteMenu) {
							// navigation to paletteMenu
							paletteMenu.draw(renderer, font);
							paletteMenu.enableAllButtons();
						} else if (menuState == Constants::fileInfosMenu) {
							// navigation to fileInfosMenu
							SDL_Rect bmpRect = { Constants::WIDTH / 2 , Constants::HEIGHT / 2, image->getWidth(), image->getHeight() };
							SDL_RenderCopy(renderer, tx, NULL, &bmpRect);
							SDL_RenderPresent(renderer);
							imageInfosMenu->draw(renderer, font);
							imageInfosMenu->backButton.enabled = true;

						} else if (menuState == Constants::showImagesMenu) {
							SDL_RenderClear(renderer);
							mainMenu.disableMenu();
							screenHandler->drawImage(image, 0, 0);
							screenHandler->drawOxFromPalette(ox, ox->width, 0);
							screenHandler->drawOx(ox, ox->width, ox->height);
							screenHandler->drawPixels(Converter::getBlackWhitePixels(image), 0, ox->height);
							screenHandler->drawPixels(ditheringGreyScale(Converter::getBlackWhitePixels(image)), 0, ox->height * 2);
							SDL_UpdateWindowSurface(window);
						}
						mainMenu.disableMenu();

					}
					break;
				case(Constants::paletteMenu):
					if (paletteMenu.checkForPresses(&event)) {
						// when any pressed get palette and navigation to main menu
						palette = paletteMenu.getPressedPalette();
						SDL_RenderClear(renderer);
						mainMenu.draw(renderer, font);
						mainMenu.enableAllButtons();
						paletteMenu.disableMenu();
						menuState = Constants::mainMenu;
					}
					break;
				case(Constants::fileInfosMenu):
					if (imageInfosMenu->backButton.checkForPress(&event)) {
						SDL_RenderClear(renderer);
						// navigation to main menu
						imageInfosMenu->backButton.enabled = false;
						mainMenu.enableAllButtons();
						mainMenu.draw(renderer, font);
						menuState = Constants::mainMenu;
					}
					break;
				}
			case (SDL_KEYDOWN):
				if(menuState == Constants::showImagesMenu) {
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						SDL_RenderClear(renderer);
						mainMenu.enableAllButtons();
						mainMenu.draw(renderer, font);
						menuState = Constants::mainMenu;
					}
				}
				break;
			}
		}
	}
	SDL_Delay(0);
	SDL_DestroyWindow(window); // Close and destroy the window

	SDL_Quit(); // Clean up
	return 0;
}
