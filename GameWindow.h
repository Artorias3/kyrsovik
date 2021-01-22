#pragma once
#include "Window.h"

#define FREE 0
#define FIRSTPLAYER 1
#define SECONDPLAYER 2
#define TURNREADY 3
#define ESCAPE 4
#define FPWIN 5
#define SPWIN 6
#define DRAW 7


class GameWindow : public Window
{
private:
	Image ***mesh;
	Image *fpsign;
	Image *spsign;
	Image *smallfpsign;
	Image *smallspsign;
	Image *bluedot;
	Image *reddot;
	Image *player;
	Image *enemy;
	Image *endmessage;

	int **cells;
	int stroke;
	int size;
public:
	GameWindow(int _size);
	GameWindow(int _size, int **_cells, int _stroke);
	~GameWindow();

	void LoadTextures();
	void LoadEndMessage(int type);

	int Compute();
	void Render();

	void setCell(int i, int j, int sign) { if (cells[i][j] == FREE) cells[i][j] = sign; }
	int getCell(int i, int j) { return cells[i][j]; }
	int getStroke() { return stroke; }
	void changeStroke();

	bool isWin();
	bool isDraw();
};