#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

typedef sf::Keyboard::Key KeyCode;
typedef sf::Mouse::Button MouseButton;

struct InputButtonState {
    bool pressed;
    bool up;
    bool down;
};

class Input
{
private:
    static InputButtonState keyStates[KeyCode::KeyCount];
    static InputButtonState mouseButtonStates[MouseButton::ButtonCount];
public:
    static void Refresh();

    //Keyboard-----------------------------------------------------------------

    static bool controlsInverted;
    static void UpdateKeyState(const sf::Event& keyEvent);
    static bool GetKey(KeyCode key);
    static bool GetKeyUp(KeyCode key);
    static bool GetKeyDown(KeyCode key);

    //Mouse--------------------------------------------------------------------

    static void UpdateMouseState(const sf::Event& mouseButtonEvent);
    static bool GetMouseButton(MouseButton key);
    static bool GetMouseButtonUp(MouseButton key);
    static bool GetMouseButtonDown(MouseButton key);
};
