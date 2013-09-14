#pragma once

#include "TetrisPiece.h"

class TetrisBoard
{
public:
	TetrisBoard(void);
	~TetrisBoard(void);

	int GetBoardWidth() const;
	int GetBoardHeight() const;

	void SetTexture(sf::Texture&);

	void AddPiece(TetrisPiece&);
	
	bool isFull() const;

	bool canRotate(TetrisPiece&) const;
	bool canMoveRight(TetrisPiece&) const;
	bool canMoveLeft(TetrisPiece&) const;
	bool canMoveDown(TetrisPiece&) const;

	int CheckRow(int) const;
	void DeleteRow(int);
	void MoveRows(int);

	void Update(double);
	void Draw(sf::RenderWindow&);	// would be nice to just create these sprites once, instead of every frame, should be easy

private:
	static const int BOARD_WIDTH = 10;
	static const int BOARD_HEIGHT = 20;

	sf::Texture _texture;

	std::vector<sf::Sprite> _sprites;

public:
	int board[BOARD_WIDTH][BOARD_HEIGHT];	// I'd prefer not to make this public but I'm also lazy
};

