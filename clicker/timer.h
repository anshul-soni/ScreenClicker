#ifndef _TIMER_H
#define _TIMER_H

#include <windows.h>

class Timer
{
public:
	Timer();
	~Timer();
	void								InitGameTime();
	float								GetGameTime();
	float								GetFramesPerSecond();
	float								GetDeltaTime();
private:
	float								timeAtGameStart;
	UINT64								ticksPerSecond;
	float								lastUpdate;
	float								fpsUpdateInterval;
	unsigned int						numFrames;
	float								fps;
	float								lastGameTime;
};

#endif