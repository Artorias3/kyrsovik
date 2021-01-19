#include "App.h"

int App::Execute()
{
	if (runningMenu() == ERROR)
		return ERROR;

	if (gameType == ONLINEGAME)
	{
		if (runningOnline() == ERROR)
			return ERROR;
	}
	else if (gameType == OFFLINEGAME)
	{
		if (runningOffline() == ERROR)
			return ERROR;
	}

	return 0;
}

int App::runningMenu()
{
	MenuWindow *mainMenu = new MenuWindow(MAINMENU);
	try { mainMenu->Init(); mainMenu->LoadTextures(); }
	catch (const char* error)
	{
		// Вывод MessageBox с сообщением об ошибке
		return ERROR;
	}

	gameType = 0;
	while (mainMenu->isRunning())
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
			mainMenu->Event(&event);

		switch (mainMenu->Compute())
		{
		case ONLINEGAME:
			gameType = ONLINEGAME;
			break;
		case OFFLINEGAME:
			gameType = OFFLINEGAME;
			break;
		case OPTIONS:
			delete mainMenu;
			
			if (runningOptions() == ERROR)
				return ERROR;

			mainMenu = new MenuWindow(MAINMENU);
			try { mainMenu->Init(); mainMenu->LoadTextures(); }
			catch (const char* error)
			{
				// Вывод MessageBox с сообщением об ошибке
				return ERROR;
			}
			break;
		}

		mainMenu->Render();
	}
	delete mainMenu;

	return 0;
}

int App::runningOptions()
{
	MenuWindow *optionsMenu = new MenuWindow(OPTIONSMENU);
	try { optionsMenu->Init(); optionsMenu->LoadTextures(); }
	catch (const char* error)
	{
		// Вывод MessageBox с сообщением об ошибке
		return ERROR;
	}

	SDL_Event event;
	while (optionsMenu->isRunning())
	{
		while (SDL_PollEvent(&event))
			optionsMenu->Event(&event);

		switch (optionsMenu->Compute())
		{
		case SMALLFIELD:
			size = 3;
			break;
		case MEDIUMFIELD:
			size = 5;
			break;
		case LARGEFIELD:
			size = 7;
			break;
		}

		optionsMenu->Render();
	}
	delete optionsMenu;

	return 0;
}

int App::runningPause()
{
	MenuWindow *pauseMenu = new MenuWindow(PAUSEMENU);
	try { pauseMenu->Init(); pauseMenu->LoadTextures(); }
	catch (const char* error)
	{
		// Вывод MessageBox с сообщением об ошибке
		return ERROR;
	}

	int ret = 0;
	SDL_Event event;
	while (pauseMenu->isRunning())
	{
		while (SDL_PollEvent(&event))
			pauseMenu->Event(&event);

		switch (pauseMenu->Compute())
		{
		case CONTINUE:
			ret = CONTINUE;
			break;
		case EXIT:
			ret = EXIT;
			break;
		}

		pauseMenu->Render();
	}
	delete pauseMenu;

	return ret;
}

int App::runningOnline()
{
	GameWindow *gameWindow = new GameWindow(size);
	try { gameWindow->Init(); gameWindow->LoadTextures(); }
	catch (const char* error)
	{
		// Вывод MessageBox с сообщением об ошибке
		return ERROR;
	}

	SDL_Event event;
	while (gameWindow->isRunning())
	{
		while (SDL_PollEvent(&event))
			gameWindow->Event(&event);

		switch (gameWindow->Compute())
		{

		}


		gameWindow->Render();
	}
	delete gameWindow;

	return 0;
}

int App::runningOffline()
{
	buffer = new int*[size];
	for (int i = 0; i < size; i++)
	{
		buffer[i] = new int[size];
		for (int j = 0; j < size; j++)
			buffer[i][j] = 0;
	}

	GameWindow *gameWindow = new GameWindow(size);
	try { gameWindow->Init(); gameWindow->LoadTextures(); }
	catch (const char* error)
	{
		// Вывод MessageBox с сообщением об ошибке
		return ERROR;
	}
	int firstTurn = gameWindow->getStroke();

	gameWindow->Render();

	SDL_Event event;
	while (gameWindow->isRunning())
	{
		if (gameWindow->getStroke() == FIRSTPLAYER)
		{
			while (SDL_PollEvent(&event))
				gameWindow->Event(&event);

			switch (gameWindow->Compute())
			{
			case ESCAPE:
				delete gameWindow;
				if (runningPause() == EXIT)
					return EXIT;

				gameWindow = new GameWindow(size, buffer, firstTurn);
				try { gameWindow->Init(); gameWindow->LoadTextures(); }
				catch (const char* error)
				{
					// Вывод MessageBox с сообщением об ошибке
					return ERROR;
				}
				if (gameWindow->getStroke() != FIRSTPLAYER)
					gameWindow->changeStroke();
				break;
			case TURNREADY:
				for (int i = 0; i < size; i++)
					for (int j = 0; j < size; j++)
						buffer[i][j] = gameWindow->getCell(i, j);
				gameWindow->changeStroke();
				break;
			}
		}
		else
		{
			for (int i = 0; i < 300; i++)
			{
				while (SDL_PollEvent(&event))
				{
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						delete gameWindow;
						if (runningPause() == EXIT)
							return EXIT;

						gameWindow = new GameWindow(size, buffer, firstTurn);
						try { gameWindow->Init(); gameWindow->LoadTextures(); }
						catch (const char* error)
						{
							// Вывод MessageBox с сообщением об ошибке
							return ERROR;
						}
						if (gameWindow->getStroke() != SECONDPLAYER)
							gameWindow->changeStroke();
					}
				}
				gameWindow->Compute();
				gameWindow->Render();
				SDL_Delay(7);
			}

			int x = -1, y = -1;

			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (buffer[i][j] == SECONDPLAYER )
					{
						if (j != size - 1 && buffer[i][j + 1] == FREE) { x = i; y = j + 1; i = size; break; }
						if (j != 0 && buffer[i][j - 1] == FREE) { x = i; y = j - 1; i = size; break; }
						if (i != 0 && j != 0 && buffer[i - 1][j - 1] == FREE) { x = i - 1; y = j - 1; i = size; break; }
						if (i != size - 1 && j != size - 1 && buffer[i + 1][j + 1] == FREE) { x = i + 1; y = j + 1; i = size; break; }
						if (i != size - 1 && buffer[i + 1][j] == FREE) { x = i + 1; y = j; i = size; break; }
						if (i != 0 && buffer[i - 1][j] == FREE) { x = i - 1; y = j; i = size; break; }
						if (i != 0 && j != size - 1 && buffer[i - 1][j + 1] == FREE) { x = i - 1; y = j + 1; i = size; break; }
						if (i != size - 1 && j != 0 && buffer[i + 1][j - 1] == FREE) { x = i + 1; y = j - 1; i = size; break; }
					}
				}
			}

			if (x == -1 || y == -1)
			{
				while (true)
				{
					x = rand() % size;
					y = rand() % size;
					if (buffer[x][y] == FREE)
						break;
				}
			}

			buffer[x][y] = SECONDPLAYER;
			gameWindow->setCell(x, y, SECONDPLAYER);
			gameWindow->changeStroke();
		}
		gameWindow->Render();
	}
	delete gameWindow;

	return 0;
}

bool App::endGame()
{

	return true;
}