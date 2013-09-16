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
	const sf::Color& GetColor() const;

	void SetTexture(sf::Texture&);
	void SetLength(int);
	void SetCoords(sf::Vector2i);
	void SetColor(sf::Color);

	void Rotate();
	void IncrementCoords(sf::Vector2i);
	
	void Update(double);
	void Draw(sf::RenderWindow&);

private:
	void initializeShape();

	sf::Texture texture;
	sf::Vector2i coords;
	sf::Color color;

	std::vector<sf::Sprite> _sprites;

	int length;
	int** shape;
};

