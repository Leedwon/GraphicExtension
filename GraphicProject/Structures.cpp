#include "Structures.h"

RGB operator+(const RGB & l, const RGB & r){
	RGB result;
	result.r = l.r + r.r;
	result.g = l.g + r.g;
	result.b = l.b + r.b;
	return result;
}

RGB operator-(const RGB & l, const RGB & r){
	RGB result;
	result.r = l.r - r.r;
	result.g = l.g - r.g;
	result.b = l.b - r.b;
	return result;
}

bool operator==(const RGB & l, const RGB & r){
	if(l.r == r.r) {
		if(l.g == r.g) {
			if (l.b == l.b)
				return true;
		}
	}
	return false;
}

bool operator!=(const RGB & l, const RGB & r)
{
	if (l.r != r.r) {
		if(l.g != r.g) {
			if (l.b != r.b)
				return true;
		}
	}
	return false;
}
