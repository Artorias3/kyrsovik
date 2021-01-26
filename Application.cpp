#include "Application.h"

int Application::Execute()
{
	if (runningMenu() == ERROR)
		return ERROR;

	if (gameType == ONLINEGAME)
	{
		if (runningHostOrClientMenu() == ERROR)
			return ERROR;

		if (gameType == PLAYASHOST)
		{
			if (runningOnlineAsHost() == ERROR)
				return ERROR;
		}	
		else if (gameType == PLAYASCLIENT)
		{
			if (runningOnlineAsClient() == ERROR)
				return ERROR;
		}
	}
	else if (gameType == OFFLINEGAME)
	{
		if (runningOffline() == ERROR)
			return ERROR;
	}

	return 0;
}

int Application::runningMenu()
{
	MenuWindow *mainMenu = new MenuWindow(MAINMENU);
	try { mainMenu->Init(); mainMenu->LoadTextures(); }
	catch (const char* error)
	{
		// Вывод MessageBox с сообщением об ошибке
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error, NULL);
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
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error, NULL);
				return ERROR;
			}
			break;
		}

		mainMenu->Render();
	}
	delete mainMenu;

	return CLOSEWINDOW;
}

int Application::runningHostOrClientMenu()
{
	MenuWindow *window = new MenuWindow(CLIENTORHOSTMENU);
	try { window->Init(); window->LoadTextures(); }
	catch (const char* error)
	{
		// Вывод MessageBox с сообщением об ошибке
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error, NULL);
		return ERROR;
	}

	SDL_Event event;
	while (window->isRunning())
	{
		while (SDL_PollEvent(&event))
			window->Event(&event);

		switch (window->Compute())
		{
		case PLAYASHOST:
			gameType = PLAYASHOST;
			break;
		case PLAYASCLIENT:
			gameType = PLAYASCLIENT;
			break;
		}
		window->Render();
	}
	delete window;

	return CLOSEWINDOW;
}

int Application::runningOptions()
{
	MenuWindow *optionsMenu = new MenuWindow(OPTIONSMENU);
	try { optionsMenu->Init(); optionsMenu->LoadTextures(); }
	catch (const char* error)
	{
		// Вывод MessageBox с сообщением об ошибке
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error, NULL);
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

	return CLOSEWINDOW;
}

int Application::runningPause()
{
	MenuWindow *pauseMenu = new MenuWindow(PAUSEMENU);
	try { pauseMenu->Init(); pauseMenu->LoadTextures(); }
	catch (const char* error)
	{
		// Вывод MessageBox с сообщением об ошибке
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error, NULL);
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

int Application::runningOnlineAsHost()
{
	WSADATA WSAdata;
	WORD version = MAKEWORD(2, 2);
	SOCKADDR_IN inputaddres;
	SOCKET listenersocket = NULL;
	SOCKET inputconnection = NULL;
	int sizeofaddress = sizeof(inputaddres);

	inputaddres.sin_addr.S_un.S_addr = INADDR_ANY;
	inputaddres.sin_port = htons(5050);
	inputaddres.sin_family = AF_INET;

	GameWindow *gameWindow = new GameWindow(size);
	try 
	{ 
		if (WSAStartup(version, &WSAdata))
			throw "Couldn't initialize winsock.";
		if ((listenersocket = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
			throw "Could not create a listener socket.";
		if (bind(listenersocket, (SOCKADDR*)&inputaddres, sizeofaddress) == SOCKET_ERROR)
			throw "Could not bind listener.";
		if (listen(listenersocket, SOMAXCONN) == SOCKET_ERROR)
			throw "Could not start listening.";

		gameWindow->Init(); 
		gameWindow->LoadTextures(); 
	}
	catch (const char* error)
	{
		// Вывод MessageBox с сообщением об ошибке
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error, NULL);
		return ERROR;
	}

	buffer = new int*[size];
	for (int i = 0; i < size; i++)
	{
		buffer[i] = new int[size];
		for (int j = 0; j < size; j++)
			buffer[i][j] = 0;
	}

	string msg = "";
	SDL_Event event;
	while (gameWindow->isRunning())
	{
		// проверяем наличие входящего подключения
		if (gameWindow->getConnect() == false)
		{
			int ret = 0;
			fd_set socketset;
			timeval timeout = { 0, 0 };
			FD_ZERO(&socketset);
			FD_SET(listenersocket, &socketset);
			ret = select(listenersocket + 1, &socketset, NULL, NULL, &timeout);

			try
			{
				if (ret != NULL)
				{
					if (ret == SOCKET_ERROR)
						throw "Can't check input connection.";
					if ((inputconnection = accept(listenersocket, (SOCKADDR*)&inputaddres, &sizeofaddress)) == INVALID_SOCKET)
						throw "Can't accept input connection.";

					gameWindow->setConnect();
					unsigned long argp = 1;
					if (ioctlsocket(inputconnection, FIONBIO, &argp) == SOCKET_ERROR)
						throw "Can't create non-bloking socket.";
					closesocket(listenersocket);
				}
			}
			catch (const char* error)
			{
				// Вывод MessageBox с сообщением об ошибке
				SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error, NULL);
				return ERROR;
			}

			msg = "connect ";
			msg += (size + '0');
			msg += ' ';
			if (gameWindow->getStroke() == FIRSTPLAYER)
				msg += (SECONDPLAYER + '0');
			else
				msg += (FIRSTPLAYER + '0');
			send(inputconnection, msg.c_str(), BUFFERSIZE, NULL);
		}

		if (gameWindow->getStroke() == FIRSTPLAYER)
		{
			while (SDL_PollEvent(&event))
				gameWindow->Event(&event);

			switch (gameWindow->Compute())
			{
			case ESCAPE:
			{
				int turn = gameWindow->getStroke();
				delete gameWindow;
				if (runningPause() == EXIT)
				{
					msg = "disconnect";
					send(inputconnection, msg.c_str(), BUFFERSIZE, NULL);
					closesocket(inputconnection);
					WSACleanup();
					return EXIT;
				}
					
				gameWindow = new GameWindow(size, buffer, turn);
				try { gameWindow->Init(); gameWindow->LoadTextures(); }
				catch (const char* error)
				{
					msg = "disconnect";
					send(inputconnection, msg.c_str(), BUFFERSIZE, NULL);
					closesocket(inputconnection);
					WSACleanup();
					// Вывод MessageBox с сообщением об ошибке
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error, NULL);
					return ERROR;
				}
				break;
			}
			case TURNREADY:
			{
				SDL_Point lastmove = gameWindow->getLastMove();
				buffer[lastmove.x][lastmove.y] = FIRSTPLAYER;

				msg = "";
				msg += (lastmove.x + '0');
				msg += ' ';
				msg += (lastmove.y + '0');
				send(inputconnection, msg.c_str(), BUFFERSIZE, NULL);

				if (gameWindow->isWin())
					gameWindow->LoadEndMessage(FPWIN);
				gameWindow->changeStroke();
				break;
			}
			}
		}
		else
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					msg = "disconnect";
					send(inputconnection, msg.c_str(), BUFFERSIZE, NULL);
					closesocket(inputconnection);
					WSACleanup();
					gameWindow->downRunning();
				}
				else if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					int turn = gameWindow->getStroke();
					delete gameWindow;
					if (runningPause() == EXIT)
					{
						msg = "disconnect";
						send(inputconnection, msg.c_str(), BUFFERSIZE, NULL);
						closesocket(inputconnection);
						WSACleanup();
						return EXIT;
					}

					gameWindow = new GameWindow(size, buffer, turn);
					try { gameWindow->Init(); gameWindow->LoadTextures(); }
					catch (const char* error)
					{
						msg = "disconnect";
						send(inputconnection, msg.c_str(), BUFFERSIZE, NULL);
						closesocket(inputconnection);
						WSACleanup();
						// Вывод MessageBox с сообщением об ошибке
						SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error, NULL);
						return ERROR;
					}
					break;
				}
			}
		}
		
		msg = "";
		char buf[BUFFERSIZE];
		if (gameWindow->isRunning() && recv(inputconnection, buf, BUFFERSIZE, NULL) != ERROR)
		{
			msg = buf;

			if (msg.find("disconnect") != string::npos)
			{
				gameWindow->LoadEndMessage(FPWIN);
				gameWindow->downRunning();
			}
			else
			{
				SDL_Point coord;
				coord.x = (msg[0] - '0');
				coord.y = (msg[2] - '0');

				gameWindow->setCell(coord.x, coord.y, SECONDPLAYER);
				buffer[coord.x][coord.y] = SECONDPLAYER;
				if (gameWindow->isWin())
					gameWindow->LoadEndMessage(SPWIN);
				gameWindow->changeStroke();
			}
		}

		if (gameWindow->isDraw())
			gameWindow->LoadEndMessage(DRAW);
		gameWindow->Render();
	}
	delete gameWindow;

	closesocket(inputconnection);
	WSACleanup();
	return 0;
}

int Application::runningOnlineAsClient()
{
	string msg = "";
	WSADATA WSAdata;
	WORD version = MAKEWORD(2, 2);
	SOCKADDR_IN outputaddres;
	SOCKET outputconnection = NULL;
	int sizeofaddress = sizeof(outputaddres);

	outputaddres.sin_addr.S_un.S_addr = inet_addr(OUTPUTADDRESS);
	outputaddres.sin_port = htons(5050);
	outputaddres.sin_family = AF_INET;

	GameWindow *gameWindow = new GameWindow(size);
	try 
	{ 
		if (WSAStartup(version, &WSAdata))
			throw "Couldn't initialize winsock.";
		if ((outputconnection = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
		{
			WSACleanup();
			throw "Could not create a socket.";
		}
		if (connect(outputconnection, (SOCKADDR*)&outputaddres, sizeofaddress) == INVALID_SOCKET)
		{
			closesocket(outputconnection);
			WSACleanup();
			throw "Can't connect to host.";
		}	
		else
		{
			gameWindow->setConnect();

			char buf[BUFFERSIZE];
			recv(outputconnection, buf, BUFFERSIZE, NULL);
			msg = buf;

			gameWindow->setStroke((msg[10] - '0'));
			if (size != (msg[8] - '0'))
			{
				msg = "disconnect";
				send(outputconnection, msg.c_str(), BUFFERSIZE, NULL);
				closesocket(outputconnection);
				WSACleanup();
				throw "The opponent has a different field size.";
			}

			unsigned long argp = 1;
			if (ioctlsocket(outputconnection, FIONBIO, &argp) == SOCKET_ERROR)
				throw "Can't create non-bloking socket.";
		}
		
		gameWindow->Init();
		gameWindow->LoadTextures();
	}
	catch (const char* error)
	{
		// Вывод MessageBox с сообщением об ошибке
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error, NULL);
		return ERROR;
	}


	buffer = new int*[size];
	for (int i = 0; i < size; i++)
	{
		buffer[i] = new int[size];
		for (int j = 0; j < size; j++)
			buffer[i][j] = 0;
	}

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
			{
				int turn = gameWindow->getStroke();
				delete gameWindow;
				if (runningPause() == EXIT)
				{
					msg = "disconnect";
					send(outputconnection, msg.c_str(), BUFFERSIZE, NULL);
					closesocket(outputconnection);
					WSACleanup();
					return EXIT;
				}

				gameWindow = new GameWindow(size, buffer, turn);
				try { gameWindow->Init(); gameWindow->LoadTextures(); }
				catch (const char* error)
				{
					msg = "disconnect";
					send(outputconnection, msg.c_str(), BUFFERSIZE, NULL);
					closesocket(outputconnection);
					WSACleanup();
					// Вывод MessageBox с сообщением об ошибке
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error, NULL);
					return ERROR;
				}
				break;
			}
			case TURNREADY:
			{
				SDL_Point lastmove = gameWindow->getLastMove();
				buffer[lastmove.x][lastmove.y] = FIRSTPLAYER;

				msg = "";
				msg += (lastmove.x + '0');
				msg += ' ';
				msg += (lastmove.y + '0');
				send(outputconnection, msg.c_str(), BUFFERSIZE, NULL);

				if (gameWindow->isWin())
					gameWindow->LoadEndMessage(FPWIN);
				gameWindow->changeStroke();
				break;
			}
			}
		}
		else
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					msg = "disconnect";
					send(outputconnection, msg.c_str(), BUFFERSIZE, NULL);
					closesocket(outputconnection);
					WSACleanup();
					gameWindow->downRunning();
				}
				else if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					int turn = gameWindow->getStroke();
					delete gameWindow;
					gameWindow = nullptr;
					if (runningPause() == EXIT)
					{
						msg = "disconnect";
						send(outputconnection, msg.c_str(), BUFFERSIZE, NULL);
						closesocket(outputconnection);
						WSACleanup();
						return EXIT;
					}

					gameWindow = new GameWindow(size, buffer, turn);
					try { gameWindow->Init(); gameWindow->LoadTextures(); }
					catch (const char* error)
					{
						msg = "disconnect";
						send(outputconnection, msg.c_str(), BUFFERSIZE, NULL);
						closesocket(outputconnection);
						WSACleanup();
						// Вывод MessageBox с сообщением об ошибке
						SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error, NULL);
						return ERROR;
					}
					break;
				}
			}
		}

		msg = "";
		char buf[BUFFERSIZE];
		if (gameWindow->isRunning() && recv(outputconnection, buf, BUFFERSIZE, NULL) != ERROR)
		{
			msg = buf;

			if (msg.find("disconnect") != string::npos)
			{
				gameWindow->LoadEndMessage(FPWIN);
				gameWindow->downRunning();
			}
			else
			{
				SDL_Point coord;
				coord.x = (msg[0] - '0');
				coord.y = (msg[2] - '0');

				gameWindow->setCell(coord.x, coord.y, SECONDPLAYER);
				buffer[coord.x][coord.y] = SECONDPLAYER;
				if (gameWindow->isWin())
					gameWindow->LoadEndMessage(SPWIN);
				gameWindow->changeStroke();
			}
		}

		if (gameWindow->isDraw())
			gameWindow->LoadEndMessage(DRAW);
		gameWindow->Render();
	}
	delete gameWindow;

	closesocket(outputconnection);
	WSACleanup();
	return 0;
}

int Application::runningOffline()
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
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error, NULL);
		return ERROR;
	}
	int firstTurn = gameWindow->getStroke();

	gameWindow->setConnect();
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
					SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error, NULL);
					return ERROR;
				}
				if (gameWindow->getStroke() == SECONDPLAYER)
					gameWindow->changeStroke();
				break;
			case TURNREADY:
			{	
				SDL_Point lastmove = gameWindow->getLastMove();
				buffer[lastmove.x][lastmove.y] = gameWindow->getCell(lastmove.x, lastmove.y);

				if (gameWindow->isWin())
					gameWindow->LoadEndMessage(FPWIN);
				gameWindow->changeStroke();
				break;
			}
			}
		}
		else
		{
			for (int i = 0; i < 100; i++)
			{
				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_QUIT)
					{
						delete gameWindow;
						return EXIT;
					}
					else if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						delete gameWindow;
						if (runningPause() == EXIT)
							return EXIT;

						gameWindow = new GameWindow(size, buffer, firstTurn);
						try { gameWindow->Init(); gameWindow->LoadTextures(); }
						catch (const char* error)
						{
							// Вывод MessageBox с сообщением об ошибке
							SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error, NULL);
							return ERROR;
						}
						if (gameWindow->getStroke() != SECONDPLAYER)
							gameWindow->changeStroke();
					}
				}
				gameWindow->Compute();
				gameWindow->Render();
				SDL_Delay(9);
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
			if (gameWindow->isWin())
				gameWindow->LoadEndMessage(SPWIN);
			gameWindow->changeStroke();
		}

		if (gameWindow->isDraw())
			gameWindow->LoadEndMessage(DRAW);
		gameWindow->Render();
	}
	delete gameWindow;

	return 0;
}