#pragma once

#include "Textures.h"

#define MAINMENU 1
#define OPTIONSMENU 2
#define PAUSEMENU 3

class Window
{
protected:
	SDL_Window *mainwind;
	SDL_Renderer *mainrend;

	SDL_Point *mousepos;

	bool running;
	bool isklick;
public:
	Window()
	{
		mainwind = nullptr;
		mainrend = nullptr;
		mousepos = nullptr;

		running = true;
		isklick = false;
	}
	~Window() { if (mousepos != nullptr) delete mousepos; Quit(); }

	virtual void Init();
	virtual void Event(SDL_Event *event);
	virtual void Quit();
};