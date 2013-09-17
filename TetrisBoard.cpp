#include "stdafx.h"
#include "TetrisBoard.h"
#include "TetrisPiece.h"


TetrisBoard::TetrisBoard(void)
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			board[i][j] = 0;
			
			//_sprites[i * BOARD_HEIGHT + j] = new sf::Sprite();
			_sprites.push_back(sf::Sprite());
			_sprites[i * BOARD_HEIGHT + j].setColor(sf::Color::Black);
			_sprites[i * BOARD_HEIGHT + j].setPosition(32.f * i, 32.f * j);
		}
	}
}


TetrisBoard::~TetrisBoard(void)
{
}

int TetrisBoard::GetBoardWidth() const
{
	return BOARD_WIDTH;
}

int TetrisBoard::GetBoardHeight() const
{
	return BOARD_HEIGHT;
}

void TetrisBoard::SetTexture(sf::Texture& t)
{
	_texture = t;

	std::vector<sf::Sprite>::iterator it = _sprites.begin();
	std::vector<sf::Sprite>::iterator end = _sprites.end();

	while (it != end)
	{
		(*it).setTexture(_texture);

		it++;
	}
}

void TetrisBoard::AddPiece(TetrisPiece& a_piece)	// adds a piece to the board based on the pieces location and size and such
{
	int lengthX = a_piece.GetLength() + a_piece.GetCoords().x,
		lengthY = a_piece.GetLength() + a_piece.GetCoords().y;

	for (int i = a_piece.GetCoords().x, k = 0; i < lengthX; i++, k++)
	{
		for (int j = a_piece.GetCoords().y, n = 0; j < lengthY; j++, n++)
		{
			if (i < BOARD_WIDTH && j < BOARD_HEIGHT)
			{
				if (a_piece.GetShape()[k][n] == 1) 
				{
					board[i][j] = 1;

					_sprites[i * BOARD_HEIGHT + j].setColor(a_piece.GetColor());
				}
			}
		}
	}
}

bool TetrisBoard::isFull() const	// check if the top row has a piece in it...if so, game over man, game over
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		if (board[i][0] == 1)
		{
			return true;
		}
	}

	return false;
}

bool TetrisBoard::canRotate(TetrisPiece& a_piece) const
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

	if (size > BOARD_WIDTH)
	{
		for (int i = 0; i < a_piece.GetLength(); i++)
		{
			if (temp[a_piece.GetLength() - 1 - (size - BOARD_WIDTH)][i] == 1)
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

	if (location >= BOARD_HEIGHT)
	{
		int tempnum = (a_piece.GetLength() - 1) - (location - BOARD_HEIGHT);

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
			if (board[i][j] == 1 && temp[k][n] == 1)
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

bool TetrisBoard::canMoveRight(TetrisPiece& a_piece) const
{
	int size = a_piece.GetLength() + a_piece.GetCoords().x;

	// if we are going outside of the bounds of the board...
	if (size >= BOARD_WIDTH)
	{
		for (int i = 0; i < a_piece.GetLength(); i++)
		{
//			std::cout << std::endl << "blah " << a_piece.length - 1 << std::endl;
			if (a_piece.GetShape()[a_piece.GetLength() - 1 - (size - GetBoardWidth())][i] == 1)
			{
				std::cout << std::endl << "right: outside board boundaries" << std::endl;
				return false;
			}
		}

//		std::cout << std::endl;
	}

	// now loop through and see if there are any pieces in the way
	for (int i = a_piece.GetCoords().x + 1, k = 0; k < a_piece.GetLength(); i++, k++)
	{
		if (i > BOARD_WIDTH) continue;

		for (int j = a_piece.GetCoords().y, q = 0; q < a_piece.GetLength(); j++, q++)
		{
			if (j > BOARD_HEIGHT) continue;

			//std::cout << a_piece.GetShape()[k][q];
			//std::cout << board.board[i][j];
			if (a_piece.GetShape()[k][q] == 1 && board[i][j] == 1)
			{
				std::cout << std::endl << "right: piece in the way" << std::endl;
				return false;
			}
		}
		//std::cout << std::endl;
	}
	//std::cout << std::endl;

	return true;
}

bool TetrisBoard::canMoveLeft(TetrisPiece& a_piece) const
{
	int location = a_piece.GetCoords().x - 1;

	// if we are going outside of the bounds of the board...
	if (location < 0)
	{
		for (int i = 0; i < a_piece.GetLength(); i++)
		{
			//std::cout << "shape[" << abs(a_piece.GetCoords().x) << "][" << i << "] = " << a_piece.GetShape()[abs(a_piece.GetCoords().x)][i] << std::endl;
			if (a_piece.GetShape()[abs(a_piece.GetCoords().x)][i] == 1)
			{
				std::cout << std::endl << "left: outside board boundaries" << std::endl;
				return false;
			}
		}
		//std::cout << std::endl;
	}

	// now loop through and see if there are any pieces in the way
	for (int i = a_piece.GetCoords().x - 1, k = 0; k < a_piece.GetLength(); i++, k++)
	{
		if (i < 0) continue;

		for (int j = a_piece.GetCoords().y, q = 0; q < a_piece.GetLength(); j++, q++)
		{
			if (j < 0) continue;
//			std::cout << a_piece.shape[q][k];
			if (a_piece.GetShape()[k][q] == 1 && board[i][j] == 1)
			{
				std::cout << std::endl << "left: pieces in the way" << std::endl;
				return false;
			}
		}
//		std::cout << std::endl;
	}
//	std::cout << std::endl;

	return true;
}

bool TetrisBoard::canMoveDown(TetrisPiece& a_piece) const
{
	int location = a_piece.GetCoords().y + a_piece.GetLength() + 1;

	// if we are going outside of the bounds of the board...
	if (location >= BOARD_HEIGHT)
	{
		int tempnum = (a_piece.GetLength() - 1) - (location - BOARD_HEIGHT);

		for (int i = 0; i < a_piece.GetLength(); i++)
		{
//			std::cout << "shape[" << i << "][" << tempnum << "] = " << a_piece.GetShape()[i][tempnum] << std::endl;
			if (a_piece.GetShape()[i][tempnum] == 1)
			{
				std::cout << std::endl << "down: outside board boundaries" << std::endl;
				return false;
			}
		}
//		std::cout << std::endl;
	}

	// now loop through and see if there are any pieces in the way
	for (int i = a_piece.GetCoords().x, k = 0; k < a_piece.GetLength(); i++, k++)
	{
		if (i < 0) continue;
		else if (i > BOARD_WIDTH - 1) i = BOARD_WIDTH - 1;

		for (int j = a_piece.GetCoords().y + 1, q = 0; q < a_piece.GetLength(); j++, q++)
		{			
			if (j < 0) continue;
			else if (j > BOARD_HEIGHT - 1) j = BOARD_HEIGHT - 1;
			
			//std::cout << a_piece.GetShape()[k][q];
			//std::cout << board.board[i][j];
			if (a_piece.GetShape()[k][q] == 1 && board[i][j] == 1)
			{
				std::cout << std::endl << "down: pieces in the way" << std::endl;
				return false;
			}
		}
		//std::cout << std::endl;
	}
	//std::cout << std::endl;

	return true;
}

int TetrisBoard::CheckRow(int row) const	// checks a given row, returning the row's index if it is full
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
//		std::cout << "[" << i << "][" << row << "]=" << board[i][row] << std::endl;
		if (board[i][row] == 0)
		{
			return -1;
		}
	}
//	std::cout << std::endl;
	return row;
}

void TetrisBoard::DeleteRow(int row)		// deletes (changes to 0) a given row's contents
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		board[i][row] = 0;

		_sprites[i * BOARD_HEIGHT + row].setColor(sf::Color::Black);
	}
}

// move all rows above the given row
void TetrisBoard::MoveRows(int bottomRow)
{
	if (bottomRow != 0)	// ignore top row (just in case)
	{
		for (int i = bottomRow; i > 0; i--)	// this goes bottom-up (as opposed to top-down)
		{
			for (int j = 0; j < BOARD_WIDTH; j++)
			{
				if (board[j][i] != 0 && board[j][i+1] != 1)	// if the piece can move down
				{
					board[j][i+1] = board[j][i];
					board[j][i] = 0;

					_sprites[j * BOARD_HEIGHT + (i+1)].setColor(_sprites[j * BOARD_HEIGHT + i].getColor());
					_sprites[j * BOARD_HEIGHT + i].setColor(sf::Color::Black);
				}
			}
		}
	}
}

void TetrisBoard::Update(double deltaTime)
{
	// temp for tempness
	std::vector<int> temp_nums;

	for (int i = 0; i < BOARD_HEIGHT; i++)	// check if any rows are completed
	{
		//std::cout << "row: " << i << " = " << board.CheckRow(i) << std::endl;
		int blah = CheckRow(i);

		if (blah != -1)
		{
			temp_nums.push_back(blah);
		}
	}

	if (temp_nums.size() > 0)
	{
		for (int i = 0; i < temp_nums.size(); i++)		// temp delete loop
		{
			DeleteRow(temp_nums[i]);
			MoveRows(temp_nums[i]);
		}

		temp_nums.clear();
	}
}

void TetrisBoard::Draw(sf::RenderWindow& renderWindow)
{
	std::vector<sf::Sprite>::iterator it = _sprites.begin();
	std::vector<sf::Sprite>::iterator end = _sprites.end();

	while (it != end)
	{
		renderWindow.draw(*it);

		it++;
	}
}