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

	Piece ip;
	/*int tempip[4][4] = new {
	{0, 0, 0, 0},
	{1, 1, 1, 1},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
	};*/
	//ip.shape = *tempip;
	ip.length = 4;
	ip.x = 0;
	ip.y = 0;
	ip.shape = new int*[4];
	for (int i = 0; i < 4; i++)
	{
		ip.shape[i] = new int[4];
		for (int j = 0; j < 4; j++)
		{
			ip.shape[i][j] = 0;
		}
	}
	ip.shape[0][1] = 1;
	ip.shape[1][1] = 1;
	ip.shape[2][1] = 1;
	ip.shape[3][1] = 1;

	Piece jp;
	jp.length = 3;
	jp.x = 0;
	jp.y = 0;
	jp.shape = new int*[jp.length];
	for (int i = 0; i < jp.length; i++)
	{
		jp.shape[i] = new int[jp.length];
		for (int j = 0; j < jp.length; j++)
		{
			jp.shape[i][j] = 0;
		}
	}
	jp.shape[0][2] = 1;
	jp.shape[1][0] = 1;
	jp.shape[1][1] = 1;
	jp.shape[1][2] = 1;
	/*	int tempjp[3][3] = {
	{0, 0, 1},
	{1, 1, 1},
	{0, 0, 0}
	};
*/


	Piece bp;
	bp.length = 2;
	bp.x = 0;
	bp.y = 0;
	bp.shape = new int*[2];
	for (int i = 0; i < bp.length; i++)
	{
		bp.shape[i] = new int[bp.length];
		for (int j = 0; j < bp.length; j++)
		{
			bp.shape[i][j] = 1;
		}
	}
/*	int tempbp[2][2] = {
	{1, 1},
	{1, 1}
	};
*/

	Piece sp;
	sp.length = 3;
	sp.x = 0;
	sp.y = 0;
	sp.shape = new int*[3];
	for (int i = 0; i < sp.length; i++)
	{
		sp.shape[i] = new int[sp.length];
		for (int j = 0; j < sp.length; j++)
		{
			sp.shape[i][j] = 0;
		}
	}
	sp.shape[0][1] = 1;
	sp.shape[0][2] = 1;
	sp.shape[1][0] = 1;
	sp.shape[1][1] = 1;
/*	int tempsp[3][3] = {
	{0, 1, 1},
	{1, 1, 0},
	{0, 0, 0}
	};
*/


	Piece tp;
	tp.length = 3;
	tp.x = 0;
	tp.y = 0;
	tp.shape = new int*[3];
	for (int i = 0; i < tp.length; i++)
	{
		tp.shape[i] = new int[tp.length];
		for (int j = 0; j < tp.length; j++)
		{
			tp.shape[i][j] = 0;
		}
	}
	tp.shape[0][1] = 1;
	tp.shape[1][0] = 1;
	tp.shape[1][1] = 1;
	tp.shape[1][2] = 1;
/*	int temptp[3][3] = {
	{0, 1, 0},
	{1, 1, 1},
	{0, 0, 0}
	};
*/


	Piece zp;
	zp.length = 3;
	zp.x = zp.y = 0;
	zp.shape = new int*[3];
	for (int i = 0; i < zp.length; i++)
	{
		zp.shape[i] = new int[zp.length];
		for (int j = 0; j < zp.length; j++)
		{
			zp.shape[i][j] = 0;
		}
	}
	zp.shape[0][0] = 1;
	zp.shape[0][1] = 1;
	zp.shape[1][1] = 1;
	zp.shape[1][2] = 1;
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
	
	currentPiece = _pieces[(rand() % (int)(6))];

	while (!IsExiting())
	{
		GameLoop();
	}
}

void TetrisGame::MovePiece(Piece& a_piece)
{
	a_piece.x += 32;
	a_piece.y += 32;
	/*switch (_blockState)
	{
	case BlockState::Starting:
		a_piece.x = 2;
		a_piece.y = 0;

		AddPiece(a_piece);

		_blockState = BlockState::Moving;

		break;
	case BlockState::Moving:
		break;
	case BlockState::Stopped:
		break;
	}*/
}

void TetrisGame::AddPiece(TetrisPiece& a_piece)
{
	int startX = a_piece.x;
	int startY = a_piece.y;

	/*for ( ; startX < startX + a_piece.length; startX++)
	{
	for ( ; startY < startY + a_piece.length; startY++)
	{
	_board[startX][startY]*/
}

void TetrisGame::RotatePiece(TetrisPiece& a_piece)
{
	int size = a_piece.length;
	int** temp = new int*[size];
	std::cout << "Before:" << std::endl;
	for (int k = 0; k < size; k++)
	{
		temp[k] = new int[size];
		for (int l = 0; l < size; l++)
		{
			std::cout << a_piece.shape[l][k];
			temp[k][l] = 0;
		}

		std::cout << std::endl;
	}
	std::cout << std::endl;
	// rotate the piece 90 degrees clockwise
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int tempint = (size - 1) - i;
			temp[i][j] = a_piece.shape[j][tempint];
		}
	}

	for (int iter = 0; iter < a_piece.length; iter++)
	{
		delete [] a_piece.shape[iter];	// delete each dynamically created int array
	}

	delete [] a_piece.shape;	// delete the dynamically created int* array

	a_piece.shape = &(*temp);

	std::cout << "After:" << std::endl;
	for (int i = 0; i < a_piece.length; i++)
	{
		for (int j = 0; j < a_piece.length; j++)
		{
			std::cout << a_piece.shape[j][i];
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}

bool TetrisGame::canRotate(TetrisPiece& a_piece)
{
	// make temp array to hold rotated piece
	int** temp = new int*[a_piece.length];

	for (int i = 0; i < a_piece.length; i++)
	{
		temp[i] = new int[a_piece.length];
		for (int j = 0; j < a_piece.length; j++)
		{
			int tempint = (a_piece.length - 1) - i;
			temp[i][j] = a_piece.shape[j][tempint];
		}
	}

	// check temp array vs right, left, and bottom areas to make sure it can rotate

	// vs right
	int size = a_piece.length + a_piece.x;

	if (size > BOARD_WIDTH)
	{
		for (int i = 0; i < a_piece.length; i++)
		{
			if (temp[a_piece.length - 1 - (size - BOARD_WIDTH)][i] == 1)
			{
				return false;
			}
		}
	}

	// vs left
	if (a_piece.x < 0)
	{
		for (int i = 0; i < a_piece.length; i++)
		{
			if (temp[abs(a_piece.x)][i] == 1)
			{
				return false;
			}
		}
	}

	// vs bottom
	int location = a_piece.y + a_piece.length;

	if (location >= BOARD_HEIGHT)
	{
		int tempnum = (a_piece.length - 1) - (location - BOARD_HEIGHT);

		for (int i = 0; i < a_piece.length; i++)
		{
			if (temp[i][tempnum] == 1)
			{
				return false;
			}
		}
	}

	// check temp array vs other pieces in the way
	for (int i = a_piece.x, k = 0; i < size; i++, k++)
	{
		for (int j = a_piece.y, n = 0; j < size; j++, n++)
		{
			if (_board[i][j] == 1 && temp[k][n] == 1)
			{
				return false;
			}
		}
	}

	// clean up the temp array and delete it
	for (int i = 0; i < a_piece.length; i++)
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
	int size = a_piece.length + a_piece.x;

	// if we are going outside of the bounds of the board...
	if (size >= BOARD_WIDTH)
	{
		for (int i = 0; i < a_piece.length; i++)
		{
//			std::cout << std::endl << "blah " << a_piece.length - 1 << std::endl;
			if (a_piece.shape[a_piece.length - 1 - (size - BOARD_WIDTH)][i] == 1)
			{
				return false;
			}
		}

//		std::cout << std::endl;
	}

	// now loop through and see if there are any pieces in the way
	for (int i = a_piece.x + 1, k = 0; k < a_piece.length; i++, k++)
	{	
		for (int j = a_piece.y + 1, q = 0; q < a_piece.length; j++, q++)
		{
			//std::cout << a_piece.shape[q][k];
			if (a_piece.shape[q][k] == 1 && _board[j][i] == 1)
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
	int location = a_piece.x - 1;

	// if we are going outside of the bounds of the board...
	if (location < 0)
	{
		for (int i = 0; i < a_piece.length; i++)
		{
			std::cout << "shape[" << abs(a_piece.x) << "][" << i << "] = " << a_piece.shape[abs(a_piece.x)][i] << std::endl;
			if (a_piece.shape[abs(a_piece.x)][i] == 1)
			{
				return false;
			}
		}
		std::cout << std::endl;
	}

	// now loop through and see if there are any pieces in the way
	for (int i = a_piece.x - 1, k = 0; k < a_piece.length; i++, k++)
	{	
		for (int j = a_piece.y - 1, q = 0; q < a_piece.length; j++, q++)
		{
//			std::cout << a_piece.shape[q][k];
			if (a_piece.shape[q][k] == 1 && _board[j][i] == 1)
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
	int location = a_piece.y + a_piece.length + 1;

	// if we are going outside of the bounds of the board...
	if (location >= BOARD_HEIGHT)
	{
		int tempnum = (a_piece.length - 1) - (location - BOARD_HEIGHT);

		for (int i = 0; i < a_piece.length; i++)
		{
			std::cout << "shape[" << i << "][" << tempnum << "] = " << a_piece.shape[i][tempnum] << std::endl;
			if (a_piece.shape[i][tempnum] == 1)
			{
				return false;
			}
		}
		std::cout << std::endl;
	}

	// now loop through and see if there are any pieces in the way
	for (int i = a_piece.x - 1, k = 0; k < a_piece.length; i++, k++)
	{	
		for (int j = a_piece.y - 1, q = 0; q < a_piece.length; j++, q++)
		{
			//std::cout << a_piece.shape[q][k];
			if (a_piece.shape[q][k] == 1 && _board[j][i] == 1)
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
					currentPiece.x++;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				//_blockSprite.move(-32.f, 0.f);
				if (canMoveLeft(currentPiece))
				{
					currentPiece.x--;
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				currentPiece.y--;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				//_blockSprite.move(0.f, 32.f);
				//MovePiece(currentPiece);

				if (canMoveDown(currentPiece))
				{
					currentPiece.y++;
				}

				std::cout << currentPiece.x << " " << currentPiece.y << std::endl;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (canRotate(currentPiece))
				{
					RotatePiece(currentPiece);
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