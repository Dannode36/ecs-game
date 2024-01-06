#include <assert.h>
#include <interfaces/IState.h>
#include <types.h>

IState::IState(const std::string theStateID, Application& theApp) :
    mApp(theApp),
    mStateID(theStateID),
    mElapsedTime(0.0f),
    mPausedTime(0.0f),
    mElapsedClock(),
    mPausedClock(),
    mInit(false),
    mPaused(false),
    mCleanup(false),
    pad_()
{
    std::cout << "IState::ctor(" << mStateID << ")" << std::endl;
}

IState::~IState()
{
    std::cout << "IState::dtor(" << mStateID << ")" << std::endl;
}

const std::string IState::GetID() const
{
    return mStateID;
}

void IState::DoInit()
{
    std::cout << "IState::DoInit(" << mStateID << ")" << std::endl;

    // If Cleanup hasn't been called yet, call it now!
    if (true == mCleanup)
    {
        HandleCleanup();
    }

    // Initialize if necessary
    if (false == mInit)
    {
        mInit = true;
        mPaused = false;
        mElapsedTime = 0.0f;
        mElapsedClock.restart();
        mPausedTime = 0.0f;
        mPausedClock.restart();
    }
}

void IState::DeInit()
{
    std::cout << "IState::DeInit(" << mStateID << ")" << std::endl;

    if (true == mInit)
    {
        mCleanup = true;
        mInit = false;
        mElapsedTime += mElapsedClock.getElapsedTime().asSeconds();

        if (true == mPaused)
        {
            mPausedTime += mPausedClock.getElapsedTime().asSeconds();
        }
    }
}

bool IState::IsInitComplete() const
{
    return mInit;
}

bool IState::IsPaused() const
{
    return mPaused;
}

void IState::Pause()
{
    std::cout << "IState::Pause(" << mStateID << ")" << std::endl;

    if (false == mPaused)
    {
        mPaused = true;
        mPausedClock.restart();
    }
}

void IState::Resume()
{
    std::cout << "IState::Resume(" << mStateID << ")" << std::endl;

    if (true == mPaused)
    {
        mPaused = false;
        mPausedTime += mPausedClock.getElapsedTime().asSeconds();
    }
}

void IState::HandleEvents(sf::Event theEvent)
{
    // Exit program if Escape key is pressed
    if ((theEvent.type == sf::Event::KeyReleased) && (theEvent.key.code == sf::Keyboard::Escape))
    {
        // Signal the application to exit
        mApp.Stop(StatusAppOK);

    }
}

float IState::GetElapsedTime() const
{
    float result = mElapsedClock.getElapsedTime().asSeconds();

    if (false == mInit)
    {
        result = mElapsedTime;
    }

    return result;
}

void IState::Cleanup()
{
    // This will be true if this IState is about to be deleted soon
    if (true == mCleanup)
    {
        // Call our handle cleanup virtual method
        HandleCleanup();

        // Clear our cleanup flag
        mCleanup = false;
    }
}
