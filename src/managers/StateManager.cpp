#include "managers/StateManager.h"
#include <iostream>
#include <cassert>
#include <types.h>
#include "interfaces/IApplication.h"

StateManager::StateManager() : m_App(nullptr) {
    std::cout << "StateManager::ctor()\n";
}

StateManager::~StateManager() {
    std::cout << "StateManager::dtor()\n";

    // Drop all active states
    while(!m_Stack.empty())
    {
        // Retrieve the currently active state and unload then delete it
        auto& state = m_Stack.back();

        state->Pause();
        state->Unload();
        state->Cleanup();

        m_Stack.pop_back();
    }
}

void StateManager::RegisterApp(IApplication& app) {
    assert(NULL == m_App && "StateManager::RegisterApp() app pointer was already registered");

    m_App = &app;
}

bool StateManager::IsEmpty() {
    return m_Stack.empty();
}

void StateManager::AddActiveState(std::shared_ptr<IState> state) {
    // Log the adding of each state
    std::cout << "StateManager::AddActiveState(" << state->GetID() << ")\n";

    // Is there a state currently running? then Pause it
    if(!m_Stack.empty()) {
        // Pause the currently running state since we are changing the
        // currently active state to the one provided
        m_Stack.back()->Pause();
    }

    // Add the active state
    m_Stack.push_back(state);

    // Initialize the new active state
    state->Load();
}

void StateManager::AddInactiveState(std::shared_ptr<IState> state) {
    // Log the adding of each state
    std::cout << "StateManager::AddInactiveState(" << state->GetID() << ")\n";

    // Add the inactive state to the bottom of the stack
    m_Stack.insert(m_Stack.begin(), state);
}

std::shared_ptr<IState> StateManager::GetActiveState() {
    return m_Stack.back();
}

void StateManager::InactivateActiveState() {

    if(!m_Stack.empty()) {
        // Retrieve the currently active state
        auto& activeState = m_Stack.back();

        // Log the inactivating an active state
        std::cout << "StateManager::InactivateActiveState(" << activeState->GetID() << ")" << std::endl;

        // Pause the currently active state
        activeState->Pause();

        // Pop the currently active state off the stack
        m_Stack.pop_back();

        // Move this now inactive state to the absolute back of our stack
        m_Stack.insert(m_Stack.begin(), activeState);
    }
    else {
        m_App->Stop(StatusAppOK);
        return;
    }

    // Is there another state to activate? then call Resume to activate it
    if(!m_Stack.empty()) {
        // Has this state ever been initialized?
        if(m_Stack.back()->IsLoaded()) {
            // Resume the new active state
            m_Stack.back()->Resume();
        }
        else {
            // Initialize the new active state
            m_Stack.back()->Load();
        }
    }
    else {
        m_App->Stop(StatusAppOK);
    }
}

//Exits current state and adds it to the bottom of the stack
void StateManager::DropActiveState() {
    // Is there no currently active state to drop?
    if(!m_Stack.empty()) {
        auto& activeState = m_Stack.back();
        std::cout << "StateManager::DropActiveState(" << activeState->GetID() << ")\n";

        activeState->Pause();
        activeState->Unload();

        m_Stack.pop_back();
        m_Stack.insert(m_Stack.begin(), activeState);

        // Is there another state to activate? then call Resume to activate it
        if (!m_Stack.empty()) {
            // Has this state ever been initialized?
            if (m_Stack.back()->IsLoaded()) {
                m_Stack.back()->Resume();
            }
            else {
                m_Stack.back()->Load();
            }
            return; //New state loaded
        }
    }

    //No State
    m_App->Stop(StatusAppOK);
}

//Exits current state and removes it from the stack
void StateManager::RemoveActiveState() {
    if (!m_Stack.empty()) {
        // Retrieve the currently active state
        auto& anState = m_Stack.back();

        // Log the removing of an active state
        std::cout << "StateManager::RemoveActiveState(" << anState->GetID() << ")\n";

        // Pause the currently active state
        anState->Pause();

        // Deinitialize the currently active state before we pop it off the stack
        anState->Unload();

        // Pop the currently active state off the stack
        m_Stack.pop_back();
    }

    // Is there another state to activate? then call Resume to activate it
    if (!m_Stack.empty()) {
        // Has this state ever been initialized?
        if (m_Stack.back()->IsLoaded()) {
            // Resume the new active state
            m_Stack.back()->Resume();
        }
        else {
            // Initialize the new active state
            m_Stack.back()->Load();
        }
    }
    else {
        m_App->Stop(StatusAppOK);
    }
}

void StateManager::ResetActiveState() {
    // Is there no currently active state to reset?
    if(!m_Stack.empty()) {
        // Retrieve the currently active state
        auto& anState = m_Stack.back();

        // Log the resetting of an active state
        std::cout << "StateManager::ResetActiveState(" << anState->GetID() << ")\n";

        // Pause the currently active state
        anState->Pause();

        // Call the ReInit method to Reset the currently active state
        anState->Reload();

        // Resume the currently active state
        anState->Resume();

        // Don't keep pointers around we don't need anymore
        anState = NULL;
    }
    else {
        m_App->Stop(StatusAppOK);
    }
}

void StateManager::Cleanup() {
    for (auto& state : m_Stack) {
        state->Cleanup(); //TODO: optimize this crap
    }
}

void StateManager::SetActiveState(std::string stateID)
{
    auto it = std::find_if(m_Stack.begin(), m_Stack.end(),
        [&](const auto& state) -> bool {
            return state->GetID() == stateID;
        });

    if (it != m_Stack.end()) {
        auto state = *it;
        std::cout << "StateManager::SetActiveState(" << state->GetID() << ")\n";

        m_Stack.erase(it);

        if (!m_Stack.empty()) {
            m_Stack.back()->Pause();
        }

        m_Stack.push_back(state);

        // Has the new state ever been loaded?
        if (m_Stack.back()->IsLoaded()) {
            m_Stack.back()->Resume();
        }
        else {
            m_Stack.back()->Load();
        }
    }
    else {
        std::cout << "StateManager: The state \"" << stateID << "\" could not be found\n";
    }
}
