#include <assert.h>
#include <interfaces/IState.h>
#include <types.h>

IState::IState(const std::string theStateID, IApplication& theApp) :
    app(theApp),
    mStateID(theStateID),
    mLoaded(false),
    mPaused(false),
    mCleanup(false) { }

IState::~IState() {
    Unload();
    Cleanup();
}

const std::string IState::GetID() const {
    return mStateID;
}

bool IState::IsLoaded() const {
    return mLoaded;
}

bool IState::IsPaused() const {
    return mPaused;
}

void IState::Load() {
    // If Cleanup hasn't been called yet, call it now!
    if (true == mCleanup) {
        Dispose();
    }

    // Initialize if necessary
    if (mLoaded == false) {
        mLoaded = true;
        mPaused = false;
    }
}

void IState::Unload() {
    if (mLoaded == true) {
        mCleanup = true;
        mLoaded = false;
    }
}

void IState::Pause() {
    if (mPaused == false) {
        mPaused = true;
    }
}

void IState::Resume() {
    if (mPaused == true) {
        mPaused = false;
    }
}

void IState::Cleanup()
{
    if (mCleanup == true)
    {
        // Call our handle cleanup virtual method
        Dispose();

        // Clear our cleanup flag
        mCleanup = false;
    }
}
