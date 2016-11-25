#pragma once
#include<vector>
#include "Component.h"
#include "Transform.h"

#ifndef UTINY_API

#define UTINY_API __declspec(dllimport)

#endif

class UTINY_API Camera :
	public Component
{
	
	static Camera* MainCamera;
	Transform* skyTransform;
	USE_CLASS_INFO
public:
	static Camera* Main();
	Transform* transform();
	std::vector<size_t> RequiredComponents() override;
	virtual void Update() override;
	void SetAsMainCamera();
	void SetSkyObject(GameObject* pobj);
	float aspectRatio;
	float fieldOfView;
	float nearDistance;
	float farDistance;

	Camera();
	~Camera();
};

