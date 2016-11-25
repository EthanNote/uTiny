#define UTINY_API __declspec(dllexport)

#include "../include/Mesh.h"


//
//int Mesh::Type()
//{
//	return ComponentType::MeshComponent;
//}

int Mesh::GetTriangleCount()
{
	return triangleCount;
}

void * Mesh::GetMeshData()
{
	return meshData;
}

std::vector<size_t> Mesh::RequiredComponents()
{
	return std::vector<size_t>();
}

void Mesh::Update()
{
}

void Mesh::SetMeshData(void* buffer, int triangleCount) {
	meshData = (Triangle*)buffer;
	this->triangleCount = triangleCount;
}

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}
