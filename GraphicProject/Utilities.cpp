#include "Utilities.h"

SDL_Color operator+(const SDL_Color & l, const SDL_Color & r){
	SDL_Color result;
	result.r = l.r + r.r;
	result.g = l.g + r.g;
	result.b = l.b + r.b;
	return result;
}

SDL_Color operator-(const SDL_Color & l, const SDL_Color & r){
	SDL_Color result;
	result.r = l.r - r.r;
	result.g = l.g - r.g;
	result.b = l.b - r.b;
	return result;

}

bool operator==(const SDL_Color & l, const SDL_Color & r){
	if (l.r == r.r) {
		if (l.g == r.g) {
			if (l.b == r.b)
				return true;
		}
	}
	return false;
}

bool operator!=(const SDL_Color & l, const SDL_Color & r){
	if (l.r != r.r) {
		if (l.g != r.g) {
			if (l.b != r.b)
				return true;
		}
	}
	return false;
}
