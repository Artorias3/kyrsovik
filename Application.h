#pragma once
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

#include <winsock2.h>
#include <string>
using namespace std;

#include "GameWindow.h"
#include "MenuWindow.h"

#define ERROR (-1)
#define BUFFERSIZE 15
#define OUTPUTADDRESS "127.0.0.1"

class Application
{
private:
	int gameType;
	int size;
	int **buffer;
public:
	Application() { gameType = 0; size = 3; buffer = nullptr; }
	~Application() { if (buffer != nullptr) { for (int i = 0; i < size; i++) delete[] buffer[i]; delete[] buffer; } }

	int Execute();

	int runningMenu();
	int runningOptions();
	int runningPause();
	int runningHostOrClientMenu();
	int runningOnlineAsHost();
	int runningOnlineAsClient();
	int runningOffline();
};