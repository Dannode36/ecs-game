#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>
#include <vector>

typedef sf::Keyboard::Key KeyCode;
typedef sf::Mouse::Button MouseButton;
typedef sf::Joystick Joystick;

struct ButtonState {
    bool pressed;
    bool up;
    bool down;
};

class Input
{
public:
    friend class Application;
    static bool controlsInverted;
private:
    static bool any;
    static bool anyDown;

    //Keyboard Data------------------------------------------------------------
    static ButtonState keyStates[KeyCode::KeyCount]; //Array containing the state of all supported keys
    static std::string text;

    //Mouse Data---------------------------------------------------------------
    static ButtonState mouseButtonStates[MouseButton::ButtonCount]; //Array containing the state of all mouse buttons
    static bool cursorInWindow; //Is the cursor in the area of the window

    //Controller Data----------------------------------------------------------
    static ButtonState joystickButtonStates[Joystick::Count][Joystick::ButtonCount]; //2D Array containing the state all joystick buttons
    static float joystickAxisValues[Joystick::Count][Joystick::AxisCount]; //2D Array containing the state all joystick buttons

    //Window Data--------------------------------------------------------------
    static bool focused; //Is the window focused

public:
    static bool Any(); //Is any key or mouse button pressed currently?
    static bool AnyDown(); //Was any key or mouse button pressed this frame

    //Keyboard Getters---------------------------------------------------------

    static void UpdateKeyState(const sf::Event& keyEvent);
    static bool GetKey(KeyCode key);
    static bool GetKeyUp(KeyCode key);
    static bool GetKeyDown(KeyCode key);
    static std::string GetText();

    //Mouse Getters------------------------------------------------------------

    static void UpdateMouseState(const sf::Event& mouseButtonEvent);
    static bool GetMouseButton(MouseButton key);
    static bool GetMouseButtonUp(MouseButton key);
    static bool GetMouseButtonDown(MouseButton key);
    static sf::Vector2i GetMousePosition();
private:
    static void Refresh();
    static void Update(const sf::Event& event);
};
