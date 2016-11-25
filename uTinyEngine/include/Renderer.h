#pragma once
#include "Component.h"

#ifndef UTINY_API

#define UTINY_API __declspec(dllimport)

#endif

class UTINY_API Renderer :
	public Component
{
	
	USE_CLASS_INFO
public:
	std::vector<size_t> RequiredComponents() override;
	virtual void Render();
	void Update() override;
	Renderer();
	~Renderer();
};

class UTINY_API GridRenderer :public Renderer {
	virtual void Render() override;
};