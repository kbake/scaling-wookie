#pragma once
class TetrisPiece
{
public:
	TetrisPiece(void);
	~TetrisPiece(void);

	sf::Vector2i GetCoords() const;
	int GetLength() const;
	int** GetShape();

	void SetTexture(sf::Texture&);
	void SetLength(int);
	void SetCoords(sf::Vector2i);
	void SetShape(int*);

	void Draw(sf::RenderWindow&);

private:
	void initializeShape();

	sf::Texture texture;
	sf::Vector2i coords;
	int length;
	int** shape;
};

