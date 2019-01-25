#include "Button.h"


bool Button::checkForPress(const SDL_Event* ev) {
	if (enabled) {
		if (ev->type == SDL_MOUSEBUTTONDOWN) {
			if (ev->button.button == SDL_BUTTON_LEFT &&
				ev->button.x >= x &&
				ev->button.x <= (x + width) &&
				ev->button.y >= y &&
				ev->button.y <= y + height) {
				return true;
			}
		}
	}
	return false;
}

void Button::draw(SDL_Renderer* renderer, SDL_Color frame, SDL_Color fill, TTF_Font* font) {
	SDL_Rect* button = &createSdlRect();
	SDL_SetRenderDrawColor(renderer, fill.r, fill.g, fill.b, fill.a);
	SDL_RenderFillRect(renderer, button);
	SDL_SetRenderDrawColor(renderer, frame.r, frame.g, frame.b, frame.a);
	SDL_RenderDrawRect(renderer, button);
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), SDL_Color{ 0, 0, 0, 1 });
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, textTexture, NULL, button);
	SDL_RenderPresent(renderer);
}

Button::~Button() {
}
