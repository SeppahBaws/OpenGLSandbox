﻿#pragma once
#include "src/helpers/Singleton.h"
#include <chrono>

class Time : public Singleton<Time>
{
public:
	static std::chrono::steady_clock::time_point GetTimePoint();
	static float GetTime();

	static float GetDeltaTime();
	
	static void Update(std::chrono::high_resolution_clock::time_point lastTime);

private:
	static float m_DeltaTime;
	static std::chrono::high_resolution_clock::time_point m_StartTime;
};
