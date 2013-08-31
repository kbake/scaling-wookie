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

private:
	void GameLoop();
	void DrawBoard();

	sf::RenderWindow _mainWindow;

	TetrisBoard board;

	sf::Vector2i _boardLocation;

	std::list<sf::Sprite*> spriteList;

	sf::Texture _blockTexture;
	sf::Sprite _blockSprite;

	enum GameState { ShowingSplash, ShowingMenu, Playing, Paused, Exiting };
	enum BlockState { Starting, Moving, Stopped };

	GameState _gameState;
	BlockState _blockState;

	TetrisPiece _pieces[6];

	TetrisPiece* currentPiece;

	void CreateNewPiece();

	bool canRotate(TetrisPiece&);
	bool canMoveRight(TetrisPiece&);
	bool canMoveLeft(TetrisPiece&);
	bool canMoveDown(TetrisPiece&);
};

