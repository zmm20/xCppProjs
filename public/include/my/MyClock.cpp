#include "MyClock.h"


void CMyClock::clockBeg() noexcept
{
    m_tmpTime = std::chrono::system_clock::now();
}

float CMyClock::clockEnd() noexcept
{
    const auto timePoint2 = std::chrono::system_clock::now();
    const auto tickets = timePoint2 - m_tmpTime;
    const auto timeLen = std::chrono::duration_cast<std::chrono::milliseconds>(tickets);

    return timeLen.count() / 1000.0;
}