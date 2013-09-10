#include "stdafx.h"
#include "ScoreBoard.h"


ScoreBoard::ScoreBoard(void) :
	_score(0),
	_position(0, 0),
	_size(0, 0)
{
}

ScoreBoard::ScoreBoard(sf::Vector2f pos, sf::Vector2f size) :
	_score(0),
	_position(pos),
	_size(size)
{
	_background.setPosition(_position);
	_background.setScale(_size);
	_background.setColor(sf::Color::Black);
}

ScoreBoard::~ScoreBoard(void)
{
}

int ScoreBoard::GetScore() const
{
	return _score;
}

const sf::Font& ScoreBoard::GetFont() const
{
	return _font;
}

const sf::Text& ScoreBoard::GetText() const
{
	return _text;
}

sf::Vector2f ScoreBoard::GetPosition() const
{
	return _position;
}

sf::Vector2f ScoreBoard::GetSize() const
{
	return _size;
}

void ScoreBoard::SetScore(int score)
{
	_score += score;
	
	_text.setString(std::to_string(_score));
}

void ScoreBoard::SetFont(std::string fontLoc)
{
	_font.loadFromFile(fontLoc);
	
	_text.setFont(_font);
	_text.setCharacterSize(20);
	_text.setColor(sf::Color::Green);
	_text.setPosition(_position);
}

void ScoreBoard::SetText(std::string text)
{
	_text.setFont(_font);
	//_text.setString(text);
	_text.setCharacterSize(20);
	_text.setColor(sf::Color::Green);
}

void ScoreBoard::SetTexture(sf::Texture& texture)
{
	_texture = texture;

	_background.setTexture(_texture);
}

void ScoreBoard::SetPosition(sf::Vector2f pos)
{
	_position = pos;
}

void ScoreBoard::SetSize(sf::Vector2f size)
{
	_size = size;
}

void ScoreBoard::Draw(sf::RenderWindow& renderWindow)
{
	renderWindow.draw(_background);
	renderWindow.draw(_text);
}