#include "Input.h"

//Static initialization

bool Input::controlsInverted = false;
Event<unsigned int> Input::joystickConnectedEvent;
Event<unsigned int> Input::joystickDisconnectedEvent;

bool Input::any = false;
bool Input::anyDown = false;

ButtonState Input::keyStates[KeyCode::KeyCount];
std::string Input::text = std::string();

ButtonState Input::mouseButtonStates[MouseButton::ButtonCount];

ButtonState Input::joyBtnStates[Joystick::Count][Joystick::ButtonCount];
bool Input::joyConnectionFlags[Joystick::Count];

bool Input::cursorInWindow = false;
bool Input::focused = false;

static inline constexpr bool isKeyboardEvent(sf::Event::EventType type) {
    return type == sf::Event::KeyPressed 
        || type == sf::Event::KeyReleased;
}

static inline constexpr bool isMouseEvent(sf::Event::EventType type) {
    return type == sf::Event::MouseButtonPressed
        || type == sf::Event::MouseButtonReleased;
}

static inline constexpr bool isJoystickEvent(sf::Event::EventType type) {
    return type == sf::Event::JoystickButtonPressed
        || type == sf::Event::JoystickButtonReleased
        || type == sf::Event::JoystickConnected
        || type == sf::Event::JoystickDisconnected;
}

void Input::Update(const sf::Event& event) {
    if (isKeyboardEvent(event.type)) {
        UpdateKeyState(event);
    }
    else if (isMouseEvent(event.type)) {
        UpdateMouseState(event);
    }
    else if (isJoystickEvent(event.type)) {
        UpdateJoystickState(event);
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

    //Joystick shtuff
    for (size_t id = 0; id < Joystick::Count; id++) {
        //If joystick is connected
        if (joyConnectionFlags[id]) {
            for (size_t btn = 0; btn < Joystick::Count; btn++) {
                joyBtnStates[id][btn].up = false;
                joyBtnStates[id][btn].down = false;

                if (joyBtnStates[id][btn].pressed) {
                    any = true;
                }
            }
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
        any = true;
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
        any = true;
        anyDown = true;
    }
    else if (mbEvent.type == sf::Event::MouseButtonReleased) {
        mouseButtonStates[mbEvent.mouseButton.button].pressed = false;
        mouseButtonStates[mbEvent.mouseButton.button].up = true;
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

sf::Vector2i Input::GetMousePosition() {
    return sf::Mouse::getPosition();
}

//Controller---------------------------------------------------------------

void Input::UpdateJoystickState(const sf::Event& event) {
    auto& joyBtnEvent = event.joystickButton;
    if (event.type == sf::Event::JoystickButtonPressed) {
        joyBtnStates[joyBtnEvent.joystickId][joyBtnEvent.button].pressed = true;
        joyBtnStates[joyBtnEvent.joystickId][joyBtnEvent.button].down = true;
        any = true;
        anyDown = true;
    }
    else if (event.type == sf::Event::JoystickButtonReleased) {
        joyBtnStates[joyBtnEvent.joystickId][joyBtnEvent.button].pressed = false;
        joyBtnStates[joyBtnEvent.joystickId][joyBtnEvent.button].up = true;
    }
    else if (event.type == sf::Event::JoystickConnected) {
        joyConnectionFlags[event.joystickConnect.joystickId] = true;
        joystickConnectedEvent.fire(event.joystickConnect.joystickId);
    }
    else if (event.type == sf::Event::JoystickDisconnected) {
        joyConnectionFlags[event.joystickConnect.joystickId] = false;
        joystickDisconnectedEvent.fire(event.joystickConnect.joystickId);

    }
}

bool Input::GetJoyButton(unsigned int id, unsigned int button) {
    return joyBtnStates[id][button].pressed;
}

bool Input::GetJoyButtonUp(unsigned int id, unsigned int button) {
    return joyBtnStates[id][button].up;
}

bool Input::GetJoyButtonDown(unsigned int id, unsigned int button) {
    return joyBtnStates[id][button].down;
}

float Input::GetAxis(unsigned int id, Joystick::Axis axis) {
    return Joystick::getAxisPosition(id, axis);
}
