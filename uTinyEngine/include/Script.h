#pragma once
class Transform;
class GameObject;

#ifndef UTINY_API

#define UTINY_API __declspec(dllimport)

#endif

class UTINY_API Script
{
	friend class GameObject;
	GameObject* _gameObject;
	Transform* _transform;
protected:
	GameObject* gameObject();
	Transform* transform();
public:
	virtual void Start();
	virtual void  Update();
	Script();
	~Script();

};

