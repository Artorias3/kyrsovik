#pragma once
#include "Image.h"

typedef struct Textures
{
	Textures();
	~Textures()
	{
		delete mesh;
		delete fpsign;
		delete spsign;
		delete smallfpsign;
		delete smallspsign;
		delete bluedot;
		delete reddot;
		delete winline;
		delete winmessage;
	}

	Image *mesh;
	Image *fpsign;
	Image *spsign;
	Image *smallfpsign;
	Image *smallspsign;
	Image *bluedot;
	Image *reddot;
	Image *winline;
	Image *winmessage;
}Textures;