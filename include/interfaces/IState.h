#pragma once
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <types.h>

/// Provides the base class interface for all game states
class IState
{
private:
    const std::string mStateID; //The State ID
    bool mLoaded; //Boolean that indicates that Load has been called
    bool mPaused; //State is currently paused (not active)
    bool mCleanup; //State needs to be cleaned up at the end of the next game loop

private:
    IState(const IState&);
    IState& operator=(const IState&);// Intentionally undefined

protected:
    IApplication& app;

    /*
        \brief Dispose is responsible for performing any cleanup required
        before this State is removed.
    */
    virtual void Dispose() = 0;

public:
    IState(const std::string stateID, IApplication& app);
    virtual ~IState();

    const std::string GetID() const;
    bool IsLoaded() const;
    bool IsPaused() const;

    /*
        \brief Dispose will be called if mCleanup is true so Derived classes 
        should always call IState::Load() first before initializing their assets.
    */
    virtual void Load();

    /*
        \brief Reload resets this state when the StateManager::ResetActiveState()
        method is called
    */
    virtual void Reload() = 0;

    /*
        \brief Unload marks this state to be cleaned up
    */
    void Unload();

    //Pause the state
    virtual void Pause();

    //Resume the state
    virtual void Resume();

    /*
        \brief HandleEvent is responsible for handling input events for this
        State when it is the active State.
        @param[in] event to process from the App class Loop method
    */
    virtual void HandleEvent(sf::Event& event) = 0;

    /*
        \brief Update is responsible for handling all State fixed update needs for
        this State when it is the active State.
    */
    virtual void Update(sf::Time dt) = 0;

    /*
        \brief Draw is responsible for handling all Drawing needs for this State
        when it is the Active State.
    */
    virtual void Draw(sf::RenderWindow& target) = 0;

    /*
        \brief Cleanup is responsible for calling Dispose if this class has
        been flagged to be cleaned up after it completes the game loop.
    */
    void Cleanup();
};
