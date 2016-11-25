#define UTINY_API __declspec(dllexport)
#include<iostream>
#include "../include/Camera.h"
#include "../include/Transform.h"
#include "../include/GameObject.h"
#include "../include/Time.h"
Camera* Camera::MainCamera;
Camera * Camera::Main()
{
	return Camera::MainCamera;
}

//int Camera::Type()
//{
//	return ComponentType::CameraComponent;
//}

Transform * Camera::transform()
{
	if (!gameObject)
		return nullptr;
	return gameObject->GetComponent<Transform>();
}

std::vector<size_t> Camera::RequiredComponents()
{
	std::vector<size_t> req;
	req.push_back(class_hashcode(Transform));
	return req;
}

void Camera::Update()
{
	Transform* self = transform();
	if (self&&skyTransform)
	{
		auto mat = self->WorldMatrix;
		skyTransform->translation = Vector3(mat[3][0], mat[3][1], mat[3][2]);
		skyTransform->Rotate(Vector3::Up(), Time::DeltaTime()*2);
	}
}

void Camera::SetAsMainCamera()
{
	Camera::MainCamera = this;
}

void Camera::SetSkyObject(GameObject * pobj)
{
	if (pobj)
		skyTransform = pobj->GetComponent<Transform>();
	else
		skyTransform = nullptr;
}

Camera::Camera()
{
	fieldOfView = 60;
	aspectRatio = 1.333333f;
	nearDistance = 0.1f;
	farDistance = 100.0f;

	skyTransform = nullptr;
}


Camera::~Camera()
{
}
