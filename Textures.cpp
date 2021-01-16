#include "Textures.h"

Textures::Textures()
{
	mesh = nullptr;
	fpsign = nullptr;
	spsign = nullptr;
	smallfpsign = nullptr;
	smallspsign = nullptr;
	bluedot = nullptr;
	reddot = nullptr;
	winline = nullptr; 
	winmessage = nullptr;

	mesh = new Image;
	bluedot = new Image;
	reddot = new Image;
	fpsign = new Image;
	spsign = new Image;
	smallfpsign = new Image;
	smallspsign = new Image;
	winline = new Image;
	winmessage = new Image;

	mesh->SetRect(51, 51, 120, 120);
	bluedot->SetRect(36, 394, 15, 15);
	reddot->SetRect(36, 451, 15, 15);
	fpsign->SetRect(0, 0, 100, 100);
	spsign->SetRect(0, 0, 100, 100);
	smallfpsign->SetRect(255, 381, 39, 39);
	smallspsign->SetRect(255, 438, 39, 39);
	winline->SetRect(0, 0, 0, 0);
	winmessage->SetRect(0, 0, 500, 400);
}