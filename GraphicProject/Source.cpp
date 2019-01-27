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
#include "OxFileIO.h"
#include "Decompressor.h"

int main(int argc, char* args[]) {
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SurfaceHandler* screenHandler;
	SDL_Event event; // Declare event handle
	char* dropped_filedir = nullptr; // Pointer for directory of dropped file
	Image* image = nullptr;
	Ox *loadedOx = nullptr;
	Constants::fileExtension extension;
	Constants::paletteType palette;
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
	MainMenu mainMenu;
	PaletteMenu paletteMenu;
	ImageInfosMenu *imageInfosMenu = nullptr;
	SDL_Rect textPlace{ Constants::WIDTH / 2 - 240, 0, 480, 120 };
	renderText(renderer, "Please drag and drop file that you want to work on", font, &textPlace, Constants::TEXT_COLOR);
	textPlace.y += Constants::BUTTON_HEIGHT;
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
				extension = checkForFileExtension(dropped_filedir);
				if (extension == Constants::fileExtension::bmp) {
					image = new Image(dropped_filedir);
					imageInfosMenu = new ImageInfosMenu(image);
					SDL_RenderClear(renderer);
					mainMenu.draw(renderer, font);
					mainMenu.enableAllButtons();
					// when file loaded navigate to main menu
					menuState = Constants::mainMenu;
				} else if(extension == Constants::fileExtension::ox) {
					loadedOx = OxFileIO::readOx(dropped_filedir);
				} else {
					SDL_RenderClear(renderer);
					SDL_Rect textPlace{ Constants::WIDTH / 2 - 240, 0, 480, 120 };
					renderText(renderer, Constants::WRONG_FILE_EXTENSION, font, &textPlace, Constants::TEXT_COLOR);
				}
				SDL_free(dropped_filedir); // Free dropped_filedir memory
				
				break;
			case (SDL_MOUSEBUTTONDOWN):
				switch (menuState) {
				case(Constants::mainMenu):
					if (mainMenu.checkForPresses(&event)) {
						menuState = mainMenu.getMenuState();
						SDL_SetRenderDrawColor(renderer, Constants::APP_BACKGROUND.r, Constants::APP_BACKGROUND.g, Constants::APP_BACKGROUND.b, Constants::APP_BACKGROUND.a);
						SDL_RenderClear(renderer);
						 if (menuState == Constants::fileInfosMenu) {
							// navigation to fileInfosMenu
							imageInfosMenu->draw(renderer, font);
							imageInfosMenu->enableAllButtons();
						} else if (menuState == Constants::compressAndSave) {
							// choose palette and dithering then save
							paletteMenu.draw(renderer, font);
							paletteMenu.enableAllButtons();
							menuState = Constants::paletteMenu;
						}
						mainMenu.disableMenu();
					}
					break;
				case(Constants::paletteMenu):
					if (paletteMenu.checkForPresses(&event)) {
						Ox *ox = new Ox(Converter::convertImageToOxRawColors(image));
						// when any pressed get palette and navigation to main menu
						palette = paletteMenu.getPressedPalette();
						ox->paletteType = palette;
						switch (palette) {
						case Constants::dedicated:
							ox->setDedicatedPalette(image);
							break;
						case Constants::grey:
							ox->pixels = Converter::createGreyScalePixels(image);
							break;
						case Constants::bwDith:
							ox->pixels = ditheringGreyScale(Converter::createGreyScalePixels(image));
							break;
						}
						std::string filePath = getFilenameWithoutExtension(image->getFilePath());
						filePath += ".ox";
						OxFileIO::saveOx(filePath, ox);
						SDL_SetRenderDrawColor(renderer, Constants::APP_BACKGROUND.r, Constants::APP_BACKGROUND.g, Constants::APP_BACKGROUND.b, Constants::APP_BACKGROUND.a);
						SDL_RenderClear(renderer);
						mainMenu.draw(renderer, font);
						mainMenu.enableAllButtons();
						paletteMenu.disableMenu();
						menuState = Constants::mainMenu;

					}
					break;
				case(Constants::fileInfosMenu):
					if (imageInfosMenu->isBackButtonPressed(&event)) {
						SDL_SetRenderDrawColor(renderer, Constants::APP_BACKGROUND.r, Constants::APP_BACKGROUND.g, Constants::APP_BACKGROUND.b, Constants::APP_BACKGROUND.a);
						SDL_RenderClear(renderer);
						imageInfosMenu->disableMenu();
						mainMenu.enableAllButtons();
						mainMenu.draw(renderer, font);
						menuState = Constants::mainMenu;
					} else if(imageInfosMenu->isAnyImageButtonPressed(&event)) {
						menuState = Constants::showingImage;
						Ox *ox = new Ox(Converter::convertImageToOxRawColors(image));
						Constants::imageDrawType drawType = imageInfosMenu->getImageDrawType();
						switch(drawType) {
						case Constants::original:
							try {
								screenHandler->drawImage(image, 0, 0);
								SDL_UpdateWindowSurface(window);
								break;
							} catch (SurfaceHandler::SurfaceHandlerExceptions ex) {
								tooSmallSurfaceExceptionHandle(renderer, font);
							}
						case Constants::rawColors:
							try {
								screenHandler->drawOx(ox, 0, 0);
								SDL_UpdateWindowSurface(window);
								break;
							}
							catch (SurfaceHandler::SurfaceHandlerExceptions ex) {
								tooSmallSurfaceExceptionHandle(renderer, font);
							}
						case Constants::dedicatedPalette:
							try {
								ox->setDedicatedPalette(image);
								screenHandler->drawOxFromPalette(ox, 0, 0);
								SDL_UpdateWindowSurface(window);
								break;
							} catch (SurfaceHandler::SurfaceHandlerExceptions ex) {
								tooSmallSurfaceExceptionHandle(renderer, font);
							}
						case Constants::greyScale:
							try {
								screenHandler->drawPixels(Converter::createGreyScalePixels(image), 0, 0);
								SDL_UpdateWindowSurface(window);
								break;
							}
							catch (SurfaceHandler::SurfaceHandlerExceptions ex) {
								tooSmallSurfaceExceptionHandle(renderer, font);
							}
						case Constants::bwDithering:
							try {
								screenHandler->drawPixels(ditheringGreyScale(Converter::createGreyScalePixels(image)), 0, 0);
								SDL_UpdateWindowSurface(window);
								break;
							} catch (SurfaceHandler::SurfaceHandlerExceptions ex) {
								tooSmallSurfaceExceptionHandle(renderer, font); 
							}
						case Constants::dedicatedDithering:
							try {
								ox->setDedicatedPalette(image);
								ox->paletteIndexes = ditheringColor(image->getPixelMap(), *ox);
								screenHandler->drawOxFromPalette(ox, 0, 0);
								SDL_UpdateWindowSurface(window);
								break;
							} catch (SurfaceHandler::SurfaceHandlerExceptions ex) {
								tooSmallSurfaceExceptionHandle(renderer, font);
							}
						}
						SDL_SetRenderDrawColor(renderer, Constants::APP_BACKGROUND.r, Constants::APP_BACKGROUND.g, Constants::APP_BACKGROUND.b, Constants::APP_BACKGROUND.a);
						SDL_RenderClear(renderer);
						imageInfosMenu->disableMenu();
					}
					break;
				}
			case (SDL_KEYDOWN):
				if(menuState == Constants::showingImage || menuState == Constants::paletteMenu) {
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						SDL_SetRenderDrawColor(renderer, Constants::APP_BACKGROUND.r, Constants::APP_BACKGROUND.g, Constants::APP_BACKGROUND.b, Constants::APP_BACKGROUND.a);
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
