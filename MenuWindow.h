#pragma once
#include "Window.h"

#define CLOSEWINDOW 0
#define EXIT 1
#define ONLINEGAME 2
#define PLAYASHOST 3
#define PLAYASCLIENT 4 
#define OFFLINEGAME 5
#define OPTIONS 6
#define SMALLFIELD 7
#define MEDIUMFIELD 8
#define LARGEFIELD 9
#define CONTINUE 10

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