#pragma once
#include "Button.h"
#include "Image.h"
#include "Constants.h"

class ImageInfosMenu
{
private:
	bool isImgBtnPressed();
public:
	Button buttonBack;
	Button buttonOriginalImage;
	Button buttonRawColors;
	Button buttonDedicatedPalette;
	Button buttonGreyScale;
	Button buttonBwDithering;
	Image *img;
	void enableAllButtons();
	void disableAllButtons();
	void setAllButtonsToFalse();
	void disableMenu();
	ImageInfosMenu(Image *img);
	void draw(SDL_Renderer *renderer, TTF_Font *font);
	bool isBackButtonPressed(SDL_Event *event);
	bool isAnyImageButtonPressed(SDL_Event *event);
	Constants::imageDrawType getImageDrawType();

	~ImageInfosMenu();
};

