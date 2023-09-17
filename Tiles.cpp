#include "Tiles.h"
#include "iostream"
using namespace std;

Tiles::Tiles(unsigned int tileValue, bool flaged, bool revealed)
{
	_tileValue = tileValue;
	_flaged = flaged;
	_revealed = revealed;
}

void Tiles::FlagTile()
{
	if (_flaged == false)
	{
		_flaged = true;
	}
	else
		_flaged = false;
}

void Tiles::RevealTile()
{
	if (_revealed == false)
		_revealed = true;
}

bool Tiles::TileRevealed()
{
	if (_revealed == true)
		return true;
	return false;
}

unsigned int Tiles::ReturnTileValue()
{
	return _tileValue;
}

bool Tiles::ReturnFlagValue()
{
	return _flaged;
}


void Tiles::ChangeTileValue(unsigned int value)
{
	_tileValue = value;
}

void Tiles::SetDefault()
{
	_tileValue = 0;
	_flaged = false;
	_revealed = false;
}