#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "../Application.h"

/// Provides the base class interface for all game states
class IState
{
public:
    /**
        * IState constructor
        * @param[in] theStateID to use for this State object
        * @param[in] theApp is the address to the IApp derived class
        */
    IState(const std::string theStateID, Application& theApp);

    /**
        IState deconstructor
        */
    virtual ~IState();

    /**
        * GetID will return the ID used to identify this State object
        * @return std::string is the ID for this State object
        */
    const std::string GetID() const;

    /**
        * DoInit is responsible for initializing this State.  HandleCleanup will
        * be called if mCleanup is true so Derived classes should always call
        * IState::DoInit() first before initializing their assets.
        */
    virtual void DoInit();

    /**
        * ReInit is responsible for Reseting this state when the
        * StateManager::ResetActiveState() method is called.  This way a Game
        * State can be restarted without unloading and reloading the game assets
        */
    virtual void ReInit() = 0;

    /**
        * DeInit is responsible for marking this state to be cleaned up
        */
    void DeInit();

    /**
        * IsInitComplete will return true if the DoInit method has been called
        * for this state.
        * @return true if DoInit has been called, false otherwise or if DeInit
        *         was called
        */
    bool IsInitComplete() const;

    /**
        * IsPaused will return true if this state is not the currently active
        * state.
        * @return true if state is not current active state, false otherwise
        */
    bool IsPaused() const;

    /**
        * Pause is responsible for pausing this State since the Application
        * may have lost focus or another State has become activate.
        */
    virtual void Pause();

    /**
        * Resume is responsible for resuming this State since the Application
        * may have gained focus or the previous State was removed.
        */
    virtual void Resume();

    /**
        * HandleEvents is responsible for handling input events for this
        * State when it is the active State.
        * @param[in] theEvent to process from the App class Loop method
        */
    virtual void HandleEvents(sf::Event theEvent);

    /**
        * UpdateFixed is responsible for handling all State fixed update needs for
        * this State when it is the active State.
        */
    virtual void UpdateFixed() = 0;

    /**
        * UpdateVariable is responsible for handling all State variable update
        * needs for this State when it is the active State.
        * @param[in] theElapsedTime since the last Draw was called
        */
    virtual void UpdateVariable(float theElapsedTime) = 0;

    /**
        * Draw is responsible for handling all Drawing needs for this State
        * when it is the Active State.
        */
    virtual void Draw() = 0;

    /**
        * Cleanup is responsible for calling HandleCleanup if this class has
        * been flagged to be cleaned up after it completes the game loop.
        */
    void Cleanup();

    /**
        * GetElapsedTime will return one of the following:
        * 1) If this state is not paused: total elapsed time since DoInit was called
        * 2) If this state is paused: total elapsed time since Pause was called
        * 3) If this state is not initialized: total elapsed time from DoInit to DeInit
        * @return total elapsed time as described above.
        */
    float GetElapsedTime() const;

protected:
    /// Address to the App class
    Application& mApp;

    /**
        * HandleCleanup is responsible for performing any cleanup required
        * before this State is removed.
        */
    virtual void HandleCleanup(void) = 0;

private:
    /// The State ID
    const std::string     mStateID;
    /// Total elapsed time since DoInit was called
    float                 mElapsedTime;
    /// Total elapsed time paused since DoInit was called
    float                 mPausedTime;
    /// Clock will help us keep track of running and paused elapsed time
    sf::Clock             mElapsedClock;
    /// Clock will help us keep track of time paused
    sf::Clock             mPausedClock;
    /// Boolean that indicates that DoInit has been called
    bool                  mInit;
    /// State is currently paused (not active)
    bool                  mPaused;
    /// State needs to be cleaned up at the end of the next game loop
    bool                  mCleanup;
    /// Padding
    char                  pad_[5];

    /**
        * Our copy constructor is private because we do not allow copies of
        * our Singleton class
        */
    IState(const IState&);  // Intentionally undefined

    /**
        * Our assignment operator is private because we do not allow copies
        * of our Singleton class
        */
    IState& operator=(const IState&);// Intentionally undefined
};
