#include "Window.h"

void Window::Init()
{
	// инициализируем подсистемы SDL и SDL_image
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw "SDL initialization fault";
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		throw "SDL_image initialization fault";

	if (!(mainwind = SDL_CreateWindow("TicTacToe v1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 500, SDL_WINDOW_SHOWN)))
		throw "Window create fault";
	if (!(mainrend = SDL_CreateRenderer(mainwind, -1, NULL)))
		throw "Render create fault";
}

void Window::Quit()
{
	SDL_DestroyWindow(mainwind);
	mainwind = nullptr;
	SDL_DestroyRenderer(mainrend);
	mainrend = nullptr;

	SDL_Quit();
	IMG_Quit();
}

void Window::Event(SDL_Event *event)
{
	switch (event->type)
	{
	case SDL_QUIT:
		running = false;
		break;
	case SDL_MOUSEBUTTONUP:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			mousepos.x = event->button.x;
			mousepos.y = event->button.y;
			isklick = true;
		}
		break;
	case SDL_MOUSEMOTION:
		mousepos.x = event->motion.x;
		mousepos.y = event->motion.y;
		break;
	case SDL_KEYDOWN:
		if (event->key.keysym.sym == SDLK_ESCAPE)
			escape = true;
		break;
	default:
		break;
	}
}