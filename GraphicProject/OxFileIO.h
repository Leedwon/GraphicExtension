#pragma once
#include  "Ox.h"
#include <fstream>
#include "Header.h"
#include <string.h>

 class OxFileIO
{
public:
	static Ox* readOx(std::string fileName);
	static bool saveOx(std::string fileName, Ox *ox);
};

