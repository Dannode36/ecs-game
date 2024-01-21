#include "Input.h"

bool Input::controlsInverted = false;
InputButtonState Input::keyStates[KeyCode::KeyCount];
InputButtonState Input::mouseButtonStates[MouseButton::ButtonCount];

void Input::Refresh() {
    for (auto& key : keyStates)
    {
        key.up = false;
        key.down = false;
    }
    for (auto& mouseButton : mouseButtonStates)
    {
        mouseButton.up = false;
        mouseButton.down = false;
    }
}

//Keyboard-----------------------------------------------------------------

void Input::UpdateKeyState(const sf::Event& keyEvent) {
    if (keyEvent.type == sf::Event::KeyPressed) {
        keyStates[keyEvent.key.code].pressed = true;
        keyStates[keyEvent.key.code].down = true;
    }
    else if (keyEvent.type == sf::Event::KeyReleased) {
        keyStates[keyEvent.key.code].pressed = false;
        keyStates[keyEvent.key.code].up = true;
    }
}
bool Input::GetKey(KeyCode key) {
    return keyStates[key].pressed;
}
bool Input::GetKeyUp(KeyCode key) {
    return keyStates[key].up;
}
bool Input::GetKeyDown(KeyCode key) {
    return keyStates[key].down;
}

//Mouse--------------------------------------------------------------------

void Input::UpdateMouseState(const sf::Event& mbEvent) {
    if (mbEvent.type == sf::Event::MouseButtonPressed) {
        mouseButtonStates[mbEvent.mouseButton.button].pressed = true;
        mouseButtonStates[mbEvent.mouseButton.button].down = true;
    }
    else if (mbEvent.type == sf::Event::MouseButtonReleased) {
        mouseButtonStates[mbEvent.mouseButton.button].pressed = false;
        mouseButtonStates[mbEvent.mouseButton.button].up = true;
    }

    if (mbEvent.type == sf::Event::MouseMoved) {
        mbEvent.mouseMove.
    }
}
bool Input::GetMouseButton(MouseButton mouseButton) {
    return mouseButtonStates[mouseButton].pressed;
}
bool Input::GetMouseButtonUp(MouseButton mouseButton) {
    return mouseButtonStates[mouseButton].up;
}
bool Input::GetMouseButtonDown(MouseButton mouseButton) {
    return mouseButtonStates[mouseButton].down;
}

sf::Vector2f Input::GetMousePosition(sf::View view)
{
    return sf::Mouse::;
}
