#include <SDL.h>
#include <string>
#include "Image.h"
#include <math.h>
#include <iostream>

int main(int argc, char *args[]) {
	std::string pictureFile = "picture1.bmp";
	Image image(pictureFile);
	SDL_Window *window = nullptr;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "Video initialization error" << std::endl;
	else
	{
		window = SDL_CreateWindow("App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
		if(window == NULL)
			std::cout << "Window creation error" << std::endl;
		else
		{
			SDL_UpdateWindowSurface(window);
			SDL_Delay(2000);
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
