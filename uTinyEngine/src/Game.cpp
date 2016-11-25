#define UTINY_API __declspec(dllexport)

#include "../include/Game.h"
#include "../include/GameObject.h"
#include "../include/Transform.h"


Game::Game():
	scene(nullptr)
{
}


Game::~Game()
{
}
