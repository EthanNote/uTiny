#pragma once
#include "Input.h"
#include "Scene.h"
#include "Material.h"
#include "Texture.h"

#ifndef UTINY_API

#define UTINY_API __declspec(dllimport)

#endif


class UTINY_API Game
{
public:
	std::unique_ptr<Scene> scene;
	static int Run(Game* game);
	template<class T>
	static int Run();
	Game();
	~Game();
};

template<class T>
inline int Game::Run()
{
	std::unique_ptr<Game> game = new T;
	int r = Run(game.get());
	return r;
}
