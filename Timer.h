#pragma once
class Timer
{
public:
	Timer(void);
	Timer(sf::Vector2f);	// location
	~Timer(void);

	const sf::Font& GetFont() const;
	const sf::Text& GetText() const;
	const sf::Texture& GetTexture() const;
	sf::Vector2f GetPosition() const;
	sf::Vector2f GetSize() const;
	
	void SetFont(std::string);
	void SetText(std::string);
	void SetTexture(sf::Texture&);
	void SetPosition(sf::Vector2f);
	void SetSize(sf::Vector2f);

	void Draw(sf::RenderWindow&);

private:
	sf::Font _font;
	sf::Text _text;
	sf::Texture _texture;
	sf::Sprite _background;
	sf::Vector2f _position;
	sf::Vector2f _size;

	void initialize();
};

