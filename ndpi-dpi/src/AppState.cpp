#include "AppState.h"

using namespace ndpi;

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
