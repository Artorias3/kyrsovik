#pragma once
#include "GameWindow.h"
#include "MenuWindow.h"

#define ERROR -1

class App
{
private:
	int gameType;
	int size;
	int **buffer;
public:
	App() { gameType = 0; size = 3; buffer = nullptr; }
	~App() { if (buffer != nullptr) { for (int i = 0; i < size; i++) delete[] buffer[i]; delete[] buffer; } }
	
	bool endGame();

	int Execute();

	int runningMenu();
	int runningOptions();
	int runningPause();
	int runningOnline();
	int runningOffline();
};