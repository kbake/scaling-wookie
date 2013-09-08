#pragma once

#include "TetrisPiece.h"

class PreviewBox
{
public:
	PreviewBox(void);
	~PreviewBox(void);

	void SetPiece(TetrisPiece&);
	void SetTexture(sf::Texture&);
	void SetLocation(sf::Vector2i);
	void SetSize(sf::Vector2i);

	void Draw(sf::RenderWindow&);

private:
	void deletePiece();

	TetrisPiece _nextPiece;
	sf::Texture _texture;
	sf::Sprite _box;
	sf::Vector2i _location;
	sf::Vector2i _size;
};