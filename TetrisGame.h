#pragma once

#include "TetrisBoard.h"

class PreviewBox;
class ScoreBoard;
class Timer;

class TetrisGame
{
public:
	TetrisGame(void);
	~TetrisGame(void);

	void Start();
	sf::RenderWindow& GetWindow();

	bool IsExiting();

private:
	void GameLoop(float);
	void DrawBoard();

	double totalTimeElapsed;
	float tickSpeed;
	float tickTimeElapsed;

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
	TetrisPiece* nextPiece;

	PreviewBox* _previewBox;
	ScoreBoard* _scoreBoard;

	Timer* _timer;

	void CreateNewPiece();
};

