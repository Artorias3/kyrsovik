#include "App.h"

int App::Execute()
{
	if (!Init())
	{
		SDL_Delay(4000);
		system("pause");
		return -1;
	}

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
	Quit();

	return 0;
}

bool App::Init()
{
	// инициализируем подсистемы SDL и SDL_image
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << SDL_GetError() << endl;
		return false;
	}
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
	cout << IMG_GetError() << endl;
	return false;
	}

	if (!(mainwind = SDL_CreateWindow("TicTacToe v1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 500, SDL_WINDOW_SHOWN)))
	{
		cout << SDL_GetError() << endl;
		return false;
	}
#ifdef _SURFACES_
	if (!(mainsurf = SDL_GetWindowSurface(mainwind)))
	{
		cout << SDL_GetError() << endl;
		return false;
	}
#elif defined _TEXTURES_
	if (!(mainrend = SDL_CreateRenderer(mainwind, -1, NULL)))
	{
		cout << SDL_GetError() << endl;
		return false;
	}
	SDL_SetRenderDrawColor(mainrend, 0xff, 0xff, 0xff, 0xff);
#endif

	srand(time(NULL));
	stroke = 1 + rand() % 2;
	cells = new int[9]();

	// загрузка изображений

	texture = new Textures;

#ifdef _TEXTURES_

	texture->mainfield->LoadImage("Images\\GameField.png", mainrend);
	texture->bluedot->LoadImage("Images\\BlueDot.png", mainrend);
	texture->reddot->LoadImage("Images\\RedDot.png", mainrend);
	if (stroke == 1)
	{
		texture->fpsign->LoadImage("Images\\BlueCross.png", mainrend);
		texture->spsign->LoadImage("Images\\RedNull.png", mainrend);
		texture->smallfpsign->LoadImage("Images\\BlueSmallCross.png", mainrend);
		texture->smallspsign->LoadImage("Images\\RedSmallNull.png", mainrend);
	}
	else
	{
		texture->fpsign->LoadImage("Images\\BlueNull.png", mainrend);
		texture->spsign->LoadImage("Images\\RedCross.png", mainrend);
		texture->smallfpsign->LoadImage("Images\\BlueSmallNull.png", mainrend);
		texture->smallspsign->LoadImage("Images\\RedSmallCross.png", mainrend);
	}

#elif defined _SURFACES_

	texture->mainfield->LoadImage("Images\\GameField.png", mainsurf);
	texture->bluedot->LoadImage("Images\\BlueDot.png", mainsurf);
	texture->reddot->LoadImage("Images\\RedDot.png", mainsurf);
	if (stroke == 1)
	{
		texture->fpsign->LoadImage("Images\\BlueCross.png", mainsurf);
		texture->spsign->LoadImage("Images\\RedNull.png", mainsurf);
		texture->smallfpsign->LoadImage("Images\\BlueSmallCross.png", mainsurf);
		texture->smallspsign->LoadImage("Images\\RedSmallNull.png", mainsurf);
	}
	else
	{
		texture->fpsign->LoadImage("Images\\BlueNull.png", mainsurf);
		texture->spsign->LoadImage("Images\\RedCross.png", mainsurf);
		texture->smallfpsign->LoadImage("Images\\BlueSmallNull.png", mainsurf);
		texture->smallspsign->LoadImage("Images\\RedSmallCross.png", mainsurf);
	}

#endif

	if (!texture->mainfield || !texture->bluedot || !texture->reddot || !texture->spsign ||
		!texture->fpsign || !texture->smallfpsign || !texture->smallspsign)
	{
		cout << SDL_GetError() << endl;
		return false;
	}

	mousepos = new SDL_Point;
	mousepos->x = 0;
	mousepos->y = 0;

	return true;
}

void App::Event(SDL_Event *event)
{
	switch (event->type)
	{
	case SDL_QUIT:
		running = false;
		break;
	case SDL_MOUSEBUTTONUP:
		switch (event->button.button)
		{
		case SDL_BUTTON_LEFT:
			mousepos->x = event->button.x;
			mousepos->y = event->button.y;
			isklick = true;
		}
		break;
	default:
		break;
	}
}

void App::Compute()
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

#ifdef _TEXTURES_

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

#elif defined _SURFACES_

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
			texture->winline->LoadImage("Images\\RedHorisontalLine.png", mainsurf);
			texture->winmessage->LoadImage("Images\\Player2win.png", mainsurf);
		}
		else
		{
			texture->winline->LoadImage("Images\\BlueHorisontalLine.png", mainsurf);
			texture->winmessage->LoadImage("Images\\Player1win.png", mainsurf);
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
			texture->winline->LoadImage("Images\\RedVerticalLine.png", mainsurf);
			texture->winmessage->LoadImage("Images\\Player2win.png", mainsurf);
		}
		else
		{
			texture->winline->LoadImage("Images\\BlueVerticalLine.png", mainsurf);
			texture->winmessage->LoadImage("Images\\Player1win.png", mainsurf);
		}
		iswin = true;
	}
	// Если выйгрышная комбинация на главной диагонали
	else if (cells[0] == cells[4] && cells[0] == cells[8] && cells[0] != 0)
	{
		texture->winline->SetRect(40, 40, 320, 320);
		if (stroke == 1)
		{
			texture->winline->LoadImage("Images\\RedSlash.png", mainsurf);
			texture->winmessage->LoadImage("Images\\Player2win.png", mainsurf);
		}
		else
		{
			texture->winline->LoadImage("Images\\BlueSlash.png", mainsurf);
			texture->winmessage->LoadImage("Images\\Player1win.png", mainsurf);
		}
		iswin = true;
	}
	// если выйгрышная комбинация на побочной диагонали
	else if (cells[2] == cells[4] && cells[2] == cells[6] && cells[2] != 0)
	{
		texture->winline->SetRect(40, 40, 320, 320);
		if (stroke == 1)
		{
			texture->winline->LoadImage("Images\\RedBackslash.png", mainsurf);
			texture->winmessage->LoadImage("Images\\Player2win.png", mainsurf);
		}
		else
		{
			texture->winline->LoadImage("Images\\BlueBackslash.png", mainsurf);
			texture->winmessage->LoadImage("Images\\Player1win.png", mainsurf);
		}
		iswin = true;
	}
	else if (cells[0] != 0 && cells[1] != 0 && cells[2] != 0 &&
			 cells[3] != 0 && cells[4] != 0 && cells[5] != 0 &&
			 cells[6] != 0 && cells[7] != 0 && cells[8] != 0)
	{
		texture->winline->SetRect(40, 40, 320, 320);
		texture->winline->LoadImage("Images\\RedBackslash.png", mainsurf);
		SDL_SetSurfaceAlphaMod(texture->winline->GetTexture(), 0x00);
		texture->winmessage->LoadImage("Images\\Draw.png", mainsurf);
		iswin = true;
	}

#endif

	if (iswin)
		running = false;
}

#ifdef _TEXTURES_

void App::Render()
{
	SDL_RenderClear(mainrend);
	SDL_RenderCopy(mainrend, texture->mainfield->GetTexture(), NULL, texture->mainfield->GetRect());
	SDL_RenderCopy(mainrend, texture->smallfpsign->GetTexture(), NULL, texture->smallfpsign->GetRect());
	SDL_RenderCopy(mainrend, texture->smallspsign->GetTexture(), NULL, texture->smallspsign->GetRect());

	for(int y = 40, i = 0; y <= 260; y += 110)
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

#elif defined _SURFACES_

void App::Render()
{
	SDL_BlitSurface(texture->mainfield->GetTexture(), NULL, mainsurf, texture->mainfield->GetRect());
	SDL_BlitSurface(texture->smallfpsign->GetTexture(), NULL, mainsurf, texture->smallfpsign->GetRect());
	SDL_BlitSurface(texture->smallspsign->GetTexture(), NULL, mainsurf, texture->smallspsign->GetRect());

	for (int y = 40, i = 0; y <= 260; y += 110)
		for (int x = 40; x <= 260; x += 110, i++)
		{
			if (cells[i] == 1)
			{
				SDL_Rect *tmp = texture->fpsign->GetRect();
				tmp->x = x;
				tmp->y = y;
				SDL_BlitSurface(texture->fpsign->GetTexture(), NULL, mainsurf, tmp);
			}
			else if (cells[i] == 2)
			{
				SDL_Rect *tmp = texture->spsign->GetRect();
				tmp->x = x;
				tmp->y = y;
				SDL_BlitSurface(texture->spsign->GetTexture(), NULL, mainsurf, tmp);
			}
		}

	if (stroke == 1)
		SDL_BlitSurface(texture->bluedot->GetTexture(), NULL, mainsurf, texture->bluedot->GetRect());
	else
		SDL_BlitSurface(texture->reddot->GetTexture(), NULL, mainsurf, texture->reddot->GetRect());
	SDL_UpdateWindowSurface(mainwind);

	if (iswin)
	{
		SDL_BlitSurface(texture->winline->GetTexture(), NULL, mainsurf, texture->winline->GetRect());
		SDL_UpdateWindowSurface(mainwind);
		SDL_Delay(1500);
		SDL_BlitSurface(texture->winmessage->GetTexture(), NULL, mainsurf, texture->winmessage->GetRect());
		SDL_UpdateWindowSurface(mainwind);
		SDL_Delay(5000);
	}
	
}
#endif

void App::Quit()
{
	delete texture;
	texture = nullptr;
	delete[] cells;
	cells = nullptr;
	delete mousepos;
	mousepos = nullptr;

	SDL_DestroyWindow(mainwind);
	mainwind = nullptr;
#ifdef _SURFACES_
	mainsurf = nullptr;
#elif defined _TEXTURES_
	SDL_DestroyRenderer(mainrend);
	mainrend = nullptr;
#endif

	SDL_Quit();
	IMG_Quit();
}