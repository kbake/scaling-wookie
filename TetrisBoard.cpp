#include "stdafx.h"
#include "TetrisBoard.h"
#include "TetrisPiece.h"


TetrisBoard::TetrisBoard(void)
{
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

void TetrisBoard::AddPiece(TetrisPiece& a_piece)
{
	int lengthX = a_piece.GetLength() + a_piece.GetCoords().x,
		lengthY = a_piece.GetLength() + a_piece.GetCoords().y;

	for (int i = a_piece.GetCoords().x; i < lengthX; i++)
	{
		for (int j = a_piece.GetCoords().y; j < lengthY; j++)
		{
			if (i < BOARD_WIDTH && j < BOARD_HEIGHT)
			{
				board[i][j] = 1;
			}
		}
	}
}

int TetrisBoard::CheckRow(int row) const
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		if (board[row][i] == 0)
		{
			return -1;
		}
	}

	return row;
}

void TetrisBoard::DeleteRow(int row)
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		board[row][i] = 0;
	}
}

void TetrisBoard::Draw(sf::RenderWindow& renderWindow)
{
	sf::Sprite* temp;

	for (int x = 0; x < BOARD_WIDTH; x++)
	{
		for (int y = 0; y < BOARD_HEIGHT; y++)
		{
			temp = new sf::Sprite();
			temp->setTexture(_texture);
			temp->setPosition(32.f * x, 32.f * y);

			if (board[x][y] != 0)
			{
				temp->setColor(sf::Color(15, 100, 200));
			}
			else
			{
				temp->setColor(sf::Color());
			}

			renderWindow.draw(*temp);
			
			delete temp;
			temp = NULL;
		}
	}
}