#pragma once
#include <functional>
#include <vector>

template<typename... Ps>
class Event
{
    std::vector<std::function<void(Ps...)>> m_EventHandlers;
public:
    void addListener(std::function<void(Ps...)> handler) {
        m_EventHandlers.push_back(handler);
    }

    void removeListener(std::function<void(Ps...)> handler) {
        auto it = std::find(m_EventHandlers.begin(), m_EventHandlers.end(), handler);
        if (it != m_EventHandlers.end()) {
            m_EventHandlers.erase(it);
        }
    }

    void clear() {
        m_EventHandlers.clear();
    }

    virtual void fire(Ps... args) {
        for (auto& handler : m_EventHandlers)
        {
            handler(args...);
        }
    }
};
