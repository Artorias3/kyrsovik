#include "Application.h"


int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Rus");
	Application mainapp;

	return mainapp.Execute();
}