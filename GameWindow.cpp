#include "GameWindow.h"

int GameWindow::Execute()
{
	try
	{
		Init();
	}
	catch (char* message)
	{
		// Вывод MessageBox с сообщением об ошибке
		return 1;
	}

	// выбираем кто ходит первым
	srand(time(NULL));
	stroke = 1 + rand() % 2;
	//cells = new int[9]();

	texture = new Textures;

	mousepos = new SDL_Point;
	mousepos->x = 0;
	mousepos->y = 0;


	SDL_Event event;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			Event(&event);
		}
		Compute();
		Render();
	}

	delete texture;
	texture = nullptr;
	delete[] cells;
	cells = nullptr;
	delete mousepos;
	mousepos = nullptr;

	Quit();
	return 0;
}

void GameWindow::Compute()
{
	// проверяем было ли нажатие на новую область
	// если было, то ставим в массив клеток поля соответствующий знак и передаем ход следующему игроку
	// если небыло, то проходим дальше без изменений
	if (isklick)
	{
		if (mousepos->x >= 40 && mousepos->x <= 139)
		{
			if (mousepos->y >= 40 && mousepos->y <= 139)
			{
				if (cells[0] == 0)
				{
					cells[0] = stroke;
					stroke = (stroke == 1) ? 2 : 1;
				}
			}
			else if (mousepos->y >= 150 && mousepos->y <= 249)
			{
				if (cells[3] == 0)
				{
					cells[3] = stroke;
					stroke = (stroke == 1) ? 2 : 1;
				}
			}
			else if (mousepos->y >= 260 && mousepos->y <= 359)
			{
				if (cells[6] == 0)
				{
					cells[6] = stroke;
					stroke = (stroke == 1) ? 2 : 1;
				}
			}
		}
		else if (mousepos->x >= 150 && mousepos->x <= 249)
		{
			if (mousepos->y >= 40 && mousepos->y <= 139)
			{
				if (cells[1] == 0)
				{
					cells[1] = stroke;
					stroke = (stroke == 1) ? 2 : 1;
				}
			}
			else if (mousepos->y >= 150 && mousepos->y <= 249)
			{
				if (cells[4] == 0)
				{
					cells[4] = stroke;
					stroke = (stroke == 1) ? 2 : 1;
				}
			}
			else if (mousepos->y >= 260 && mousepos->y <= 359)
			{
				if (cells[7] == 0)
				{
					cells[7] = stroke;
					stroke = (stroke == 1) ? 2 : 1;
				}
			}
		}
		else if (mousepos->x >= 260 && mousepos->x <= 359)
		{
			if (mousepos->y >= 40 && mousepos->y <= 139)
			{
				if (cells[2] == 0)
				{
					cells[2] = stroke;
					stroke = (stroke == 1) ? 2 : 1;
				}
			}
			else if (mousepos->y >= 150 && mousepos->y <= 249)
			{
				if (cells[5] == 0)
				{
					cells[5] = stroke;
					stroke = (stroke == 1) ? 2 : 1;
				}
			}
			else if (mousepos->y >= 260 && mousepos->y <= 359)
			{
				if (cells[8] == 0)
				{
					cells[8] = stroke;
					stroke = (stroke == 1) ? 2 : 1;
				}
			}
		}
		isklick = false;
	}

	// Если в каком-то ряду есть выйгрышная комбинация
	if ((cells[0] == cells[1] && cells[0] == cells[2] && cells[0] != 0) ||
		(cells[3] == cells[4] && cells[3] == cells[5] && cells[3] != 0) ||
		(cells[6] == cells[7] && cells[6] == cells[8] && cells[6] != 0))
	{
		if (cells[0] == cells[1] && cells[0] == cells[2])
			texture->winline->SetRect(44, 86, 8, 312);
		else if (cells[3] == cells[4] && cells[3] == cells[5])
			texture->winline->SetRect(44, 196, 8, 312);
		else
			texture->winline->SetRect(44, 306, 8, 312);

		if (stroke == 1)
		{
			texture->winline->LoadImage("Images\\RedHorisontalLine.png", mainrend);
			texture->winmessage->LoadImage("Images\\Player2win.png", mainrend);
		}
		else
		{
			texture->winline->LoadImage("Images\\BlueHorisontalLine.png", mainrend);
			texture->winmessage->LoadImage("Images\\Player1win.png", mainrend);
		}
		iswin = true;
	}
	// Если в каком-то из столбцов есть выйгрышная комбинация
	else if ((cells[0] == cells[3] && cells[0] == cells[6] && cells[0] != 0) ||
		(cells[1] == cells[4] && cells[1] == cells[7] && cells[1] != 0) ||
		(cells[2] == cells[5] && cells[2] == cells[8] && cells[2] != 0))
	{
		if (cells[0] == cells[3] && cells[0] == cells[6])
			texture->winline->SetRect(86, 44, 312, 8);
		else if (cells[1] == cells[4] && cells[1] == cells[7])
			texture->winline->SetRect(196, 44, 312, 8);
		else
			texture->winline->SetRect(306, 44, 312, 8);

		if (stroke == 1)
		{
			texture->winline->LoadImage("Images\\RedVerticalLine.png", mainrend);
			texture->winmessage->LoadImage("Images\\Player2win.png", mainrend);
		}
		else
		{
			texture->winline->LoadImage("Images\\BlueVerticalLine.png", mainrend);
			texture->winmessage->LoadImage("Images\\Player1win.png", mainrend);
		}
		iswin = true;
	}
	// Если выйгрышная комбинация на главной диагонали
	else if (cells[0] == cells[4] && cells[0] == cells[8] && cells[0] != 0)
	{
		texture->winline->SetRect(40, 40, 320, 320);
		if (stroke == 1)
		{
			texture->winline->LoadImage("Images\\RedSlash.png", mainrend);
			texture->winmessage->LoadImage("Images\\Player2win.png", mainrend);
		}
		else
		{
			texture->winline->LoadImage("Images\\BlueSlash.png", mainrend);
			texture->winmessage->LoadImage("Images\\Player1win.png", mainrend);
		}
		iswin = true;
	}
	// если выйгрышная комбинация на побочной диагонали
	else if (cells[2] == cells[4] && cells[2] == cells[6] && cells[2] != 0)
	{
		texture->winline->SetRect(40, 40, 320, 320);
		if (stroke == 1)
		{
			texture->winline->LoadImage("Images\\RedBackslash.png", mainrend);
			texture->winmessage->LoadImage("Images\\Player2win.png", mainrend);
		}
		else
		{
			texture->winline->LoadImage("Images\\BlueBackslash.png", mainrend);
			texture->winmessage->LoadImage("Images\\Player1win.png", mainrend);
		}
		iswin = true;
	}
	else if (cells[0] != 0 && cells[1] != 0 && cells[2] != 0 &&
		cells[3] != 0 && cells[4] != 0 && cells[5] != 0 &&
		cells[6] != 0 && cells[7] != 0 && cells[8] != 0)
	{
		texture->winline->SetRect(40, 40, 320, 320);
		texture->winline->LoadImage("Images\\RedBackslash.png", mainrend);
		SDL_SetTextureAlphaMod(texture->winline->GetTexture(), 0x00);
		texture->winmessage->LoadImage("Images\\Draw.png", mainrend);
		iswin = true;
	}

	if (iswin)
		running = false;
}

void GameWindow::Render()
{
	SDL_RenderClear(mainrend);
	//SDL_RenderCopy(mainrend, texture->mainfield->GetTexture(), NULL, texture->mainfield->GetRect());
	SDL_RenderCopy(mainrend, texture->smallfpsign->GetTexture(), NULL, texture->smallfpsign->GetRect());
	SDL_RenderCopy(mainrend, texture->smallspsign->GetTexture(), NULL, texture->smallspsign->GetRect());

	for (int y = 40, i = 0; y <= 260; y += 110)
		for (int x = 40; x <= 260; x += 110, i++)
			if (cells[i] == 1)
			{
				SDL_Rect *tmp = texture->fpsign->GetRect();
				tmp->x = x;
				tmp->y = y;
				SDL_RenderCopy(mainrend, texture->fpsign->GetTexture(), NULL, tmp);
			}
			else if (cells[i] == 2)
			{
				SDL_Rect *tmp = texture->spsign->GetRect();
				tmp->x = x;
				tmp->y = y;
				SDL_RenderCopy(mainrend, texture->spsign->GetTexture(), NULL, tmp);
			}

	if (stroke == 1)
		SDL_RenderCopy(mainrend, texture->bluedot->GetTexture(), NULL, texture->bluedot->GetRect());
	else
		SDL_RenderCopy(mainrend, texture->reddot->GetTexture(), NULL, texture->reddot->GetRect());
	SDL_RenderPresent(mainrend);

	if (iswin)
	{
		SDL_RenderCopy(mainrend, texture->winline->GetTexture(), NULL, texture->winline->GetRect());
		SDL_RenderPresent(mainrend);
		SDL_Delay(1500);
		SDL_RenderCopy(mainrend, texture->winmessage->GetTexture(), NULL, texture->winmessage->GetRect());
		SDL_RenderPresent(mainrend);
		SDL_Delay(5000);
	}
}