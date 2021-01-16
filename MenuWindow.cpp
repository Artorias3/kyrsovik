#include "MenuWindow.h"

void MenuWindow::LoadTextures()
{
	if (menuType == MAINMENU)
	{
		buttons = new Image[4];

		buttons[0].LoadImage("Images\\OnlineGameButton.png", mainrend);
		buttons[0].SetRect(50, 50, 50, 200);

		buttons[1].LoadImage("Images\\OfflineGameButton.png", mainrend);
		buttons[1].SetRect(50, 120, 50, 200);

		buttons[2].LoadImage("Images\\OptionsButton.png", mainrend);
		buttons[2].SetRect(50, 190, 50, 200);

		buttons[3].LoadImage("Images\\ExitButton.png", mainrend);
		buttons[3].SetRect(50, 260, 50, 200);
	}
	else if (menuType == OPTIONSMENU)
	{
		buttons = new Image[4];

		buttons[0].LoadImage("Images\\SmallFieldButton.png", mainrend);
		buttons[0].SetRect(50, 50, 50, 200);

		buttons[1].LoadImage("Images\\MediumFieldButton.png", mainrend);
		buttons[1].SetRect(50, 120, 50, 200);

		buttons[2].LoadImage("Images\\LargeFieldButton.png", mainrend);
		buttons[2].SetRect(50, 190, 50, 200);

		buttons[3].LoadImage("Images\\ExitButton.png", mainrend);
		buttons[3].SetRect(50, 260, 50, 200);
	}
	else if (menuType == PAUSEMENU)
	{
		buttons = new Image[2];

		buttons[0].LoadImage("Images\\ContinueButton.png", mainrend);
		buttons[0].SetRect(50, 50, 50, 200);

		buttons[1].LoadImage("Images\\ExitButton.png", mainrend);
		buttons[1].SetRect(50, 120, 50, 200);
	}
}

int MenuWindow::Execute()
{
	running = true;
	isklick = false;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
			Event(&event);

		int ret = Compute();
		if (ret != 0)
			return ret;

		Render();
	}

	return CLOSEWINDOW;
}

int MenuWindow::Compute()
{
	if (isklick)	// Обработка нажатий на кнопки в различных видах меню
	{
		if (menuType == MAINMENU)
		{
			if (buttons[0].isCursorHit(mousepos->x, mousepos->y))
				return ONLINEGAME;
			else if (buttons[1].isCursorHit(mousepos->x, mousepos->y))
				return OFFLINEGAME;
			else if (buttons[2].isCursorHit(mousepos->x, mousepos->y))
				return OPTIONS;
			else if (buttons[3].isCursorHit(mousepos->x, mousepos->y))
			{
				running = false;
				return EXIT;
			}
		}
		else if (menuType == OPTIONSMENU)
		{
			if (buttons[0].isCursorHit(mousepos->x, mousepos->y))
				return SMALLFIELD;
			else if (buttons[1].isCursorHit(mousepos->x, mousepos->y))
				return MEDIUMFIELD;
			else if (buttons[2].isCursorHit(mousepos->x, mousepos->y))
				return LARGEFIELD;
			else if (buttons[3].isCursorHit(mousepos->x, mousepos->y))
			{
				running = false;
				return EXIT;
			}
		}
		else if (menuType == PAUSEMENU)
		{
			if (buttons[0].isCursorHit(mousepos->x, mousepos->y))
				return LARGEFIELD;
			else if (buttons[1].isCursorHit(mousepos->x, mousepos->y))
			{
				running = false;
				return EXIT;
			}
		}
	}
	else	// Подсветка кнопок, над которыми находится курсор
	{
		// проверяем попадает ли курсор на одну и зкнопок
		// и если попадает, то загружаем подсвеченую текстуру кнопки
		if (buttons[0].isCursorHit(mousepos->x, mousepos->y))
		{
			if (buttonLight != 0)
			{
				if (menuType == MAINMENU)
					buttons[0].LoadImage("Images\\OnlineGameButtonLight.png", mainrend);
				else if (menuType == OPTIONSMENU)
					buttons[0].LoadImage("Images\\SmallFieldButtonLight.png", mainrend);
				else if (menuType == PAUSEMENU)
					buttons[0].LoadImage("Images\\ContinueButtonLight.png", mainrend);

				buttonLight = 0;
			}
		}
		else if (buttons[1].isCursorHit(mousepos->x, mousepos->y))
		{
			if (buttonLight != 1)
			{
				if (menuType == MAINMENU)
					buttons[1].LoadImage("Images\\OfflineGameButtonLight.png", mainrend);
				else if (menuType == OPTIONSMENU)
					buttons[1].LoadImage("Images\\MediumFieldButtonLight.png", mainrend);
				else if (menuType == PAUSEMENU)
					buttons[1].LoadImage("Images\\ExitButtonLight.png", mainrend);

				buttonLight = 1;
			}
		}
		else if (menuType != PAUSEMENU && buttons[2].isCursorHit(mousepos->x, mousepos->y))
		{
			if (buttonLight != 2)
			{
				if (menuType == MAINMENU)
					buttons[2].LoadImage("Images\\OptionsButtonLight.png", mainrend);
				else if (menuType == OPTIONSMENU)
					buttons[2].LoadImage("Images\\LargeFieldButtonLight.png", mainrend);

				buttonLight = 2;
			}
		}
		else if (menuType != PAUSEMENU && buttons[3].isCursorHit(mousepos->x, mousepos->y))
		{
			if (buttonLight != 3)
			{
				buttons[3].LoadImage("Images\\ExitButtonLight.png", mainrend);

				buttonLight = 3;
			}
		}
		// если курсор не попадает ни на одну из кнопок, 
		// то загружаем обычную текстуру кнопки, если она еще не загружена
		else
		{
			if (buttonLight == 0)
			{
				if (menuType == MAINMENU)
					buttons[0].LoadImage("Images\\OnlineGameButton.png", mainrend);
				else if (menuType == OPTIONSMENU)
					buttons[0].LoadImage("Images\\SmallFieldButton.png", mainrend);
				else if (menuType == PAUSEMENU)
					buttons[0].LoadImage("Images\\ContinueButton.png", mainrend);
			}
			else if (buttonLight == 1)
			{
				if (menuType == MAINMENU)
					buttons[1].LoadImage("Images\\OfflineGameButton.png", mainrend);
				else if (menuType == OPTIONSMENU)
					buttons[1].LoadImage("Images\\MediumFieldButton.png", mainrend);
				else if (menuType == PAUSEMENU)
					buttons[1].LoadImage("Images\\ExitButton.png", mainrend);
			}
			else if (buttonLight == 2)
			{
				if (menuType == MAINMENU)
					buttons[2].LoadImage("Images\\OptionsButton.png", mainrend);
				else if (menuType == OPTIONSMENU)
					buttons[2].LoadImage("Images\\LargeFieldButton.png", mainrend);
			}
			else if (buttonLight == 3)
			{
				buttons[3].LoadImage("Images\\ExitButton.png", mainrend);
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
	if (menuType != PAUSEMENU)
	{
		SDL_RenderCopy(mainrend, buttons[2].GetTexture(), NULL, buttons[2].GetRect());
		SDL_RenderCopy(mainrend, buttons[3].GetTexture(), NULL, buttons[3].GetRect());
	}

	SDL_RenderPresent(mainrend);
}