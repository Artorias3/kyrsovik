#include "App.h"

int App::Execute()
{
	mainMenu = new MenuWindow(MAINMENU);
	try { mainMenu->Init(); mainMenu->LoadTextures(); }
	catch (const char* error)
	{
		// Вывод MessageBox с сообщением об ошибке
		return 1;
	}

	while (true)
	{
		int ret = mainMenu->Execute();
		if (ret == ONLINEGAME)
		{

		}
		else if (ret == OFFLINEGAME)
		{

		}
		else if (ret == OPTIONS)
		{

		}
		else if (ret == EXIT || ret == CLOSEWINDOW)
		{
			delete mainMenu;
			return 0;
		}
	}

}