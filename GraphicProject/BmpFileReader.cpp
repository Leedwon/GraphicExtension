#include "BmpFileReader.h"



BmpFileReader::BmpFileReader(std::string fileString) {
	filePath = fileString;
	surface = SDL_LoadBMP(filePath.c_str());
	handler = new SurfaceHandler(surface);
}

BmpFileReader::~BmpFileReader() {
	delete handler;
	SDL_free(surface);
}
