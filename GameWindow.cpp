#include "GameWindow.h"

GameWindow::GameWindow(int _size) : Window()
{
	mesh = nullptr;
	fpsign = nullptr;
	spsign = nullptr;
	smallfpsign = nullptr;
	smallspsign = nullptr;
	bluedot = nullptr;
	reddot = nullptr;
	player = nullptr;
	enemy = nullptr;

	cells = nullptr;
	size = _size;
	iswin = false;

	srand(time(NULL));
	stroke = 1 + rand() % 2;

	mesh = new Image**[size];
	cells = new int*[size];
	for (int i = 0; i < size; i++)
	{
		mesh[i] = new Image*[size];
		cells[i] = new int[size];
		for (int j = 0; j < size; j++)
			cells[i][j] = FREE;
	}
}

GameWindow::GameWindow(int _size, int **_cells, int _stroke)
{
	mesh = nullptr;
	fpsign = nullptr;
	spsign = nullptr;
	smallfpsign = nullptr;
	smallspsign = nullptr;
	bluedot = nullptr;
	reddot = nullptr;
	player = nullptr;
	enemy = nullptr;

	cells = nullptr;
	size = _size;
	iswin = false;
	stroke = _stroke;

	mesh = new Image**[size];
	cells = new int*[size];
	for (int i = 0; i < size; i++)
	{
		mesh[i] = new Image*[size];
		cells[i] = new int[size];
		for (int j = 0; j < size; j++)
			cells[i][j] = _cells[i][j];
	}
}

GameWindow::~GameWindow()
{
	if (mesh != nullptr)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				if (mesh[i][j] != nullptr)
					delete mesh[i][j];
			delete[] mesh[i];
		}
		delete[] mesh;
	}
	if (fpsign != nullptr) delete fpsign;
	if (spsign != nullptr) delete spsign;
	if (smallfpsign != nullptr) delete smallfpsign;
	if (smallspsign != nullptr) delete smallspsign;
	if (bluedot != nullptr) delete bluedot;
	if (reddot != nullptr) delete reddot;
	if (player != nullptr) delete player;
	if (enemy != nullptr) delete enemy;
	
	if (cells != nullptr)
	{
		for (int i = 0; i < size; i++)
			delete[] cells[i];
		delete[] cells;
	}

	Quit();
}

void GameWindow::LoadTextures()
{
	SDL_SetWindowSize(mainwind, 110 * size + 50, 110 * size + 190);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			mesh[i][j] = new Image();
			mesh[i][j]->LoadImage("Images\\Mesh.png", mainrend);
			mesh[i][j]->SetRect(20 + i * 110, 20 + j * 110, 120, 120);
		}
	}

	fpsign = new Image();
	spsign = new Image();
	smallfpsign = new Image();
	smallspsign = new Image();
	bluedot = new Image();
	reddot = new Image();
	player = new Image();
	enemy = new Image();

	if (stroke == FIRSTPLAYER)
		fpsign->LoadImage("Images\\BlueCross.png", mainrend);
	else
		fpsign->LoadImage("Images\\BlueNull.png", mainrend);
	fpsign->SetRect(0, 0, 100, 100);

	if (stroke == SECONDPLAYER)
		spsign->LoadImage("Images\\RedCross.png", mainrend);
	else 
		spsign->LoadImage("Images\\RedNull.png", mainrend);
	spsign->SetRect(0, 0, 100, 100);
	
	if (stroke == FIRSTPLAYER)
		smallfpsign->LoadImage("Images\\BlueSmallCross.png", mainrend);
	else
		smallfpsign->LoadImage("Images\\BlueSmallNull.png", mainrend);
	smallfpsign->SetRect(300, 57 + size * 110, 39, 39);
	
	if (stroke == SECONDPLAYER)
		smallspsign->LoadImage("Images\\RedSmallCross.png", mainrend);
	else
		smallspsign->LoadImage("Images\\RedSmallNull.png", mainrend);
	smallspsign->SetRect(300, 127 + size * 110, 39, 39);
	
	
	bluedot->LoadImage("Images\\BlueDot.png", mainrend);
	bluedot->SetRect(85, 68 + size * 110, 15, 15);

	reddot->LoadImage("Images\\RedDot.png", mainrend);
	reddot->SetRect(85, 138 + size * 110, 15, 15);

	player->LoadImage("Images\\Player1.png", mainrend);
	player->SetRect(100, 50 + size * 110, 50, 200);

	enemy->LoadImage("Images\\Player2.png", mainrend);
	enemy->SetRect(100, 120 + size * 110, 50, 200);
}

int GameWindow::Compute()
{
	// проверяем было ли нажатие на новую область
	// если было, то ставим в массив клеток поля соответствующий знак и передаем ход следующему игроку
	// если небыло, то проходим дальше без изменений
	if (escape)
	{
		isklick = false;
		escape = false;
		return ESCAPE;
	}
	if (isklick)
	{
		isklick = false;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (mesh[i][j]->isCursorHit(mousepos.x, mousepos.y))
				{
					if (cells[i][j] == FREE)
					{
						cells[i][j] = stroke;
						return TURNREADY;
					}
				}
			}
		}
	}



	return 0;
}

void GameWindow::Render()
{
	SDL_SetRenderDrawColor(mainrend, 0xff, 0xff, 0xff, 0xff);
	SDL_RenderClear(mainrend);

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			SDL_RenderCopy(mainrend, mesh[i][j]->GetTexture(), NULL, mesh[i][j]->GetRect());

			if (cells[i][j] == FIRSTPLAYER)
			{
				fpsign->SetRect(30 + i * 110, 30 + j * 110, 100, 100);
				SDL_RenderCopy(mainrend, fpsign->GetTexture(), NULL, fpsign->GetRect());
			}
			else if (cells[i][j] == SECONDPLAYER)
			{
				spsign->SetRect(30 + i * 110, 30 + j * 110, 100, 100);
				SDL_RenderCopy(mainrend, spsign->GetTexture(), NULL, spsign->GetRect());
			}
		}
	}

	if (stroke == FIRSTPLAYER) SDL_RenderCopy(mainrend, bluedot->GetTexture(), NULL, bluedot->GetRect());
	else SDL_RenderCopy(mainrend, reddot->GetTexture(), NULL, reddot->GetRect());

	SDL_RenderCopy(mainrend, player->GetTexture(), NULL, player->GetRect());
	SDL_RenderCopy(mainrend, enemy->GetTexture(), NULL, enemy->GetRect());
	SDL_RenderCopy(mainrend, smallfpsign->GetTexture(), NULL, smallfpsign->GetRect());
	SDL_RenderCopy(mainrend, smallspsign->GetTexture(), NULL, smallspsign->GetRect());

	SDL_RenderPresent(mainrend);
}

void GameWindow::changeStroke()
{
	if (stroke == FIRSTPLAYER) stroke = SECONDPLAYER;
	else stroke = FIRSTPLAYER;
}