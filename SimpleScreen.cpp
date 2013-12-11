#include "stdafx.h"
#include "SimpleScreen.h"


SimpleScreen::SimpleScreen(void)
{
}


SimpleScreen::~SimpleScreen(void)
{
}

void SimpleScreen::SetTexture(sf::Texture& texture)
{
	_texture = texture;

	_background.setTexture(_texture);
}

void SimpleScreen::Update(double deltaTime)
{
}

void SimpleScreen::Draw(sf::RenderWindow& rw)
{
	rw.draw(_background);
}