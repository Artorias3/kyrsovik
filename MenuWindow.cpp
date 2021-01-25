#include "MenuWindow.h"

void MenuWindow::LoadTextures()
{
	if (menuType == MAINMENU)
	{
		buttons = new Image[4];

		buttons[0].LoadImage("Images\\buttons\\OnlineGameButton.png", mainrend);
		buttons[0].SetRect(50, 50, 50, 200);

		buttons[1].LoadImage("Images\\buttons\\OfflineGameButton.png", mainrend);
		buttons[1].SetRect(50, 120, 50, 200);

		buttons[2].LoadImage("Images\\buttons\\OptionsButton.png", mainrend);
		buttons[2].SetRect(50, 190, 50, 200);

		buttons[3].LoadImage("Images\\buttons\\ExitButton.png", mainrend);
		buttons[3].SetRect(50, 260, 50, 200);
	}
	else if (menuType == OPTIONSMENU)
	{
		buttons = new Image[4];

		buttons[0].LoadImage("Images\\buttons\\SmallFieldButton.png", mainrend);
		buttons[0].SetRect(50, 50, 50, 200);

		buttons[1].LoadImage("Images\\buttons\\MediumFieldButton.png", mainrend);
		buttons[1].SetRect(50, 120, 50, 200);

		buttons[2].LoadImage("Images\\buttons\\LargeFieldButton.png", mainrend);
		buttons[2].SetRect(50, 190, 50, 200);

		buttons[3].LoadImage("Images\\buttons\\ExitButton.png", mainrend);
		buttons[3].SetRect(50, 260, 50, 200);
	}
	else if (menuType == CLIENTORHOSTMENU)
	{
		buttons = new Image[2];

		buttons[0].LoadImage("Images\\buttons\\HostButton.png", mainrend);
		buttons[0].SetRect(50, 50, 50, 200);

		buttons[1].LoadImage("Images\\buttons\\ClientButton.png", mainrend);
		buttons[1].SetRect(50, 120, 50, 200);
	}
	else if (menuType == PAUSEMENU)
	{
		buttons = new Image[2];

		buttons[0].LoadImage("Images\\buttons\\ContinueButton.png", mainrend);
		buttons[0].SetRect(50, 50, 50, 200);

		buttons[1].LoadImage("Images\\buttons\\ExitButton.png", mainrend);
		buttons[1].SetRect(50, 120, 50, 200);
	}
}

int MenuWindow::Compute()
{
	if (isklick)	// Обработка нажатий на кнопки в различных видах меню
	{
		isklick = false;

		if (menuType == MAINMENU)
		{
			if (buttons[0].isCursorHit(mousepos.x, mousepos.y)) { running = false; return ONLINEGAME; }
			else if (buttons[1].isCursorHit(mousepos.x, mousepos.y)) { running = false; return OFFLINEGAME; }
			else if (buttons[2].isCursorHit(mousepos.x, mousepos.y)) { return OPTIONS; }
			else if (buttons[3].isCursorHit(mousepos.x, mousepos.y)) { running = false; return EXIT; }
		}
		else if (menuType == OPTIONSMENU)
		{
			if (buttons[0].isCursorHit(mousepos.x, mousepos.y)) { return SMALLFIELD; }
			else if (buttons[1].isCursorHit(mousepos.x, mousepos.y)) { return MEDIUMFIELD; }
			else if (buttons[2].isCursorHit(mousepos.x, mousepos.y)) { return LARGEFIELD; }
			else if (buttons[3].isCursorHit(mousepos.x, mousepos.y)) { running = false; return EXIT; }
		}
		else if (menuType == CLIENTORHOSTMENU)
		{
			if (buttons[0].isCursorHit(mousepos.x, mousepos.y)) { running = false; return PLAYASHOST; }
			else if (buttons[1].isCursorHit(mousepos.x, mousepos.y)) { running = false; return PLAYASCLIENT; }
		}
		else if (menuType == PAUSEMENU)
		{
			if (buttons[0].isCursorHit(mousepos.x, mousepos.y)) { running = false; return CONTINUE; }
			else if (buttons[1].isCursorHit(mousepos.x, mousepos.y)) { running = false; return EXIT; }
		}
	}
	else	// Подсветка кнопок, над которыми находится курсор
	{
		// проверяем попадает ли курсор на одну и зкнопок
		// и если попадает, то загружаем подсвеченую текстуру кнопки
		if (buttons[0].isCursorHit(mousepos.x, mousepos.y))
		{
			if (buttonLight != 0)
			{
				if (menuType == MAINMENU) buttons[0].LoadImage("Images\\buttons\\OnlineGameButtonLight.png", mainrend);
				else if (menuType == OPTIONSMENU) buttons[0].LoadImage("Images\\buttons\\SmallFieldButtonLight.png", mainrend);
				else if (menuType == CLIENTORHOSTMENU) buttons[0].LoadImage("Images\\buttons\\HostButtonLight.png", mainrend);
				else if (menuType == PAUSEMENU) buttons[0].LoadImage("Images\\buttons\\ContinueButtonLight.png", mainrend);

				buttonLight = 0;
			}
		}
		else if (buttons[1].isCursorHit(mousepos.x, mousepos.y))
		{
			if (buttonLight != 1)
			{
				if (menuType == MAINMENU) buttons[1].LoadImage("Images\\buttons\\OfflineGameButtonLight.png", mainrend);
				else if (menuType == OPTIONSMENU) buttons[1].LoadImage("Images\\buttons\\MediumFieldButtonLight.png", mainrend);
				else if (menuType == CLIENTORHOSTMENU) buttons[1].LoadImage("Images\\buttons\\ClientButtonLight.png", mainrend);
				else if (menuType == PAUSEMENU) buttons[1].LoadImage("Images\\buttons\\ExitButtonLight.png", mainrend);

				buttonLight = 1;
			}
		}
		else if (menuType != PAUSEMENU && buttons[2].isCursorHit(mousepos.x, mousepos.y))
		{
			if (buttonLight != 2)
			{
				if (menuType == MAINMENU) buttons[2].LoadImage("Images\\buttons\\OptionsButtonLight.png", mainrend);
				else if (menuType == OPTIONSMENU) buttons[2].LoadImage("Images\\buttons\\LargeFieldButtonLight.png", mainrend);

				buttonLight = 2;
			}
		}
		else if (menuType != PAUSEMENU && buttons[3].isCursorHit(mousepos.x, mousepos.y))
		{
			if (buttonLight != 3)
			{
				buttons[3].LoadImage("Images\\buttons\\ExitButtonLight.png", mainrend);

				buttonLight = 3;
			}
		}
		// если курсор не попадает ни на одну из кнопок, 
		// то загружаем обычную текстуру кнопки, если она еще не загружена
		else
		{
			if (buttonLight == 0)
			{
				if (menuType == MAINMENU) buttons[0].LoadImage("Images\\buttons\\OnlineGameButton.png", mainrend);
				else if (menuType == OPTIONSMENU) buttons[0].LoadImage("Images\\buttons\\SmallFieldButton.png", mainrend);
				else if (menuType == CLIENTORHOSTMENU) buttons[0].LoadImage("Images\\buttons\\HostButton.png", mainrend);
				else if (menuType == PAUSEMENU) buttons[0].LoadImage("Images\\buttons\\ContinueButton.png", mainrend);
			}
			else if (buttonLight == 1)
			{
				if (menuType == MAINMENU) buttons[1].LoadImage("Images\\buttons\\OfflineGameButton.png", mainrend);
				else if (menuType == OPTIONSMENU) buttons[1].LoadImage("Images\\buttons\\MediumFieldButton.png", mainrend);
				else if (menuType == CLIENTORHOSTMENU) buttons[1].LoadImage("Images\\buttons\\ClientButton.png", mainrend);
				else if (menuType == PAUSEMENU) buttons[1].LoadImage("Images\\buttons\\ExitButton.png", mainrend);
			}
			else if (buttonLight == 2)
			{
				if (menuType == MAINMENU) buttons[2].LoadImage("Images\\buttons\\OptionsButton.png", mainrend);
				else if (menuType == OPTIONSMENU) buttons[2].LoadImage("Images\\buttons\\LargeFieldButton.png", mainrend);
			}
			else if (buttonLight == 3)
			{
				buttons[3].LoadImage("Images\\buttons\\ExitButton.png", mainrend);
			}
			buttonLight = -1;
		}
	}

	return 0;
}

void MenuWindow::Render()
{
	SDL_SetRenderDrawColor(mainrend, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(mainrend);

	SDL_RenderCopy(mainrend, buttons[0].GetTexture(), NULL, buttons[0].GetRect());
	SDL_RenderCopy(mainrend, buttons[1].GetTexture(), NULL, buttons[1].GetRect());
	if (menuType != PAUSEMENU && menuType != CLIENTORHOSTMENU)
	{
		SDL_RenderCopy(mainrend, buttons[2].GetTexture(), NULL, buttons[2].GetRect());
		SDL_RenderCopy(mainrend, buttons[3].GetTexture(), NULL, buttons[3].GetRect());
	}

	SDL_RenderPresent(mainrend);
}