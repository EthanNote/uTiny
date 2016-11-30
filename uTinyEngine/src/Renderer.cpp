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



void PlaneShadowRenderer::SetupCastParameter(Vector3 lightPosition, Vector3 planeNormal, Vector3 planePoint)
{
}

void PlaneShadowRenderer::SetupCastParameter(Vector3 lightPosition)
{
	castMatrix[0] = lightPosition.y;
	castMatrix[1] = 0;
	castMatrix[2] = 0;
	castMatrix[3] = 0;

	castMatrix[4] = -lightPosition.x;
	castMatrix[5] = 0;
	castMatrix[6] = -lightPosition.z;
	castMatrix[7] = 0;

	castMatrix[8] = 0;
	castMatrix[9] = 0;
	castMatrix[10] = lightPosition.y;
	castMatrix[11] = 0;

	castMatrix[12] = 0;
	castMatrix[13] = 0.01;
	castMatrix[14] = 0;
	castMatrix[15] = 1/*lightPosition.y*/;
}

PlaneShadowRenderer::PlaneShadowRenderer()
{
	SetupCastParameter(Vector3::One());
}

void PlaneShadowRenderer::Assign(PlaneShadowRenderer * renderer, GameObject * object)
{
	if (object&&object->GetComponent<Mesh>()) {
		object->AddComponent(renderer);
	}
	auto child = object->GetChildList();
	for (auto i = child.begin();i != child.end();i++) {
		Assign(renderer, i->get());
	}

}
