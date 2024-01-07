#pragma once
#include <vector>
#include <string>
#include <interfaces/IState.h>

/// Provides game state manager class for managing game states
class StateManager
{
private:
    /// Pointer to the App class for error handling and logging
    IApplication* m_App;
    /// Stack to store the current and previously active states
    std::vector<IState*>  m_Stack;
    std::vector<IState*>  m_Dead;

private:
    // StateManager copy constructor is undefined/private because we do not allow copies of our class 
    StateManager(const StateManager&);
    //Our assignment operator is undefined/private because we do not allow copies of our class
    StateManager& operator=(const StateManager&);

public:
    StateManager();
    virtual ~StateManager();

    void RegisterApp(IApplication* theApp);
    bool IsEmpty();

    void AddActiveState(IState* theState);
    void AddInactiveState(IState* theState);
    IState* GetActiveState();
    void InactivateActiveState();
    void DropActiveState();
    void ResetActiveState();
    void RemoveActiveState();
    void SetActiveState(std::string theStateID);
    void Cleanup();
};
