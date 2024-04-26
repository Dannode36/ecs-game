#include "ui/Rectangle.h"
#include <mathf.h>

void Fade::fade(int length, int endOpacity) {
	currentTime = 0;
	opacityStart = currentColour.a;
	opacityEnd = endOpacity;
	fadeLength = length;
}

void Fade::update(const sf::Time& dt) {
	if (currentTime < fadeLength) {
		currentColour.a = lerp(opacityStart, opacityEnd, currentTime / static_cast<float>(fadeLength)); //div by 0 error should never happen
		rect.setFillColor(currentColour);
		currentTime += dt.asMilliseconds(); //Progress the fade animation time. Move to start for an instant fade
	}
}

void Fade::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(rect);
}
