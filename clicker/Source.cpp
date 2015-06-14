#include <windows.h>
#include <iostream>
#include <vector>
#include "Timer.h"


void  LeftClick();
POINT GetMousePosition();
void  SetMousePosition(POINT& mp);

int main()
{
	HWND myWindow;
	AllocConsole();
	myWindow = FindWindowA("ConsoleWindowClass", NULL);

	bool  running = true;
	while (running)
	{
		float seconds = 0.0f;
		int   clicks = 0;
		float waitTime = 0.0f;
		bool  getMousePositions = true;
		int   vectorPosition = 0;
		int   vectorSize = 0;
		bool  hasPoints = false;
		std::vector<POINT> mousePoints;
		std::cout << "\n\n Time \n\n >> ";
		std::cin >> waitTime;
		std::cout << std::endl;
		do
		{
			std::cout << "Press ctrl to add the current mouse position to the list or 'S' to continue" << std::endl;
			POINT mouse = GetMousePosition();
			std::cout << "\nPoints saved in list : " << mousePoints.size() << std::endl;
			if (GetAsyncKeyState(VK_CONTROL))
			{
				hasPoints = true;
				mousePoints.push_back(mouse);
				std::cout << "Added Point (" << mouse.x << ", " << mouse.y << ")" << std::endl;
				Sleep(250);
			}
			if (GetAsyncKeyState('S'))
			{
				getMousePositions = false;
			}
			COORD pos = { 0, 10 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		} while (getMousePositions);
		Timer t;
		t.InitGameTime();
		t.GetDeltaTime();
		float DT = 0.5f;
		do
		{
			DT -= t.GetDeltaTime();
			COORD pos = { 0, 15 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			std::cout << "Clicks will start in : " << DT << std::endl;

		} while (DT > 0.0f);
		DT = 0.0f;
		ShowWindow(myWindow, 0);
		vectorSize = (mousePoints.size() - 1);
		do
		{
			DT += t.GetDeltaTime();
			if (hasPoints)
			{
				SetMousePosition(mousePoints[vectorPosition]);
				vectorPosition++;
				if (vectorPosition > vectorSize)
				{
					vectorPosition = 0;
				}
			}
			LeftClick();
			Sleep(10);
			clicks++;
			if (DT > 1.0f)
			{
				seconds += DT;
				DT = 0.0f;
			}
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				running = false;
			}
		} while (seconds < waitTime && running);
		std::cout << "Finished - Mouse Was Clicked : " << clicks << " times in " << seconds << " seconds" << std::endl;
		ShowWindow(myWindow, 1);
		system("cls");
	}
}

void LeftClick()
{
	INPUT    Input = { 0 };													
	Input.type = INPUT_MOUSE;								
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;						
	SendInput(1, &Input, sizeof(INPUT));								
	ZeroMemory(&Input, sizeof(INPUT));								
	Input.type = INPUT_MOUSE;									
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;								
	SendInput(1, &Input, sizeof(INPUT));								
}


POINT GetMousePosition()
{
	static POINT m;
	POINT mouse;
	GetCursorPos(&mouse);
	m.x = mouse.x;
	m.y = mouse.y;
	return m;
}

void SetMousePosition(POINT& mp)
{
	long sWidth = GetSystemMetrics(SM_CXSCREEN) - 1;
	long sHeight = GetSystemMetrics(SM_CYSCREEN) - 1;
	float x = mp.x * (65535.0f / sWidth);
	float y = mp.y * (65535.0f / sHeight);
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Input.mi.dx = (long)x;
	Input.mi.dy = (long)y;
	SendInput(1, &Input, sizeof(INPUT));
}
