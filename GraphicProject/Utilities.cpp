#include "Utilities.h"

SDL_Color operator+(const SDL_Color& l, const SDL_Color& r) {
	SDL_Color result;
	result.r = l.r + r.r;
	result.g = l.g + r.g;
	result.b = l.b + r.b;
	return result;
}

SDL_Color operator-(const SDL_Color& l, const SDL_Color& r) {
	SDL_Color result;
	result.r = l.r - r.r;
	result.g = l.g - r.g;
	result.b = l.b - r.b;
	return result;

}

bool operator==(const SDL_Color& l, const SDL_Color& r) {
	if (l.r == r.r) {
		if (l.g == r.g) {
			if (l.b == r.b)
				return true;
		}
	}
	return false;
}

bool operator!=(const SDL_Color& l, const SDL_Color& r) {
	if (l.r != r.r) {
		if (l.g != r.g) {
			if (l.b != r.b)
				return true;
		}
	}
	return false;
}

void renderText(SDL_Renderer *renderer, std::string text, TTF_Font *font, SDL_Rect *background, SDL_Color textColor) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	SDL_RenderCopy(renderer, textTexture, NULL, background);
	SDL_RenderPresent(renderer);
}