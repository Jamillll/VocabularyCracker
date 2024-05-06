#include "Timer.h"

Timer::Timer(float* returnAddress)
{
	m_ReturnAddress = returnAddress;
	m_StartTime = std::chrono::system_clock::now();
}

Timer::~Timer()
{
	std::chrono::duration<float, std::milli> duration;
	duration = std::chrono::system_clock::now() - m_StartTime;

	*m_ReturnAddress = duration.count();
}
