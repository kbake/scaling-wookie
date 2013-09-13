#include "stdafx.h"
#include "Timer.h"


Timer::Timer(void) :
	_position(0, 0)
{
}

Timer::Timer(sf::Vector2f pos)
{
	_position = pos;
}

Timer::~Timer(void)
{
}

const sf::Font& Timer::GetFont() const
{
	return _font;
}

const sf::Text& Timer::GetText() const
{
	return _text;
}

const sf::Texture& Timer::GetTexture() const
{
	return _texture;
}

sf::Vector2f Timer::GetPosition() const
{
	return _position;
}

sf::Vector2f Timer::GetSize() const
{
	return _size;
}

void Timer::SetFont(std::string fontLoc)
{
	_font.loadFromFile(fontLoc);
}

void Timer::SetText(std::string text)
{
	_text.setString(text);
}

void Timer::SetTexture(sf::Texture& texture)
{
	_texture = texture;
}

void Timer::SetPosition(sf::Vector2f position)
{
	_position = position;
}

void Timer::SetSize(sf::Vector2f size)
{
	_size = size;

	initialize();
}

void Timer::initialize()
{
	_background.setTexture(_texture);
	_background.setColor(sf::Color::Black);
	_background.setScale(_size);
	_background.setPosition(_position);

	_text.setFont(_font);
	_text.setCharacterSize(20);
	_text.setColor(sf::Color::White);
	_text.setPosition(_position);
}

void Timer::Draw(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(_background);
	renderWindow.draw(_text);
}