#pragma once
#include "Window.h"

class GameWindow : public Window
{
private:
	Textures *texture;
	
	int *cells;
	int stroke;
	int size;

	bool iswin;
public:
	GameWindow() : Window()
	{
		texture = nullptr;
		cells = nullptr;
		
		size = 3;
		iswin = false;
	}
	~GameWindow() {}

	int Execute();

	void Compute();
	void Render();
};