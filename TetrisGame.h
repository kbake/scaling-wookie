#pragma once

#include "TetrisBoard.h"

class TetrisGame
{
public:
	TetrisGame(void);
	~TetrisGame(void);

	void Start();
	sf::RenderWindow& GetWindow();

	bool IsExiting();

//	static const int BOARD_WIDTH = 10;	// Board width in blocks
//	static const int BOARD_HEIGHT = 20;		// Board height in blocks
//	static const int BLOCKSIZE = 20;			// Block size in pixels

private:
	void GameLoop();
	void DrawBoard();

	sf::RenderWindow _mainWindow;

	TetrisBoard board;
//	int _board[BOARD_WIDTH][BOARD_HEIGHT];

	//int currentPiece;

	sf::Vector2i _boardLocation;

	//std::list<int*> _pieces;
	std::list<sf::Sprite*> spriteList;

	sf::Texture _blockTexture;
	sf::Sprite _blockSprite;

	enum GameState { ShowingSplash, ShowingMenu, Playing, Paused, Exiting };
	enum BlockState { Starting, Moving, Stopped };

	GameState _gameState;
	BlockState _blockState;

	/*struct Piece {
		int x;
		int y;
		int length;
		int** shape;
	};*/

	TetrisPiece _pieces[6];

	TetrisPiece* currentPiece;

	void CreateNewPiece();

	bool canRotate(TetrisPiece&);
	bool canMoveRight(TetrisPiece&);
	bool canMoveLeft(TetrisPiece&);
	bool canMoveDown(TetrisPiece&);
};

