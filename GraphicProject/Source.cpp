#include <SDL.h>
#include <string>
#include "Image.h"

int main(int argc, char *args[]) {
	std::string pictureFile = "picture1.bmp";
	Image image(pictureFile);
	return 0;
}
