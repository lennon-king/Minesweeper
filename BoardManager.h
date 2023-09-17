#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "Tiles.h"
using namespace std;

class BoardManager
{
	unsigned int _width;
	unsigned int _height;
	unsigned int _mineCount;
	unsigned int _tileCount;
public:
	BoardManager(unsigned int width = 800, unsigned int height = 600, 
		unsigned int mineCount = 50, unsigned int tileCount = 400);
	void StoreValues(string fileName);
	void StorePremadeValues(string fileName, Tiles**& array2D);
	unsigned int ReturnWidth();
	unsigned int ReturnHeight();
	unsigned int ReturnMineCount();
	unsigned int ReturnTileCount();
};

