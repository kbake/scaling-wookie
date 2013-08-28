#pragma once

class TetrisBoard
{
public:
	TetrisBoard(void);
	~TetrisBoard(void);

	int GetBoardWidth() const;
	int GetBoardHeight() const;

	void AddPiece(TetrisPiece&);
	
	int CheckRow(int) const;
	void DeleteRow(int);

	void Draw(sf::RenderWindow&);

private:
	const int BOARD_WIDTH = 10;
	const int BOARD_HEIGHT = 20;

	sf::Texture _texture;

public:
	int board[BOARD_WIDTH][BOARD_HEIGHT];	// I'd prefer not to make this public but I'm also lazy
};

