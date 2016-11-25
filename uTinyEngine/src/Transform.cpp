#define UTINY_API __declspec(dllexport)

#include "../include/Transform.h"



//int Transform::Type()
//{
//	return ComponentType::TransformComponent;
//}

void Transform::Update()
{
}

Transform::Transform()
	:translation(Vector3::Zero()),
	rotation(Vector3::Zero()),
	scale(Vector3::One())
{
	WorldMatrix[0][0] = 1;
	WorldMatrix[0][1] = 0;
	WorldMatrix[0][2] = 0;
	WorldMatrix[0][3] = 0;

	WorldMatrix[1][0] = 0;
	WorldMatrix[1][1] = 1;
	WorldMatrix[1][2] = 0;
	WorldMatrix[1][3] = 0;

	WorldMatrix[2][0] = 0;
	WorldMatrix[2][1] = 0;
	WorldMatrix[2][2] = 1;
	WorldMatrix[2][3] = 0;

	WorldMatrix[3][0] = 0;
	WorldMatrix[3][1] = 0;
	WorldMatrix[3][2] = 0;
	WorldMatrix[3][3] = 1;
}


Transform::~Transform()
{
}

