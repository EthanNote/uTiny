#pragma once
#include "GameObject.h"

#ifndef UTINY_API

#define UTINY_API __declspec(dllimport)

#endif

class UTINY_API Scene :public GameObject
{
	friend class Game;
public:
	Scene();
	~Scene();
	int LoadModel(const char* filename, GameObject* parent=NULL);
};

