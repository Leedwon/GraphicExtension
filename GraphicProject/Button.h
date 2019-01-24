#pragma once
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>

class Button {
public:
	int x;
	int y;
	int width;
	int height;
	bool enabled;
	bool pressed;
	std::string text;
	bool checkForPress(const SDL_Event *ev);
	SDL_Rect createSdlRect() { return SDL_Rect{ x, y, width, height }; }
	void draw(SDL_Renderer *renderer, SDL_Color frame, SDL_Color fill, TTF_Font *font);
	Button(int x, int y, int width, int height, std::string text) : x(x), y(y), width(width), height(height), text(text), pressed(false), enabled(true) {}
	~Button();

};

