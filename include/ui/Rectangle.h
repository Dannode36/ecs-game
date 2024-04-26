#pragma once
#include "ui/Widget.h"
#include "SFML/Graphics.hpp"

class Fade : public Widget {
public:
	void fade(int milliseconds, int endOpacity = -1);
	void update(const sf::Time& dt);
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	sf::RectangleShape rect;
	sf::Color currentColour;
	int currentTime;
	int fadeLength;
	int opacityStart;
	int opacityEnd;
public:
	Fade(sf::Vector2f size = sf::Vector2f(FLT_MAX, FLT_MAX), sf::Color colour = sf::Color::Black) 
		: rect(size), currentTime(0), fadeLength(-1), opacityStart(0), opacityEnd(0)
	{
		colour.a = 0;
		currentColour = colour;
		rect.setFillColor(colour);
	}
};
