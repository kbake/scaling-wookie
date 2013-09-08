#pragma once
class TetrisPiece
{
public:
	TetrisPiece(void);
	TetrisPiece(const TetrisPiece&);	// copy constructor, need to specify this due to shape being a doubly-indirected pointer
	TetrisPiece& operator=(const TetrisPiece&);	// overloading the = operator
	~TetrisPiece(void);

	sf::Vector2i GetCoords() const;
	int GetLength() const;
	int** GetShape() const;
	const sf::Texture& GetTexture() const;

	void SetTexture(sf::Texture&);
	void SetLength(int);
	void SetCoords(sf::Vector2i);

	void Rotate();

	void IncrementCoords(sf::Vector2i);
	void Draw(sf::RenderWindow&);

private:
	void initializeShape();

	sf::Texture texture;
	sf::Vector2i coords;
	int length;
	int** shape;
};

