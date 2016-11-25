#define UTINY_API __declspec(dllexport)

#include "../include/Transform.h"
#include "../include/Renderer.h"
#include "../include/Mesh.h"

std::vector<size_t> Renderer::RequiredComponents() {
	std::vector<size_t> req;
	req.push_back(class_hashcode(Transform));
	req.push_back(class_hashcode(Mesh));
	return req;
}

void Renderer::Update()
{
	Render();
}


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}


