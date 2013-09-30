#include "stdafx.h"
#include "TetrisGame.h"
#include "TetrisBoard.h"
#include "TetrisPiece.h"
#include "PreviewBox.h"
#include "ScoreBoard.h"
#include "Timer.h"


TetrisGame::TetrisGame(void) :
	_gameState(GameState::Playing),
	totalTimeElapsed(0),
	tickSpeed(1),
	tickTimeElapsed(0)
{
	// randomize currentPiece
	srand(time(NULL));
}


TetrisGame::~TetrisGame(void)
{
	if (currentPiece)
	{
		delete currentPiece;
		currentPiece = NULL;
	}

	if (nextPiece)
	{
		delete nextPiece;
		nextPiece = NULL;
	}

	if (_previewBox)
	{
		delete _previewBox;
		_previewBox = NULL;
	}

	if (_scoreBoard)
	{
		delete _scoreBoard;
		_scoreBoard = NULL;
	}

	if (_timer)
	{
		delete _timer;
		_timer = NULL;
	}
}

void TetrisGame::Start()
{
	_mainWindow.create(sf::VideoMode(800, 600), "Tetris Clone!");

	_boardLocation = sf::Vector2i(0, 0);

	_blockTexture.loadFromFile("images/block.png");
	//_blockTexture.setRepeated(true);

	_blockSprite.setTexture(_blockTexture);
	_blockSprite.setColor(sf::Color(0, 255, 0));

	TetrisPiece ip;
	/*
	{0, 0, 0, 0},
	{1, 1, 1, 1},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
	};
	*/
	ip.SetTexture(_blockTexture);
	ip.SetLength(4);
	ip.SetColor(sf::Color(100, 30, 150));
	ip.GetShape()[0][1] = 1;
	ip.GetShape()[1][1] = 1;
	ip.GetShape()[2][1] = 1;
	ip.GetShape()[3][1] = 1;


	TetrisPiece jp;
	jp.SetTexture(_blockTexture);
	jp.SetLength(3);
	jp.SetColor(sf::Color(12, 200, 120));
	jp.GetShape()[0][2] = 1;
	jp.GetShape()[1][0] = 1;
	jp.GetShape()[1][1] = 1;
	jp.GetShape()[1][2] = 1;
/*	int tempjp[3][3] = {
	{0, 0, 1},
	{1, 1, 1},
	{0, 0, 0}
	};
*/

	TetrisPiece bp;
	bp.SetTexture(_blockTexture);
	bp.SetLength(2);
	bp.SetColor(sf::Color(255, 150, 100));
	bp.GetShape()[0][0] = 1;
	bp.GetShape()[0][1] = 1;
	bp.GetShape()[1][0] = 1;
	bp.GetShape()[1][1] = 1;
/*	int tempbp[2][2] = {
	{1, 1},
	{1, 1}
	};
*/

	TetrisPiece sp;
	sp.SetTexture(_blockTexture);
	sp.SetLength(3);
	sp.SetColor(sf::Color(0, 100, 255));
	sp.GetShape()[0][1] = 1;
	sp.GetShape()[0][2] = 1;
	sp.GetShape()[1][0] = 1;
	sp.GetShape()[1][1] = 1;
/*	int tempsp[3][3] = {
	{0, 1, 1},
	{1, 1, 0},
	{0, 0, 0}
	};
*/

	TetrisPiece tp;
	tp.SetTexture(_blockTexture);
	tp.SetLength(3);
	tp.SetColor(sf::Color(0, 255, 0));
	tp.GetShape()[0][1] = 1;
	tp.GetShape()[1][0] = 1;
	tp.GetShape()[1][1] = 1;
	tp.GetShape()[1][2] = 1;
/*	int temptp[3][3] = {
	{0, 1, 0},
	{1, 1, 1},
	{0, 0, 0}
	};
*/

	TetrisPiece zp;
	zp.SetTexture(_blockTexture);
	zp.SetLength(3);
	zp.SetColor(sf::Color(255, 0, 0));
	zp.GetShape()[0][0] = 1;
	zp.GetShape()[0][1] = 1;
	zp.GetShape()[1][1] = 1;
	zp.GetShape()[1][2] = 1;
/*	int tempzp[3][3] = {
	{1, 1, 0},
	{0, 1, 1},
	{0, 0, 0}
	};
*/
	_pieces[0] = ip;
	_pieces[1] = jp;
	_pieces[2] = bp;
	_pieces[3] = sp;
	_pieces[4] = tp;
	_pieces[5] = zp;

	currentPiece = new TetrisPiece(_pieces[rand() % 6]);
	nextPiece = new TetrisPiece(_pieces[rand() % 6]);

	_previewBox = new PreviewBox();
	_previewBox->SetLocation(sf::Vector2i(500, 20));
	_previewBox->SetSize(sf::Vector2i(6, 5));
	_previewBox->SetTexture(_blockTexture);
	_previewBox->SetPiece(*nextPiece);

	_scoreBoard = new ScoreBoard(sf::Vector2f(500, 200), sf::Vector2f(6, 2));
	_scoreBoard->SetTexture(_blockTexture);
	_scoreBoard->SetFont("fonts/arial.ttf");
	_scoreBoard->SetScore(0);

	board.SetTexture(_blockTexture);
	board.SetScoreBoard(*_scoreBoard);

	_timer = new Timer();
	_timer->SetFont("fonts/arial.ttf");
	_timer->SetText("00:00");
	_timer->SetTexture(_blockTexture);
	_timer->SetPosition(sf::Vector2f(500, 400));
	_timer->SetSize(sf::Vector2f(6, 2));

	_gameMusic.openFromFile("audio/music/recording.wav");
	_gameMusic.setLoop(true);
	_gameMusic.setVolume(50.f);
	_gameMusic.play();

	_rotateBuffer.loadFromFile("audio/fx/rotate.ogg");
	_rotateSound.setBuffer(_rotateBuffer);

	sf::Clock clock;
	sf::Time elapsed;

	while (!IsExiting())
	{
		elapsed = clock.restart();
		GameLoop(elapsed.asSeconds());
	}
}

void TetrisGame::CreateNewPiece()
{
	delete currentPiece;
	currentPiece = NULL;

	currentPiece = nextPiece;
	//currentPiece->SetCoords(sf::Vector2i(4, 0));

	nextPiece = new TetrisPiece(_pieces[rand() % 6]);

	_previewBox->SetPiece(*nextPiece);
}

void TetrisGame::GameLoop(float timeDelta)
{
	sf::Event event;
	_mainWindow.pollEvent(event);

	switch (_gameState)
	{
	case TetrisGame::ShowingSplash:
		break;
	case TetrisGame::ShowingMenu:
		break;
	case TetrisGame::Paused:
		break;
	case TetrisGame::Playing:
		totalTimeElapsed += timeDelta;
		// I know...this is gross
		_timer->SetText(std::to_string((int)totalTimeElapsed/3600) + "" + std::to_string((int)totalTimeElapsed/60) + ":" + (((int)totalTimeElapsed % 60) < 10 ? "0" : "") + std::to_string((int)totalTimeElapsed % 60));

		if (tickSpeed != .25 && (int)totalTimeElapsed/60 >= 2) tickSpeed = .25;
		else if (tickSpeed != .5 && (int)totalTimeElapsed/60 >= 1) tickSpeed = .5;

		tickTimeElapsed += timeDelta;

		_mainWindow.clear(sf::Color(0, 255, 255));

		board.Update(timeDelta);

		board.Draw(_mainWindow);
		currentPiece->Draw(_mainWindow);
		_previewBox->Draw(_mainWindow);
		_scoreBoard->Draw(_mainWindow);
		_timer->Draw(_mainWindow);

		_mainWindow.display();

		if (board.isFull())	// check if any pieces are at the top of the board
		{
			_gameState = TetrisGame::Exiting;
		}
		
		// add score based off size
		//_scoreBoard->SetScore(pow(10, temp_nums.size()));	need to implement the even system -_-

		if (event.type == sf::Event::Closed)
		{
			_gameState = GameState::Exiting;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				_gameState = GameState::Exiting;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				//_blockSprite.move(32.f, 0.f);
				if (board.canMoveRight(*currentPiece)) 
				{
					currentPiece->IncrementCoords(sf::Vector2i(1, 0));
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				//_blockSprite.move(-32.f, 0.f);
				if (board.canMoveLeft(*currentPiece))
				{
					currentPiece->IncrementCoords(sf::Vector2i(-1, 0));
				}
			}
			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				currentPiece->IncrementCoords(sf::Vector2i(0, -1));
			}*/
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (board.canMoveDown(*currentPiece))
				{
					currentPiece->IncrementCoords(sf::Vector2i(0, 1));
				}
				else
				{
					// add current piece to the board (however I plan on doing that)
					board.AddPiece(*currentPiece);

					// create a new randomized piece at the top of the screen
					CreateNewPiece();
				}

				//std::cout << currentPiece->GetCoords().x << " " << currentPiece->GetCoords().y << std::endl;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (board.canRotate(*currentPiece))
				{
					_rotateSound.play();

					currentPiece->Rotate();
				}
			}
		}

		if (tickTimeElapsed > tickSpeed)
		{
			tickTimeElapsed = 0;

			if (board.canMoveDown(*currentPiece))
			{
				currentPiece->IncrementCoords(sf::Vector2i(0, 1));
			}
			else
			{
				// add current piece to the board (however I plan on doing that)
				board.AddPiece(*currentPiece);

				// create a new randomized piece at the top of the screen
				CreateNewPiece();
			}
		}

		break;
	}
}

bool TetrisGame::IsExiting()
{
	if (_gameState == TetrisGame::Exiting)
	{
		return true;
	}

	return false;
}