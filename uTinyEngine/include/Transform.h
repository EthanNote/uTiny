#pragma once
#include "Component.h"
#include "Vector3.h"

#ifndef UTINY_API

#define UTINY_API __declspec(dllimport)

#endif

class UTINY_API Transform :
	public Component
{
	//static const ComponentType ClassType = ComponentType::TransformComponent;
	USE_CLASS_INFO
	
public:
	float LocalMatrix[4][4];
	float WorldMatrix[4][4];

	Vector3 translation;
	Vector3 rotation;
	Vector3 scale;

	Vector3 Forward();
	Vector3 Right();
	Vector3 Up();

	void Translate(Vector3 v);
	void Rotate(Vector3 axis, float angle);
	void Scale(Vector3 s);

	virtual std::vector<size_t> RequiredComponents() override;

	Transform World();

	//virtual int Type() override;
	virtual void Update() override;
	Transform();
	~Transform();

	//static void ReverseMatrix(float** src, float dst);
};

