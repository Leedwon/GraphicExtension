#pragma once
#include "Button.h"
#include "Image.h"

class ImageInfosMenu
{
public:
	Button backButton;
	Image img;
	ImageInfosMenu(Image img);
	void draw(SDL_Renderer *renderer, TTF_Font *font);
	bool isBackButtonPressed(SDL_Event *event);
	~ImageInfosMenu();
};

