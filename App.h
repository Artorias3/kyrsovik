#pragma once
#include "Image.h"

class App
{
private:
	SDL_Window *mainwind;
#ifdef _SURFACES_
	SDL_Surface *mainsurf;
#elif defined _TEXTURES_
	SDL_Renderer *mainrend;
#endif

	SDL_Point *mousepos;
	Textures *texture;
	
	int *cells;
	int stroke;

	bool running;
	bool iswin;
	bool isklick;
public:
	App() 
	{
		mainwind = nullptr;
#ifdef _SURFACES_
		mainsurf = nullptr;
#elif defined _TEXTURES_
		mainrend = nullptr;
#endif
		mousepos = nullptr;
		texture = nullptr;
		cells = nullptr;
		
		running = true;
		iswin = false;
		isklick = false;
	}
	~App() {}

	int Execute();

	bool Init();
	void Event(SDL_Event *event);
	void Compute();
	void Render();
	void Quit();
};