#include "pch.h"
#include "Time.h"

float Time::m_DeltaTime = 0.0f;
std::chrono::high_resolution_clock::time_point Time::m_StartTime;

std::chrono::steady_clock::time_point Time::GetTimePoint()
{
	return std::chrono::high_resolution_clock::now();
}

float Time::GetTime()
{
	return std::chrono::duration<float>(GetTimePoint() - m_StartTime).count();
}

float Time::GetDeltaTime()
{
	return m_DeltaTime;
}

void Time::Update(std::chrono::high_resolution_clock::time_point lastTime)
{
	const auto currentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
}
