#include "BoardManager.h"

BoardManager::BoardManager(unsigned int width, unsigned int height,
	unsigned int mineCount, unsigned int tileCount)
{
	_width = width;
	_height = height;
	_mineCount = mineCount;
	_tileCount = tileCount;
}
void BoardManager::StoreValues(string fileName)
{
	ifstream boardInfo(fileName);
	if (boardInfo.is_open())
	{
		string lineFromFile;
		getline(boardInfo, lineFromFile);
		_width = stoi(lineFromFile) * 32;
		getline(boardInfo, lineFromFile);
		_height = stoi(lineFromFile) * 32 + 100;
		getline(boardInfo, lineFromFile);
		_mineCount = stoi(lineFromFile);
		_tileCount = (_width / 32) * ((_height - 100)/ 32);
	}
	else
		cout << "File couldn't open! Default Board Loaded." << endl;
}
void BoardManager::StorePremadeValues(string fileName, Tiles**& array2D)
{
	ifstream boardInfo(fileName);
	if (boardInfo.is_open())
	{
		unsigned int totalHeight = 0;
		string lineFromFile;
		unsigned int totalMine = 0;
		while (getline(boardInfo, lineFromFile))
		{
			totalHeight += 1;
			for (unsigned int i = 0; i < lineFromFile.length(); i++)
			{
				if (lineFromFile[i] == '1')
				{
					array2D[totalHeight - 1][i].ChangeTileValue(9);
					totalMine += 1;
				}
			}
		}
		_height = totalHeight * 32 + 100;
		_width = lineFromFile.length() * 32;
		_mineCount = totalMine;
		_tileCount = (_width / 32) * ((_height - 100) / 32);
		for (unsigned int i = 0; i < (_height - 100) / 32; i++)
		{
			for (unsigned int j = 0; j < _width / 32; j++)
			{
				if (array2D[i][j].ReturnTileValue() == 9)
					continue;
				unsigned int totalMines = 0;
				if (i != 0 && j != 0)
					if (array2D[i - 1][j - 1].ReturnTileValue() == 9)
						totalMines += 1;
				if (i != 0)
					if (array2D[i - 1][j].ReturnTileValue() == 9)
						totalMines += 1;
				if (i != 0 && j != _width / 32 - 1)
					if (array2D[i - 1][j + 1].ReturnTileValue() == 9)
						totalMines += 1;
				if (j != 0)
					if (array2D[i][j - 1].ReturnTileValue() == 9)
						totalMines += 1;
				if (j != _width / 32 - 1)
					if (array2D[i][j + 1].ReturnTileValue() == 9)
						totalMines += 1;
				if (i != (_height - 100) / 32 - 1 && j != 0)
					if (array2D[i + 1][j - 1].ReturnTileValue() == 9)
						totalMines += 1;
				if (i != (_height - 100) / 32 - 1)
					if (array2D[i + 1][j].ReturnTileValue() == 9)
						totalMines += 1;
				if (i != (_height - 100) / 32 - 1 && j != _width / 32 - 1)
					if (array2D[i + 1][j + 1].ReturnTileValue() == 9)
						totalMines += 1;
				array2D[i][j].ChangeTileValue(totalMines);
			}
		}
	}
	else
		cout << "File couldn't open! Default Board Loaded." << endl;
}
unsigned int BoardManager::ReturnWidth()
{
	return (_width/32);
}
unsigned int BoardManager::ReturnHeight()
{
	return (_height - 100)/32;
}
unsigned int BoardManager::ReturnMineCount()
{
	return _mineCount;
}
unsigned int BoardManager::ReturnTileCount()
{
	return _tileCount;
}