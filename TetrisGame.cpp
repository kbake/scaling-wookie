#include "stdafx.h"
#include "TetrisGame.h"
#include "TetrisBoard.h"
#include "TetrisPiece.h"


TetrisGame::TetrisGame(void) :
	_gameState(GameState::Playing),
	_blockState(BlockState::Starting)
{
	// randomize currentPiece
	srand(time(NULL));
}


TetrisGame::~TetrisGame(void)
{
}

void TetrisGame::Start()
{
	_mainWindow.create(sf::VideoMode(800, 600), "Tetris Clone!");

	_boardLocation = sf::Vector2i(0, 0);

	// initialize the board to all zero
	//for (int y = 0; y < BOARD_HEIGHT; y++)
	//{
	//	for (int x = 0; x < BOARD_WIDTH; x++)
	//	{
	//		_board[x][y] = 0;
	//	}
	//}

	_blockTexture.loadFromFile("images/block.png");
	_blockTexture.setRepeated(true);

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
	ip.GetShape()[0][1] = 1;
	ip.GetShape()[1][1] = 1;
	ip.GetShape()[2][1] = 1;
	ip.GetShape()[3][1] = 1;


	TetrisPiece jp;
	jp.SetTexture(_blockTexture);
	jp.SetLength(3);
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

	
	currentPiece = _pieces[(rand() % 6)];

	board.SetTexture(_blockTexture);

	while (!IsExiting())
	{
		GameLoop();
	}
}

void TetrisGame::CreateNewPiece()
{
	currentPiece = _pieces[(rand() % 6)];
	currentPiece.SetCoords(sf::Vector2i(0, 0));
}

bool TetrisGame::canRotate(TetrisPiece& a_piece)
{
	// make temp array to hold rotated piece
	int** temp = new int*[a_piece.GetLength()];

	for (int i = 0; i < a_piece.GetLength(); i++)
	{
		temp[i] = new int[a_piece.GetLength()];
		for (int j = 0; j < a_piece.GetLength(); j++)
		{
			int tempint = (a_piece.GetLength() - 1) - i;
			temp[i][j] = a_piece.GetShape()[j][tempint];
		}
	}

	// check temp array vs right, left, and bottom areas to make sure it can rotate

	// vs right
	int size = a_piece.GetLength() + a_piece.GetCoords().x;

	if (size > board.GetBoardWidth())
	{
		for (int i = 0; i < a_piece.GetLength(); i++)
		{
			if (temp[a_piece.GetLength() - 1 - (size - board.GetBoardWidth())][i] == 1)
			{
				return false;
			}
		}
	}

	// vs left
	if (a_piece.GetCoords().x < 0)
	{
		for (int i = 0; i < a_piece.GetLength(); i++)
		{
			if (temp[abs(a_piece.GetCoords().x)][i] == 1)
			{
				return false;
			}
		}
	}

	// vs bottom
	int location = a_piece.GetCoords().y + a_piece.GetLength();

	if (location >= board.GetBoardHeight())
	{
		int tempnum = (a_piece.GetLength() - 1) - (location - board.GetBoardHeight());

		for (int i = 0; i < a_piece.GetLength(); i++)
		{
			if (temp[i][tempnum] == 1)
			{
				return false;
			}
		}
	}

	// check temp array vs other pieces in the way
	for (int i = a_piece.GetCoords().x, k = 0; i < size; i++, k++)
	{
		for (int j = a_piece.GetCoords().y, n = 0; j < size; j++, n++)
		{
			if (board.board[i][j] == 1 && temp[k][n] == 1)
			{
				return false;
			}
		}
	}

	// clean up the temp array and delete it
	for (int i = 0; i < a_piece.GetLength(); i++)
	{
		delete [] temp[i];
		temp[i] = NULL;
	}

	delete [] temp;
	temp = NULL;

	return true;
}

bool TetrisGame::canMoveRight(TetrisPiece& a_piece)
{
	int size = a_piece.GetLength() + a_piece.GetCoords().x;

	// if we are going outside of the bounds of the board...
	if (size >= board.GetBoardWidth())
	{
		for (int i = 0; i < a_piece.GetLength(); i++)
		{
//			std::cout << std::endl << "blah " << a_piece.length - 1 << std::endl;
			if (a_piece.GetShape()[a_piece.GetLength() - 1 - (size - board.GetBoardWidth())][i] == 1)
			{
				return false;
			}
		}

//		std::cout << std::endl;
	}

	// now loop through and see if there are any pieces in the way
	for (int i = a_piece.GetCoords().x + 1, k = 0; k < a_piece.GetLength(); i++, k++)
	{	
		for (int j = a_piece.GetCoords().y + 1, q = 0; q < a_piece.GetLength(); j++, q++)
		{
			//std::cout << a_piece.shape[q][k];
			if (a_piece.GetShape()[q][k] == 1 && board.board[j][i] == 1)
			{
				return false;
			}
		}
		//std::cout << std::endl;
	}
	//std::cout << std::endl;

	return true;
}

bool TetrisGame::canMoveLeft(TetrisPiece& a_piece)
{
	int location = a_piece.GetCoords().x - 1;

	// if we are going outside of the bounds of the board...
	if (location < 0)
	{
		for (int i = 0; i < a_piece.GetLength(); i++)
		{
			std::cout << "shape[" << abs(a_piece.GetCoords().x) << "][" << i << "] = " << a_piece.GetShape()[abs(a_piece.GetCoords().x)][i] << std::endl;
			if (a_piece.GetShape()[abs(a_piece.GetCoords().x)][i] == 1)
			{
				return false;
			}
		}
		std::cout << std::endl;
	}

	// now loop through and see if there are any pieces in the way
	for (int i = a_piece.GetCoords().x - 1, k = 0; k < a_piece.GetLength(); i++, k++)
	{	
		for (int j = a_piece.GetCoords().y - 1, q = 0; q < a_piece.GetLength(); j++, q++)
		{
//			std::cout << a_piece.shape[q][k];
			if (a_piece.GetShape()[q][k] == 1 && board.board[j][i] == 1)
			{
				return false;
			}
		}
//		std::cout << std::endl;
	}
//	std::cout << std::endl;

	return true;
}

bool TetrisGame::canMoveDown(TetrisPiece& a_piece)
{
	int location = a_piece.GetCoords().y + a_piece.GetLength() + 1;

	// if we are going outside of the bounds of the board...
	if (location >= board.GetBoardHeight())
	{
		int tempnum = (a_piece.GetLength() - 1) - (location - board.GetBoardHeight());

		for (int i = 0; i < a_piece.GetLength(); i++)
		{
			std::cout << "shape[" << i << "][" << tempnum << "] = " << a_piece.GetShape()[i][tempnum] << std::endl;
			if (a_piece.GetShape()[i][tempnum] == 1)
			{
				return false;
			}
		}
		std::cout << std::endl;
	}

	// now loop through and see if there are any pieces in the way
	for (int i = a_piece.GetCoords().x - 1, k = 0; k < a_piece.GetLength(); i++, k++)
	{	
		for (int j = a_piece.GetCoords().y - 1, q = 0; q < a_piece.GetLength(); j++, q++)
		{
			//std::cout << a_piece.shape[q][k];
			if (a_piece.GetShape()[q][k] == 1 && board.board[j][i] == 1)
			{
				return false;
			}
		}
		//std::cout << std::endl;
	}
	//std::cout << std::endl;

	return true;
}

//void TetrisGame::DrawBoard()
//{
//	/*for (std::list<sf::Sprite*>::const_iterator it = spriteList.begin(); it != spriteList.end(); it++)
//	{
//	//_mainWindow.draw(it);
//	_mainWindow.draw((**it));
//
//	//delete *it;
//	}*/
//
//	sf::Sprite* temp;
//
//	for (int x = 0; x < BOARD_WIDTH; x++)
//	{
//		for (int y = 0; y < BOARD_HEIGHT; y++)
//		{
//			temp = new sf::Sprite();
//			temp->setTexture(_blockTexture);
//			temp->setPosition(32.f * x, 32.f * y);
//
//			if (_board[x][y] != 0)
//			{
//				temp->setColor(sf::Color(15, 100, 200));
//			}
//			else
//			{
//				temp->setColor(sf::Color());
//			}
//
//			_mainWindow.draw(*temp);
//			delete temp;
//			temp = NULL;
//		}
//	}
//
//}

void TetrisGame::GameLoop()
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
		_mainWindow.clear(sf::Color(0, 255, 255));

		board.Draw(_mainWindow);
		currentPiece.Draw(_mainWindow);

		_mainWindow.display();

		/*for (std::list<sf::Sprite*>::iterator it = spriteList.begin(); it != spriteList.end(); it++)
		{
			delete (*it);
			(*it) = NULL;
		}*/

		//spriteList.clear();
		//_mainWindow.draw(_blockSprite);
		//_mainWindow.display();

		if (event.type == sf::Event::Closed)
		{
			_gameState = TetrisGame::Exiting;
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
				if (canMoveRight(currentPiece)) 
				{
					currentPiece.SetCoords(sf::Vector2i(1, 0));
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				//_blockSprite.move(-32.f, 0.f);
				if (canMoveLeft(currentPiece))
				{
					currentPiece.SetCoords(sf::Vector2i(-1, 0));
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				currentPiece.SetCoords(sf::Vector2i(0, -1));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (canMoveDown(currentPiece))
				{
					currentPiece.SetCoords(sf::Vector2i(0, 1));
				}
				else
				{
					// add current piece to the board (however I plan on doing that)
					board.AddPiece(currentPiece);

					// create a new randomized piece at the top of the screen
					CreateNewPiece();
				}

				std::cout << currentPiece.GetCoords().x << " " << currentPiece.GetCoords().y << std::endl;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (canRotate(currentPiece))
				{
					currentPiece.Rotate();
				}
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