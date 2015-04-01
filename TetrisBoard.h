#pragma once

#include "TetrisPiece.h"

class ScoreBoard;

class TetrisBoard
{
public:
	TetrisBoard(void);
	~TetrisBoard(void);

	int GetBoardWidth() const;
	int GetBoardHeight() const;

	void SetTexture(sf::Texture&);
	void SetScoreBoard(ScoreBoard&);

	void AddPiece(TetrisPiece&);
	
	const bool isFull() const;

	const bool canRotate(TetrisPiece&) const;
	const bool canMoveRight(TetrisPiece&) const;
	const bool canMoveLeft(TetrisPiece&) const;
	const bool canMoveDown(TetrisPiece&) const;

	int CheckRow(int) const;
	void DeleteRow(int);
	void MoveRows(int);

	void Update(double);
	void Draw(sf::RenderWindow&);	// would be nice to just create these sprites once, instead of every frame, should be easy
	void Reset();

private:
	static const int BOARD_WIDTH = 10;
	static const int BOARD_HEIGHT = 20;

	ScoreBoard* _scoreboard;

	sf::Texture _explosionTexture;
	sf::Texture _texture;
	sf::Sprite _explosionSprite;
	sf::Sound _explosion;
	sf::SoundBuffer _explosionBuffer;

	std::vector<sf::Sprite> _sprites;

	double _animationCurrentTime;
	double _animationTemp;
	float _animationTotalTime;
	int _animationIndex;
	int _animationSize;
	int _sizeX;
	int _sizeY;

	bool _isAnimating;

public:
	int board[BOARD_WIDTH][BOARD_HEIGHT];	// I'd prefer not to make this public but I'm also lazy
};

