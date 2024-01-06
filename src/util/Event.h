#pragma once
#include <functional>
#include <vector>

class EventArgs
{
public:
    void* m_object;
public:
    EventArgs(void* obj)
    {
        m_object = obj;
    }
};

template<typename T>
class Event
{
    std::vector <std::function<void(T&)> m_EventHandlers;

public:
    void addListener(std::function<void(T&)> handler) {
        m_EventHandlers.push_back(handler)
    }

    void removeListener(std::function<void(T&)> handler) {
        // etc etc
    }

    virtual void fire(EventArg& args) {
        for (auto& handler : m_EventHandlers)
        {
            handler(args);
        }
    }
};
