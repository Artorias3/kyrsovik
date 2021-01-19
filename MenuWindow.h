#pragma once
#include "Window.h"

#define CLOSEWINDOW 0
#define EXIT 1
#define ONLINEGAME 2
#define OFFLINEGAME 3
#define OPTIONS 4
#define SMALLFIELD 5
#define MEDIUMFIELD 6
#define LARGEFIELD 7
#define CONTINUE 8

class MenuWindow : public Window
{
private:
	Image *buttons;
	int buttonLight;
	int menuType;
public:
	MenuWindow(int type) : Window() { buttons = nullptr; buttonLight = -1; menuType = type; }
	~MenuWindow() { if (buttons != nullptr) delete[] buttons; }

	void LoadTextures();

	int Compute();
	void Render();
};