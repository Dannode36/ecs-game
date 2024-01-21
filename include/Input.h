#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>
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
    //Keyboard Data------------------------------------------------------------
    static InputButtonState keyStates[KeyCode::KeyCount];

    //Mouse Data---------------------------------------------------------------
    static InputButtonState mouseButtonStates[MouseButton::ButtonCount];
    static bool cursorInWindow; //Is the cursor in the area of the window

    //Window Data--------------------------------------------------------------
    static bool focused; //Is the window focused

public:
    static void Refresh();

    //Keyboard Getters---------------------------------------------------------

    static bool controlsInverted;
    static void UpdateKeyState(const sf::Event& keyEvent);
    static bool GetKey(KeyCode key);
    static bool GetKeyUp(KeyCode key);
    static bool GetKeyDown(KeyCode key);

    //Mouse Getters------------------------------------------------------------

    static void UpdateMouseState(const sf::Event& mouseButtonEvent);
    static bool GetMouseButton(MouseButton key);
    static bool GetMouseButtonUp(MouseButton key);
    static bool GetMouseButtonDown(MouseButton key);
    static sf::Vector2i GetMousePosition();
    static sf::Vector2f GetMousePosition(sf::View view);
};
