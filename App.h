#pragma once
#include "GameWindow.h"
#include "MenuWindow.h"


class App
{
private:
	MenuWindow *mainMenu;
	MenuWindow *optionsMenu;
	MenuWindow *pauseMenu;

	GameWindow *gameWindow;
public:
	App() 
	{
		mainMenu = nullptr;
		optionsMenu = nullptr;
		pauseMenu = nullptr;
		gameWindow = nullptr;
	}
	int Execute();
};