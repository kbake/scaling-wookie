#include "stdafx.h"
#include "TetrisGame.h"
#include "TetrisBoard.h"
#include "TetrisPiece.h"
#include "PreviewBox.h"


TetrisGame::TetrisGame(void) :
	_gameState(GameState::Playing),
	_blockState(BlockState::Starting)
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
}

void TetrisGame::Start()
{
	_mainWindow.create(sf::VideoMode(800, 600), "Tetris Clone!");

	_boardLocation = sf::Vector2i(0, 0);

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

	currentPiece = new TetrisPiece(_pieces[rand() % 6]);
	nextPiece = new TetrisPiece(_pieces[rand() % 6]);

	_previewBox = new PreviewBox();
	_previewBox->SetLocation(sf::Vector2i(500, 20));
	_previewBox->SetSize(sf::Vector2i(6, 5));
	_previewBox->SetTexture(_blockTexture);
	_previewBox->SetPiece(*nextPiece);

	board.SetTexture(_blockTexture);

	while (!IsExiting())
	{
		GameLoop();
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
//			std::cout << "shape[" << i << "][" << tempnum << "] = " << a_piece.GetShape()[i][tempnum] << std::endl;
			if (a_piece.GetShape()[i][tempnum] == 1)
			{
				return false;
			}
		}
//		std::cout << std::endl;
	}

	// now loop through and see if there are any pieces in the way
	for (int i = a_piece.GetCoords().x, k = 0; k < a_piece.GetLength(); i++, k++)
	{	
		for (int j = a_piece.GetCoords().y + 1, q = 0; q < a_piece.GetLength(); j++, q++)
		{
			if (i < 0) i = 0;
			else if (i > board.GetBoardWidth() - 1) i = board.GetBoardWidth() - 1;
			
			if (j < 0) j = 0;
			else if (j > board.GetBoardHeight() - 1) j = board.GetBoardHeight() - 1;
			
			//std::cout << a_piece.GetShape()[k][q];
			std::cout << board.board[i][j];
			if (a_piece.GetShape()[k][q] == 1 && board.board[i][j] == 1)
			{
				return false;
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	return true;
}

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
		currentPiece->Draw(_mainWindow);
		_previewBox->Draw(_mainWindow);

		_mainWindow.display();

		if (board.isFull())	// check if any pieces are at the top of the board
		{
			_gameState = TetrisGame::Exiting;
		}

		// temp for tempness
		std::vector<int> temp_nums;

		for (int i = 0; i < board.GetBoardHeight(); i++)	// check if any rows are completed
		{
			//std::cout << "row: " << i << " = " << board.CheckRow(i) << std::endl;
			int blah = board.CheckRow(i);

			if (blah != -1)
			{
				temp_nums.push_back(blah);
			}
		}

		if (temp_nums.size() > 0)
		{
			for (int i = 0; i < temp_nums.size(); i++)		// temp delete loop
			{
				board.DeleteRow(temp_nums[i]);
				board.MoveRows(temp_nums[i]);
			}

			temp_nums.clear();
		}

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
				if (canMoveRight(*currentPiece)) 
				{
					currentPiece->IncrementCoords(sf::Vector2i(1, 0));
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				//_blockSprite.move(-32.f, 0.f);
				if (canMoveLeft(*currentPiece))
				{
					currentPiece->IncrementCoords(sf::Vector2i(-1, 0));
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				currentPiece->IncrementCoords(sf::Vector2i(0, -1));
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				if (canMoveDown(*currentPiece))
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
				if (canRotate(*currentPiece))
				{
					currentPiece->Rotate();
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