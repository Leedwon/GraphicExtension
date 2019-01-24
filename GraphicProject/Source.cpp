#include <SDL.h>
#include <string>
#include "Image.h"
#include <iostream>
#include "SurfaceHandler.h"
#include "Compressor.h"
#include "Ox.h"
#include "Converter.h"
#include "Button.h"
#include "Utilities.h"
#include "MainMenu.h"
#include "PaletteMenu.h"

int main(int argc, char* args[]) {
	int height = 960;
	int width = 1080;
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SurfaceHandler* screenHandler;
	SDL_Event event; // Declare event handle
	char* dropped_filedir = nullptr; // Pointer for directory of dropped file
	Image* image;
	Constants::paletteType palette;
	Constants::menuState menuState = Constants::mainMenu;
	bool fileDropped = false;
	SDL_Init(SDL_INIT_VIDEO); // SDL2 initialization
	TTF_Init();
	window = SDL_CreateWindow( // Create a window
		Constants::APP_NAME.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
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
	mainMenu.draw(renderer, font);

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
				// TODO:: do some things with iamge
				SDL_free(dropped_filedir); // Free dropped_filedir memory
				fileDropped = true;
				break;
			case (SDL_MOUSEBUTTONDOWN):
				switch (menuState) {
				case(Constants::mainMenu):
					if (mainMenu.buttonPaletteMenu.checkForPress(&event)) {
						//when pressed
						SDL_RenderClear(renderer);
						paletteMenu.draw(renderer, font);
						paletteMenu.enableAllButtons();
						mainMenu.disableMenu();
						menuState = Constants::paletteMenu;
					}

					break;
				case(Constants::paletteMenu):
					if (paletteMenu.checkForPresses(&event)) {
						// when any pressed 
						palette = paletteMenu.getPressedPalette();
						SDL_RenderClear(renderer);
						mainMenu.draw(renderer, font);
						mainMenu.buttonPaletteMenu.enabled = true;
						paletteMenu.disableMenu();
						menuState = Constants::mainMenu;
					}
					break;
				}
			}
		}
	}
	SDL_Delay(0);
	SDL_DestroyWindow(window); // Close and destroy the window

	SDL_Quit(); // Clean up
	return 0;
}
