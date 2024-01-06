#pragma once
#include <functional>
#include <vector>

template<typename T>
class Event
{
    std::vector<std::function<void(T&)>> m_EventHandlers;
public:
    inline void addListener(std::function<void(T&)> handler) {
        m_EventHandlers.push_back(handler);
    }

    inline void removeListener(std::function<void(T&)> handler) {
        auto it = std::find(m_EventHandlers.begin(), m_EventHandlers.end(), handler);
        if (it != m_EventHandlers.end()) {
            m_EventHandlers.erase(it);
        }
    }

    inline virtual void fire(T& args) {
        for (auto& handler : m_EventHandlers)
        {
            handler(args);
        }
    }
};
