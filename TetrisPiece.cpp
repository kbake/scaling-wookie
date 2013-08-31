#include "stdafx.h"
#include "TetrisPiece.h"


TetrisPiece::TetrisPiece(void) :
	coords(0,0),
	length(0)
{
}

TetrisPiece::TetrisPiece(const TetrisPiece& tp)
{
	if (this != &tp)
	{
		coords = tp.GetCoords();
		length = tp.GetLength();
		texture = tp.GetTexture();

		initializeShape();

		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				shape[i][j] = tp.GetShape()[i][j];
			}
		}
	}
}

TetrisPiece& TetrisPiece::operator=(const TetrisPiece& tp)
{
	if (this != &tp)
	{
		coords = tp.GetCoords();
		length = tp.GetLength();
		texture = tp.GetTexture();

		initializeShape();

		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				shape[i][j] = tp.GetShape()[i][j];
			}
		}
	}

	return *this;
}

TetrisPiece::~TetrisPiece(void)
{
	if (shape)
	{
		for (int i = 0; i < length; i++)
		{
			delete [] shape[i];
			shape[i] = NULL;
		}

		delete [] shape;
		shape = NULL;
	}
}

sf::Vector2i TetrisPiece::GetCoords() const
{
	return coords;
}

int TetrisPiece::GetLength() const
{
	return length;
}

int** TetrisPiece::GetShape() const
{
	return shape;
}

sf::Texture TetrisPiece::GetTexture() const
{
	return texture;
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

void TetrisPiece::Rotate()
{
	int size = length;
	int** temp = new int*[size];
	std::cout << "Before:" << std::endl;
	for (int k = 0; k < size; k++)
	{
		temp[k] = new int[size];
		for (int l = 0; l < size; l++)
		{
			std::cout << shape[l][k];
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
			temp[i][j] = shape[j][tempint];
		}
	}

	for (int iter = 0; iter < length; iter++)
	{
		delete [] shape[iter];	// delete each dynamically created int array
	}

	delete [] shape;	// delete the dynamically created int* array

	shape = &(*temp);

	std::cout << "After:" << std::endl;
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			std::cout << shape[j][i];
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
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