#include "stdafx.h"
#include "PreviewBox.h"
#include "TetrisPiece.h"


PreviewBox::PreviewBox(void) :
	_location(sf::Vector2i()),
	_size(sf::Vector2i())
{
	_box.setColor(sf::Color());
}


PreviewBox::~PreviewBox(void)
{
}

void PreviewBox::SetPiece(TetrisPiece& a_piece)
{
	_nextPiece = a_piece;

	_nextPiece.SetCoords(sf::Vector2i(17, 2));

	std::cout << _nextPiece.GetCoords().x << ", " << _nextPiece.GetCoords().y << std::endl;
}

void PreviewBox::SetTexture(sf::Texture& texture)
{
	_box.setTexture(texture);
}

void PreviewBox::SetLocation(sf::Vector2i loc)
{
	_location = loc;
	_box.setPosition(_location.x, _location.y);
}

void PreviewBox::SetSize(sf::Vector2i size)
{
	_size = size;
	_box.setScale(_size.x, _size.y);
}

void PreviewBox::Draw(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(_box);

	_nextPiece.Draw(renderWindow);
}