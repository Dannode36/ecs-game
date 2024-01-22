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
    std::vector<std::shared_ptr<IState>>  m_Stack;

private:
    // StateManager copy constructor is undefined/private because we do not allow copies of our class 
    StateManager(const StateManager&);
    //Our assignment operator is undefined/private because we do not allow copies of our class
    StateManager& operator=(const StateManager&);

public:
    StateManager();
    virtual ~StateManager();

    void RegisterApp(IApplication& theApp);
    bool IsEmpty();

    std::shared_ptr<IState> GetActiveState();
    void AddActiveState(std::shared_ptr<IState> state);
    void AddInactiveState(std::shared_ptr<IState> state);

    void SetActiveState(std::string theStateID);
    void InactivateActiveState();
    void DropActiveState();
    void ResetActiveState();
    void RemoveActiveState();

    //Cleans up unloaded states after gameloop completes
    void Cleanup();
};
