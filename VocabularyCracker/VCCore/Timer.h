#pragma once
#include <chrono>
#include <ctime>

class Timer
{
private:
	float* m_ReturnAddress = nullptr;
	std::chrono::system_clock::time_point m_StartTime;

public:
	Timer(float* returnAddress);
	~Timer();
};