#pragma once

#include "Image.h"

#define MAINMENU 1
#define OPTIONSMENU 2
#define PAUSEMENU 3

class Window
{
protected:
	SDL_Window *mainwind;
	SDL_Renderer *mainrend;

	SDL_Point mousepos;

	bool running;
	bool isklick;
	bool escape;
public:
	Window()
	{
		mainwind = nullptr;
		mainrend = nullptr;

		running = true;
		isklick = false;
		escape = false;
		mousepos.x = 0;
		mousepos.y = 0;
	}
	~Window() { Quit(); }

	bool isRunning() { return running; }
	void downRunning() { running = false; }

	virtual void Init();
	virtual void Event(SDL_Event *event);
	virtual void Quit();
};