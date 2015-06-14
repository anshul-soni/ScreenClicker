#include "Timer.h"

Timer::Timer()
{
	this->lastUpdate = 0;
	this->fpsUpdateInterval = 1.0f;
	this->numFrames = 0;
	this->fps = 0;
	this->lastGameTime = 0;
	this->timeAtGameStart = 0;

	this->InitGameTime();
}
Timer::~Timer()
{
}

void Timer::InitGameTime()
{
	QueryPerformanceFrequency((LARGE_INTEGER *)&ticksPerSecond);
	timeAtGameStart = GetGameTime();
}

float Timer::GetGameTime()
{
	UINT64 ticks;
	float time;
	QueryPerformanceCounter((LARGE_INTEGER *)&ticks);
	time = (float)(__int64)ticks / (float)(__int64)ticksPerSecond;
	time -= timeAtGameStart;
	return time;
}

float Timer::GetFramesPerSecond()
{
	numFrames++;
	float currentUpdate = GetGameTime();
	if (currentUpdate - lastUpdate > fpsUpdateInterval)
	{
		fps = numFrames / (currentUpdate - lastUpdate);
		lastUpdate = currentUpdate;
		numFrames = 0;
	}
	return fps;
}

float Timer::GetDeltaTime()
{
	float dt = GetGameTime() - lastGameTime;
	lastGameTime += dt;
	return dt;
}