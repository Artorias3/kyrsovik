#include "Image.h"

bool Image::LoadImage(const char *s, SDL_Renderer *renderer)
{
	if (image != nullptr)
		SDL_DestroyTexture(image);
	image = nullptr;

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

void Image::SetRect(int x, int y, int h, int w)
{
	rect.x = x;
	rect.y = y;
	rect.h = h;
	rect.w = w;
}

Image::~Image()
{
	if (image != nullptr)
		SDL_DestroyTexture(image);
	image = nullptr;
}

bool Image::isCursorHit(const int x, const int y)
{
	if (x > rect.x && y > rect.y && x < rect.x + rect.w && y < rect.y + rect.h)
		return true;
	else
		return false;
}