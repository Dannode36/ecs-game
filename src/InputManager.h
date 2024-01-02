#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

typedef sf::Keyboard::Key KeyCode;

struct KeyState {
	bool pressed;
	bool up;
	bool down;
};

class InputManager
{
private:
	KeyState keyStates[KeyCode::KeyCount];

public:
	void Clear();
	void UpdateKeyState(const sf::Event& keyEvent);
	bool GetKey(KeyCode key) const;
	bool GetKeyUp(KeyCode key) const;
	bool GetKeyDown(KeyCode key) const;
};
