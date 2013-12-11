#pragma once
class SimpleScreen
{
public:
	SimpleScreen(void);
	~SimpleScreen(void);

	void SetTexture(sf::Texture&);

	void Update(double);
	void Draw(sf::RenderWindow&);

private:
	sf::Texture _texture;
	sf::Sprite _background;
};

