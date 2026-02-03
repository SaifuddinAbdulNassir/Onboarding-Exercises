#include "AppState.h"

using namespace ndpi;

// Constants

const uint32_t AppState::DEFAULT_MAX_PACKETS = 100;
const bool AppState::DEFAULT_RUNNING = true;
const uint64_t AppState::DEFAULT_UID = 0;
// Constructors & destructors

AppState::AppState()
    : maxPackets(DEFAULT_MAX_PACKETS), running(DEFAULT_RUNNING), uid(DEFAULT_UID)
{
}

AppState::~AppState()
{
}

// Business logic

void AppState::incrementUid()
{
    uid++;
}
