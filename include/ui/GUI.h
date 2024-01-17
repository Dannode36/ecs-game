#pragma once
#include "ui/GuiElement.h"
#include <map>
#include "Button.h"

class GUI : sf::Drawable
{
private:
	std::map<std::string, std::unique_ptr<IGuiElement>> elements;

public:
	template<typename T>
	inline void add(const std::string id, T* button) {
		elements.emplace(id, button);
	}

	template<typename T>
	inline T& get(const std::string& id) {
		return static_cast<T&>(*elements[id]);
	}

	inline void clear() {
		elements.clear();
	}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
