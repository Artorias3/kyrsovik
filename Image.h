#pragma once

#include <iostream>
#include <ctime>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>

class Image
{
private:
	SDL_Rect rect;
	SDL_Texture *image;
public:
	Image() { image = nullptr; }
	~Image();
	
	bool LoadImage(const char *s, SDL_Renderer *renderer);
	SDL_Texture* GetTexture() { return image; }
	SDL_Rect* GetRect() { return &rect; }
	void SetRect(int x, int y, int h, int w);

	bool isCursorHit(const int x, const int y);
};