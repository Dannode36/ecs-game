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
        IState* state = m_Stack.back();
        m_Stack.pop_back();

        state->Pause();
        state->Unload();
        state->Cleanup();
        delete state;
    }

    if (!m_Dead.empty()) {
        IState* anState = m_Dead.back();
        assert(NULL != anState && "StateManager::Dispose() invalid dropped state pointer");

        // Pop the dead state off the stack
        m_Dead.pop_back();

        anState->Unload();
        anState->Cleanup();
        delete anState;
    }
}

void StateManager::RegisterApp(IApplication* app) {
    // Check that our pointer is good
    assert(NULL != app && "StateManager::RegisterApp() app pointer provided is bad");
    assert(NULL == m_App && "StateManager::RegisterApp() app pointer was already registered");

    m_App = app;
}

bool StateManager::IsEmpty() {
    return m_Stack.empty();
}

void StateManager::AddActiveState(IState* theState) {
    // Check that they didn't provide a bad pointer
    assert(NULL != theState && "StateManager::AddActiveState() received a bad pointer");

    // Log the adding of each state
    std::cout << "StateManager::AddActiveState(" << theState->GetID() << ")\n";

    // Is there a state currently running? then Pause it
    if(!m_Stack.empty()) {
        // Pause the currently running state since we are changing the
        // currently active state to the one provided
        m_Stack.back()->Pause();
    }

    // Add the active state
    m_Stack.push_back(theState);

    // Initialize the new active state
    m_Stack.back()->Load();
}

void StateManager::AddInactiveState(IState* theState) {
    // Check that they didn't provide a bad pointer
    assert(NULL != theState && "StateManager::AddInactiveState() received a bad pointer");

    // Log the adding of each state
    std::cout << "StateManager::AddInactiveState(" << theState->GetID() << ")\n";

    // Add the inactive state to the bottom of the stack
    m_Stack.insert(m_Stack.begin(), theState);
}

IState* StateManager::GetActiveState() {
    return m_Stack.back();
}

void StateManager::InactivateActiveState() {

    if(!m_Stack.empty()) {
        // Retrieve the currently active state
        IState* activeState = m_Stack.back();

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
    if(!m_Stack.empty())
    {
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

void StateManager::DropActiveState() {
    // Is there no currently active state to drop?
    if(!m_Stack.empty()) {
        IState* activeState = m_Stack.back();
        std::cout << "StateManager::DropActiveState(" << activeState->GetID() << ")\n";

        activeState->Pause();
        activeState->Unload();

        m_Stack.pop_back();
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
            m_Stack.back()->Resume();
        }
        else {
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
        IState* anState = m_Stack.back();

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

void StateManager::RemoveActiveState() {
    if(!m_Stack.empty()) {
        // Retrieve the currently active state
        IState* anState = m_Stack.back();

        // Log the removing of an active state
        std::cout << "StateManager::RemoveActiveState(" << anState->GetID() << ")\n";

        // Pause the currently active state
        anState->Pause();
 
        // Deinitialize the currently active state before we pop it off the stack
        anState->Unload();

        // Pop the currently active state off the stack
        m_Stack.pop_back();

        // Move this state to our dropped stack
        m_Dead.push_back(anState);
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

void StateManager::SetActiveState(std::string stateID)
{
    auto it = std::find_if(m_Stack.begin(), m_Stack.end(),
        [&](const IState* state) -> bool {
            return state->GetID() == stateID;
        });

    if (it != m_Stack.end()) {
        std::cout << "StateManager::SetActiveState(" << (*it)->GetID() << ")\n";

        m_Stack.erase(it);

        if (!m_Stack.empty()) {
            m_Stack.back()->Pause();
        }

        m_Stack.push_back(*it);

        // Has this state ever been loaded?
        if (m_Stack.back()->IsLoaded()) {
            m_Stack.back()->Resume();
        }
        else {
            m_Stack.back()->Load();
        }
    }
}

void StateManager::Cleanup() {
    if(!m_Dead.empty()) {
        IState* anState = m_Dead.back();
        assert(NULL != anState && "StateManager::Dispose() invalid dropped state pointer");

        // Pop the dead state off the stack
        m_Dead.pop_back();

        anState->Unload();
        anState->Cleanup();
        delete anState;
    }

    // Make sure we still have an active state
    if(NULL == m_Stack.back()) {
        m_App->Stop(StatusAppOK);
    }
}
