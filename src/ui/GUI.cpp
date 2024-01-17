#include "ui/GUI.h"

void GUI::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto& element : elements)
	{
		target.draw(*element.second);
	}
}
