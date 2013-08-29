#include "stdafx.h"
#include "TetrisPiece.h"


TetrisPiece::TetrisPiece(void) :
	coords(0,0),
	length(0)
{
}


TetrisPiece::~TetrisPiece(void)
{
}

sf::Vector2i TetrisPiece::GetCoords() const
{
	return coords;
}

int TetrisPiece::GetLength() const
{
	return length;
}

int** TetrisPiece::GetShape()
{
	return shape;
}

void TetrisPiece::SetTexture(sf::Texture& t)
{
	texture = t;
}

void TetrisPiece::SetLength(int len)
{
	length = len;

	initializeShape();
}

void TetrisPiece::SetCoords(sf::Vector2i vec)
{
	coords.x += vec.x;
	coords.y += vec.y;
}

void TetrisPiece::SetShape(int* temp)
{
	shape = &(temp);
}

void TetrisPiece::initializeShape()
{
	shape = new int*[length];

	for (int i = 0; i < length; i++)
	{
		shape[i] = new int[length];
		for (int j = 0; j < length; j++)
		{
			shape[i][j] = 0;
		}
	}
}

void TetrisPiece::Draw(sf::RenderWindow& renderWindow)
{
	sf::Sprite* temp;

	for (int x = 0; x < length; x++)
		{
			for (int y = 0; y < length; y++)
			{
				if (shape[x][y] != 0)
				{
					temp = new sf::Sprite();
					temp->setTexture(texture);
					temp->setPosition(32.f * x + (coords.x * 32.f), 32.f * y + (coords.y * 32.f));
					temp->setColor(sf::Color(0, 255, 0));

					renderWindow.draw(*temp);

					delete temp;
					temp = NULL;
				}
			}
		}
}