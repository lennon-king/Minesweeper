#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include "TextureManager.h"
#include "BoardManager.h"
#include "Random.h"
#include "Tiles.h"
using namespace std;

void RecursiveTileReveal(int yPosition, int xPosition, int height, int width, Tiles**& array2D, unsigned int& remainingTiles)
{
	if (0 <= yPosition && yPosition < height * 32 && 0 <= xPosition && xPosition < width * 32)
	{
		if (array2D[yPosition / 32][xPosition / 32].TileRevealed() == false && array2D[yPosition / 32][xPosition / 32].ReturnFlagValue() == false)
		{
			remainingTiles -= 1;
			array2D[yPosition / 32][xPosition / 32].RevealTile();
			if (array2D[yPosition / 32][xPosition / 32].ReturnTileValue() == 0)
			{
				array2D[yPosition / 32][xPosition / 32].RevealTile();
				RecursiveTileReveal(yPosition - 32, xPosition, height, width, array2D, remainingTiles);
				RecursiveTileReveal(yPosition + 32, xPosition, height, width, array2D, remainingTiles);
				RecursiveTileReveal(yPosition, xPosition - 32, height, width, array2D, remainingTiles);
				RecursiveTileReveal(yPosition, xPosition + 32, height, width, array2D, remainingTiles);
				RecursiveTileReveal(yPosition + 32, xPosition + 32, height, width, array2D, remainingTiles);
				RecursiveTileReveal(yPosition + 32, xPosition - 32, height, width, array2D, remainingTiles);
				RecursiveTileReveal(yPosition - 32, xPosition + 32, height, width, array2D, remainingTiles);
				RecursiveTileReveal(yPosition - 32, xPosition - 32, height, width, array2D, remainingTiles);
			}
		}
	}
}
void GenerateBoard(unsigned int mines, unsigned int width, unsigned int height, Tiles**& array2D)
{
	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
		{
			array2D[i][j].SetDefault();
			
		}
	}

	for (int i = 0; i < (signed)mines; i++)
	{
		int randomX = Random::Int(0, width - 1);
		int randomY = Random::Int(0, height - 1);
		if (array2D[randomY][randomX].ReturnTileValue() != 9)
			array2D[randomY][randomX].ChangeTileValue(9);
		else
			i -= 1;
	}
	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
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
			if (i != 0 && j != width - 1)
				if (array2D[i - 1][j + 1].ReturnTileValue() == 9)
					totalMines += 1;
			if (j != 0)
				if (array2D[i][j - 1].ReturnTileValue() == 9)
					totalMines += 1;
			if (j != width - 1)
				if (array2D[i][j + 1].ReturnTileValue() == 9)
					totalMines += 1;
			if (i != height - 1 && j != 0)
				if (array2D[i + 1][j - 1].ReturnTileValue() == 9)
					totalMines += 1;
			if (i != height - 1)
				if (array2D[i + 1][j].ReturnTileValue() == 9)
					totalMines += 1;
			if (i != height - 1 && j != width - 1)
				if (array2D[i + 1][j + 1].ReturnTileValue() == 9)
					totalMines += 1;
			array2D[i][j].ChangeTileValue(totalMines);
		}
	}
}
void DisplayDigit(unsigned int digit, sf::Sprite& digits, sf::RenderWindow& window)
{
	if (digit == 0)
	{
		digits.setTextureRect(sf::Rect<int>(0, 0, 21, 32));
		window.draw(digits);
	}
	else if (digit == 1)
	{
		digits.setTextureRect(sf::Rect<int>(21, 0, 21, 32));
		window.draw(digits);
	}
	else if (digit == 2)
	{
		digits.setTextureRect(sf::Rect<int>(42, 0, 21, 32));
		window.draw(digits);
	}
	else if (digit == 3)
	{
		digits.setTextureRect(sf::Rect<int>(63, 0, 21, 32));
		window.draw(digits);
	}
	else if (digit == 4)
	{
		digits.setTextureRect(sf::Rect<int>(84, 0, 21, 32));
		window.draw(digits);
	}
	else if (digit == 5)
	{
		digits.setTextureRect(sf::Rect<int>(105, 0, 21, 32));
		window.draw(digits);
	}
	else if (digit == 6)
	{
		digits.setTextureRect(sf::Rect<int>(126, 0, 21, 32));
		window.draw(digits);
	}
	else if (digit == 7)
	{
		digits.setTextureRect(sf::Rect<int>(147, 0, 21, 32));
		window.draw(digits);
	}
	else if (digit == 8)
	{
		digits.setTextureRect(sf::Rect<int>(168, 0, 21, 32));
		window.draw(digits);
	}
	else if (digit == 9)
	{
		digits.setTextureRect(sf::Rect<int>(189, 0, 21, 32));
		window.draw(digits);
	}
	else if (digit == 10)
	{
		digits.setTextureRect(sf::Rect<int>(208, 0, 21, 32));
		window.draw(digits);
	}
}
int main()
{
	// set up textures
	unordered_map<string, sf::Texture> textures;
	sf::Sprite mine(TextureManager::GetTexture("mine"));
	sf::Sprite debug(TextureManager::GetTexture("debug"));
	sf::Sprite digits(TextureManager::GetTexture("digits"));
	sf::Sprite face_happy(TextureManager::GetTexture("face_happy"));
	sf::Sprite face_lose(TextureManager::GetTexture("face_lose"));
	sf::Sprite face_win(TextureManager::GetTexture("face_win"));
	sf::Sprite flag(TextureManager::GetTexture("flag"));
	sf::Sprite number_1(TextureManager::GetTexture("number_1"));
	sf::Sprite number_2(TextureManager::GetTexture("number_2"));
	sf::Sprite number_3(TextureManager::GetTexture("number_3"));
	sf::Sprite number_4(TextureManager::GetTexture("number_4"));
	sf::Sprite number_5(TextureManager::GetTexture("number_5"));
	sf::Sprite number_6(TextureManager::GetTexture("number_6"));
	sf::Sprite number_7(TextureManager::GetTexture("number_7"));
	sf::Sprite number_8(TextureManager::GetTexture("number_8"));
	sf::Sprite test_1(TextureManager::GetTexture("test_1"));
	sf::Sprite test_2(TextureManager::GetTexture("test_2"));
	sf::Sprite test_3(TextureManager::GetTexture("test_3"));
	sf::Sprite tile_hidden(TextureManager::GetTexture("tile_hidden"));
	sf::Sprite tile_revealed(TextureManager::GetTexture("tile_revealed"));


	// create window
	BoardManager board;
	board.StoreValues("boards/config.cfg");
	sf::RenderWindow window(sf::VideoMode(board.ReturnWidth() * 32, board.ReturnHeight() * 32 + 100), "Minesweeper");

	// generate mines and attribute values
	unsigned int width = board.ReturnWidth();
	unsigned int defaultWidth = width;
	unsigned int height = board.ReturnHeight();
	unsigned int defaultHeight = height;
	unsigned int mines = board.ReturnMineCount();
	unsigned int defaultMines = mines;
	unsigned int tileCount = board.ReturnTileCount();
	unsigned int defaultTileCount = board.ReturnTileCount();

	Tiles** array2D = new Tiles * [height];
	for (unsigned int i = 0; i < height; i++)
		array2D[i] = new Tiles[width];

	GenerateBoard(mines, width, height, array2D);

	// sets framerate to same as desktop
	window.setVerticalSyncEnabled(true);

	// is debug mode on?
	bool debugMode = false;
	// used to reset debugmode on new boards
	bool debugOn = 0;
	// is the game won? lost? neither?
	int gameState = 0;
	unsigned int remainingTiles = tileCount - mines;
	int RemainingFlags = mines;
	// main game loop
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					unsigned int xPosition = event.mouseButton.x / 32;
					unsigned int yPosition = event.mouseButton.y / 32;
					if (event.mouseButton.y < (signed)height * 32 && event.mouseButton.x < (signed)width * 32 && gameState == 0)
						if (array2D[yPosition][xPosition].TileRevealed() == false)
						{
							array2D[yPosition][xPosition].FlagTile();
							if (array2D[yPosition][xPosition].ReturnFlagValue() == true)
								RemainingFlags -= 1;
							else
								RemainingFlags += 1;
						}
				}
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					unsigned int xPosition = event.mouseButton.x;
					unsigned int yPosition = event.mouseButton.y;
					if (0 < yPosition && yPosition < height * 32 && 0 < xPosition && xPosition < width * 32 && gameState == 0)
					{
						RecursiveTileReveal(yPosition, xPosition, height, width, array2D, remainingTiles);
					}
					else if (height * 32 < yPosition && yPosition < height * 32 + 64 && height * 32 < xPosition && xPosition < height * 32 + 64 && gameState == 0)
					{
						if (debugMode == false)
						{
							debugOn = true;
							debugMode = true;
						}
						else if (debugMode == true)
						{
							debugOn = false;
							debugMode = false;
						}
					}
					else if (height * 32 < yPosition && yPosition < height * 32 + 64 && width * 16 - 32 < xPosition && xPosition < width * 16 + 32)
					{
						mines = defaultMines;
						width = defaultWidth;
						height = defaultHeight;
						tileCount = defaultTileCount;
						GenerateBoard(mines, width, height, array2D);
						gameState = 0;
						debugMode = false;
						remainingTiles = tileCount - mines;
						RemainingFlags = mines;
					}
					else if (height * 32 < yPosition && yPosition < height * 32 + 64 && height * 32 + 64 < xPosition && xPosition < height * 32 + 128)
					{
						for (unsigned int i = 0; i < height; i++)
						{
							for (unsigned int j = 0; j < width; j++)
							{
								array2D[i][j].SetDefault();

							}
						}
						board.StorePremadeValues("boards/testboard1.brd", array2D);
						gameState = 0;
						debugMode = false;
						tileCount = defaultTileCount;
						mines = board.ReturnMineCount();
						remainingTiles = tileCount - mines;
						RemainingFlags = mines;
					}
					else if (height * 32 < yPosition && yPosition < height * 32 + 64 && height * 32 + 128 < xPosition && xPosition < height * 32 + 192)
					{
						for (unsigned int i = 0; i < height; i++)
						{
							for (unsigned int j = 0; j < width; j++)
							{
								array2D[i][j].SetDefault();
							}
						}
						board.StorePremadeValues("boards/testboard2.brd", array2D);
						gameState = 0;
						debugMode = false;
						tileCount = defaultTileCount;
						mines = board.ReturnMineCount();
						remainingTiles = tileCount - mines;
						RemainingFlags = mines;

					}
					else if (height * 32 < yPosition && yPosition < height * 32 + 64 && height * 32 + 192 < xPosition && xPosition < height * 32 + 256)
					{
						for (unsigned int i = 0; i < height; i++)
						{
							for (unsigned int j = 0; j < width; j++)
							{
								array2D[i][j].SetDefault();
							}
						}
						board.StorePremadeValues("boards/testboard3.brd", array2D);
						gameState = 0;
						debugMode = false;
						tileCount = defaultTileCount;
						mines = board.ReturnMineCount();
						remainingTiles = tileCount - mines;
						RemainingFlags = mines;
					}
				}
			}
			default:
				break;
			}
		}
		window.clear(sf::Color::White);
		for (unsigned int i = 0; i < width; i++)
		{
			for (unsigned int j = 0; j < height; j++)
			{
				int tile = array2D[j][i].ReturnTileValue();
				tile_revealed.setPosition((float)i * 32, (float)j * 32);
				number_1.setPosition((float)i * 32, (float)j * 32);
				number_2.setPosition((float)i * 32, (float)j * 32);
				number_3.setPosition((float)i * 32, (float)j * 32);
				number_4.setPosition((float)i * 32, (float)j * 32);
				number_5.setPosition((float)i * 32, (float)j * 32);
				number_6.setPosition((float)i * 32, (float)j * 32);
				number_7.setPosition((float)i * 32, (float)j * 32);
				number_8.setPosition((float)i * 32, (float)j * 32);
				mine.setPosition((float)i * 32, (float)j * 32);
				tile_hidden.setPosition((float)i * 32, (float)j * 32);
				flag.setPosition((float)i * 32, (float)j * 32);
				debug.setPosition((float)height * 32, (float)height * 32);
				window.draw(debug);
				face_happy.setPosition((float)width * 16 - 32, (float)height * 32);
				face_lose.setPosition((float)width * 16 - 32, (float)height * 32);
				face_win.setPosition((float)width * 16 - 32, (float)height * 32);
				test_1.setPosition((float)height * 32 + 64, (float)height * 32);
				test_2.setPosition((float)height * 32 + 128, (float)height * 32);
				test_3.setPosition((float)height * 32 + 192, (float)height * 32);
				window.draw(test_1);
				window.draw(test_2);
				window.draw(test_3);
				if (gameState == 0)
					window.draw(face_happy);
				if (debugOn)
					debugMode = true;
				digits.setPosition(32, (float)height * 32);
				unsigned int PosRemainingFlags = RemainingFlags;
				if (RemainingFlags < 0)
					PosRemainingFlags *= -1;
				unsigned int digit;
				digit = PosRemainingFlags % 10;
				digits.setPosition(84, (float)height * 32);
				DisplayDigit(digit, digits, window);
				digit = (PosRemainingFlags / 10) % 10;
				digits.setPosition(63, (float)height * 32);
				DisplayDigit(digit, digits, window);
				digit = (PosRemainingFlags / 100) % 10;
				digits.setPosition(42, (float)height * 32);
				DisplayDigit(digit, digits, window);
				if (RemainingFlags < 0)
				{
					digit = 10;
					digits.setPosition(21, (float)height * 32);
					DisplayDigit(digit, digits, window);
				}
				if (array2D[j][i].TileRevealed() == true)
				{
					if (tile == 0)
						window.draw(tile_revealed);
					if (tile == 1)
					{
						window.draw(tile_revealed);
						window.draw(number_1);
					}
					if (tile == 2)
					{
						window.draw(tile_revealed);
						window.draw(number_2);
					}
					if (tile == 3)
					{
						window.draw(tile_revealed);
						window.draw(number_3);
					}
					if (tile == 4)
					{
						window.draw(tile_revealed);
						window.draw(number_4);
					}
					if (tile == 5)
					{
						window.draw(tile_revealed);
						window.draw(number_5);
					}
					if (tile == 6)
					{
						window.draw(tile_revealed);
						window.draw(number_6);
					}
					if (tile == 7)
					{
						window.draw(tile_revealed);
						window.draw(number_7);
					}
					if (tile == 8)
					{
						window.draw(tile_revealed);
						window.draw(number_8);
					}
					if (tile == 9)
					{
						window.draw(tile_revealed);
						window.draw(mine);
						window.draw(face_lose);
						gameState = -1;
						debugMode = true;
					}
					if (remainingTiles == 0)
					{
						window.draw(face_win);
						gameState = 1;
						RemainingFlags = 0;
						debugMode = true;
					}
				}
				else
				{
					window.draw(tile_hidden);
					if (debugMode == true)
					{
						if (tile == 9 && array2D[j][i].ReturnFlagValue() == false && gameState == 0 && debugOn)
						{
							window.draw(tile_revealed);
							window.draw(mine);
						}
						else if (tile == 9 && gameState == -1 && array2D[j][i].ReturnFlagValue() == false)
						{
							window.draw(tile_revealed);
							window.draw(mine);
						}
						else if (tile == 9 && gameState == 1)
						{
							window.draw(flag);
						}
					}
					if (array2D[j][i].ReturnFlagValue() == true)
						window.draw(flag);
				}
			}
		}
		window.display();
	}
	// clear all
	TextureManager::Clear();
	for (unsigned int i = 0; i < height; i++)
	{
		delete[] array2D[i];
	}
	delete[] array2D;
	return 0;
}