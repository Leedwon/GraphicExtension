#include <SDL.h>

int main(int argc, char *args[]){
	int width = 900;
	int height = 600;
	SDL_Window *surface = nullptr;
	SDL_Init(SDL_INIT_EVERYTHING);
	surface = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	SDL_UpdateWindowSurface(surface);
	SDL_Delay(30000);
	SDL_DestroyWindow(surface);
	SDL_Quit();
	return 0;
// zmiana
}