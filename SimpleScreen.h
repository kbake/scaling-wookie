#pragma once
class SimpleScreen
{
public:
	SimpleScreen(void);
	~SimpleScreen(void);

	void Update(double);
	void Draw(sf::RenderWindow&);

private:
	sf::Texture _texture;
	sf::Sprite _background;
};

