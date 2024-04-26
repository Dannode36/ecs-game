#include "Input.h"

bool Input::any = false;
bool Input::anyDown = false;
bool Input::controlsInverted = false;

InputButtonState Input::keyStates[KeyCode::KeyCount];
std::string Input::text = std::string();

InputButtonState Input::mouseButtonStates[MouseButton::ButtonCount];

bool Input::cursorInWindow = false;
bool Input::focused = false;

void Input::Update(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
        UpdateKeyState(event);
    }
    else if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased) {
        UpdateMouseState(event);
    }
    else if (event.type == sf::Event::TextEntered) {
        text += event.text.unicode;
    }
    else if (event.type == sf::Event::GainedFocus) {
        focused = true;
    }
    else if (event.type == sf::Event::LostFocus) {
        focused = false;
    }
    else if (event.type == sf::Event::MouseEntered) {
        cursorInWindow = true;
    }
    else if (event.type == sf::Event::MouseLeft) {
        cursorInWindow = false;
    }
}

void Input::Refresh() {
    any = false;
    anyDown = false;

    text.clear();

    for (auto& key : keyStates) {
        key.up = false;
        key.down = false;

        if (key.pressed) {
            any = true;
        }
    }
    for (auto& mouseButton : mouseButtonStates) {
        mouseButton.up = false;
        mouseButton.down = false;

        if (mouseButton.pressed) {
            any = true;
        }
    }
}

bool Input::Any() {
    return any;
}

bool Input::AnyDown() {
    return anyDown;
}

//Keyboard-----------------------------------------------------------------

void Input::UpdateKeyState(const sf::Event& keyEvent) {
    if (keyEvent.type == sf::Event::KeyPressed) {
        keyStates[keyEvent.key.code].pressed = true;
        keyStates[keyEvent.key.code].down = true;
        anyDown = true;
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

std::string Input::GetText() {
    return text;
}

//Mouse--------------------------------------------------------------------

void Input::UpdateMouseState(const sf::Event& mbEvent) {
    if (mbEvent.type == sf::Event::MouseButtonPressed) {
        mouseButtonStates[mbEvent.mouseButton.button].pressed = true;
        mouseButtonStates[mbEvent.mouseButton.button].down = true;
        anyDown = true;
    }
    else if (mbEvent.type == sf::Event::MouseButtonReleased) {
        mouseButtonStates[mbEvent.mouseButton.button].pressed = false;
        mouseButtonStates[mbEvent.mouseButton.button].up = true;
    }

    /*if (mbEvent.type == sf::Event::MouseMoved) {
        mbEvent.mouseMove.
    }*/
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

sf::Vector2i Input::GetMousePosition() {
    return sf::Mouse::getPosition();
}
