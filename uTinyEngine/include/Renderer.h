#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Vector3.h"
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

class UTINY_API PlaneShadowRenderer : public Renderer {
	float castMatrix[16];
	virtual void Render() override;
public:
	void SetupCastParameter(Vector3 lightPosition, Vector3 planeNormal, Vector3 planePoint);
	void SetupCastParameter(Vector3 lightPosition);
	PlaneShadowRenderer();
	static void Assign(PlaneShadowRenderer* renderer, GameObject* object);
};