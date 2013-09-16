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
	void CreateNewPiece();

	double totalTimeElapsed;
	float tickSpeed;
	float tickTimeElapsed;

	std::list<sf::Sprite*> spriteList;

	sf::RenderWindow _mainWindow;
	sf::Texture _blockTexture;
	sf::Sprite _blockSprite;
	sf::Vector2i _boardLocation;

	enum GameState { ShowingSplash, ShowingMenu, Playing, Paused, Exiting };

	GameState _gameState;

	TetrisBoard board;
	TetrisPiece _pieces[6];

	TetrisPiece* currentPiece;
	TetrisPiece* nextPiece;
	PreviewBox* _previewBox;
	ScoreBoard* _scoreBoard;
	Timer* _timer;
};

