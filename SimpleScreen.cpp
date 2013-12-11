#include "stdafx.h"
#include "SimpleScreen.h"


SimpleScreen::SimpleScreen(void)
{
	_texture.loadFromFile("images/titlescreen.png");
	_background.setTexture(_texture);
}


SimpleScreen::~SimpleScreen(void)
{
}

void SimpleScreen::Update(double deltaTime)
{
}

void SimpleScreen::Draw(sf::RenderWindow& rw)
{
	rw.draw(_background);
}