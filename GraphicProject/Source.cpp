#include <SDL.h>
#include <string>
#include "Image.h"
#include <iostream>
#include "SurfaceHandler.h"


int main(int argc, char *args[]) {
	int height = 960;
	int width = 1080;
	SDL_Window *window;
	SDL_Surface *screenSurface;
	SurfaceHandler *screenHandler;
	SDL_Event event;                        // Declare event handle
	char* dropped_filedir = nullptr;                  // Pointer for directory of dropped file
	Image *image;
	SDL_Init(SDL_INIT_VIDEO);               // SDL2 initialization
	
	window = SDL_CreateWindow(  // Create a window
		"SDL_DropEvent usage, please drop the file on window",
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
	screenSurface = SDL_GetWindowSurface(window);
	screenHandler = new SurfaceHandler(screenSurface);
	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0, 0, 0));
	SDL_UpdateWindowSurface(window);
	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
	SDL_bool done = SDL_FALSE;
	while (!done) {                         // Program loop
		while (!done && SDL_PollEvent(&event)) {
			switch (event.type) {
			case (SDL_QUIT): {          // In case of exit
				done = SDL_TRUE;
				break;
			}

			case (SDL_DROPFILE): {      // In case if dropped file
				dropped_filedir = event.drop.file;
				image = new Image(dropped_filedir);
				// Shows directory of dropped file
				SDL_ShowSimpleMessageBox(
					SDL_MESSAGEBOX_INFORMATION,
					"File dropped on window",
					dropped_filedir,
					window
				);
				screenHandler->drawImage(image);
				SDL_UpdateWindowSurface(window);
				SDL_free(dropped_filedir);    // Free dropped_filedir memory
				break;
			}
			}
		}
		SDL_Delay(0);
	}
	

	SDL_DestroyWindow(window);        // Close and destroy the window

	SDL_Quit();                       // Clean up
	return 0;
}
