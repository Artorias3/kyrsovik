#include "Image.h"

// class Image
//

#ifdef _TEXTURES_

bool Image::LoadImage(const char *s, SDL_Renderer *renderer)
{
	SDL_Surface *tmp = IMG_Load(s);
	if (!tmp)
	{
		cout << IMG_GetError() << endl;
		return false;
	}
	if (!(image = SDL_CreateTextureFromSurface(renderer, tmp)))
	{
		cout << SDL_GetError() << endl;
		return false;
	}

	SDL_FreeSurface(tmp);
	return true;
}

#elif defined _SURFACES_

bool Image::LoadImage(const char *s, SDL_Surface *surface)
{
	if (!(image = IMG_Load(s)))
	{
		cout << IMG_GetError() << endl;
		return false;
	}

	return true;
}

#endif

void Image::SetRect(int x, int y, int h, int w)
{
	rect.x = x;
	rect.y = y;
	rect.h = h;
	rect.w = w;
}

#ifdef _TEXTURES_
Image::~Image()
{
	if (image != nullptr)
		SDL_DestroyTexture(image);
	image = nullptr;
}
#elif defined _SURFACES_
Image::~Image() 
{ 
	if (image != nullptr)
		SDL_FreeSurface(image); 
	image = nullptr;
}
#endif

// struct Textures
//

Textures::Textures() : mainfield(nullptr), fpsign(nullptr), spsign(nullptr), smallfpsign(nullptr), smallspsign(nullptr),
bluedot(nullptr), reddot(nullptr), winline(nullptr), winmessage(nullptr)
{
	mainfield = new Image;
	bluedot = new Image;
	reddot = new Image;
	fpsign = new Image;
	spsign = new Image;
	smallfpsign = new Image;
	smallspsign = new Image;
	winline = new Image;
	winmessage = new Image;

	mainfield->SetRect(0, 0, 500, 400);
	bluedot->SetRect(36, 394, 15, 15);
	reddot->SetRect(36, 451, 15, 15);
	fpsign->SetRect(0, 0, 100, 100);
	spsign->SetRect(0, 0, 100, 100);
	smallfpsign->SetRect(255, 381, 39, 39);
	smallspsign->SetRect(255, 438, 39, 39);
	winline->SetRect(0, 0, 0, 0);
	winmessage->SetRect(0, 0, 500, 400);
}