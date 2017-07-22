#pragma once
#include <chrono>

class CMyClock
{
public:
    void clockBeg() noexcept;
    float clockEnd() noexcept; // ������
private:
    std::chrono::time_point<std::chrono::system_clock> m_tmpTime;
};