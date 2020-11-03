#pragma once

#include <iostream>
#include <ctime>
using namespace std;

#include <SDL.h>
#include <SDL_image.h>

#define _TEXTURES_

#ifdef _TEXTURES_

class Image
{
private:
	SDL_Rect rect;
	SDL_Texture *image;
public:
	Image() : image(nullptr) {}
	~Image();
	
	bool LoadImage(const char *s, SDL_Renderer *renderer);
	SDL_Texture* GetTexture() { return image; }
	SDL_Rect* GetRect() { return &rect; }
	void SetRect(int x, int y, int h, int w);
};

#elif defined _SURFACES_

class Image
{
private:
	SDL_Rect rect;
	SDL_Surface *image;
public:
	Image() : image(nullptr) {}
	~Image();

	bool LoadImage(const char *s, SDL_Surface *surface);
	SDL_Surface* GetTexture() { return image; }
	SDL_Rect* GetRect() { return &rect; }
	void SetRect(int x, int y, int h, int w);
};

#endif
typedef struct Textures
{
	Textures();
	~Textures()
	{
		delete mainfield;
		delete fpsign;
		delete spsign;
		delete smallfpsign;
		delete smallspsign;
		delete bluedot;
		delete reddot;
		delete winline;
		delete winmessage;
	}

	Image *mainfield;
	Image *fpsign;
	Image *spsign;
	Image *smallfpsign;
	Image *smallspsign;
	Image *bluedot;
	Image *reddot;
	Image *winline;
	Image *winmessage;
}Textures;