#pragma once
class TetrisPiece
{
public:
	TetrisPiece(void);
	~TetrisPiece(void);

	sf::Vector2i GetCoords() const;
	int GetLength() const;

	void SetTexture(sf::Texture&);

	void Draw(sf::RenderWindow&);

private:
	sf::Texture texture;
	sf::Vector2i coords;
	int length;
	int** shape;
};

