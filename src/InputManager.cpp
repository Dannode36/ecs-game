#include "InputManager.h"

void InputManager::Clear()
{
	for (auto& key : keyStates)
	{
		key.up = false;
		key.down = false;
	}
}

void InputManager::UpdateKeyState(const sf::Event& keyEvent)
{
	if (keyEvent.type == sf::Event::KeyPressed) {
		keyStates[keyEvent.key.code].pressed = true;
		keyStates[keyEvent.key.code].up = true;
	}
	else if (keyEvent.type == sf::Event::KeyReleased) {
		keyStates[keyEvent.key.code].pressed = false;
		keyStates[keyEvent.key.code].down = true;
	}
}

bool InputManager::GetKey(KeyCode key) const
{
	return keyStates[key].pressed;
}

bool InputManager::GetKeyUp(KeyCode key) const
{
	return keyStates[key].up;
}

bool InputManager::GetKeyDown(KeyCode key) const
{
	return keyStates[key].down;
}
