#pragma once
class Tiles
{
	// 0 for blank, 1-8 for surrounding tiles, 9 for bomb
	unsigned int _tileValue;
	// 0 unflaged, 1 flaged (unreveiled)
	bool _flaged;
	// 0 unrevealed, 1 revealed
	bool _revealed;
public:
	Tiles(unsigned int tileValue = 0, bool flaged = false, bool revealed = false);
	void FlagTile();
	void RevealTile();
	unsigned int ReturnTileValue();
	bool ReturnFlagValue();
	bool TileRevealed();
	void ChangeTileValue(unsigned int value);
	void SetDefault();
};

