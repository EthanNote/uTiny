#define UTINY_API __declspec(dllexport)

#include "../include/Material.h"
#include "../include/Renderer.h"
#include "../include/GameObject.h"
std::vector<size_t> Material::RequiredComponents() {
	std::vector<size_t> req;
	return req;
}


Material::Material() :
	lighting(true)
{
	UVTransform* t = new UVTransform;
	t->uvOffset[0] = 0;
	t->uvOffset[1] = 0;
	t->uvRotation = 0;
	t->uvScale[0] = 0;
	t->uvScale[1] = 0;
	uvTransform = std::shared_ptr<UVTransform>(t);

}


Material::~Material()
{
}

void Material::AssignMaterial(GameObject * obj, Material * mat, bool replace)
{
	if (obj->GetComponent<Mesh>()) {
		if (!obj->GetComponent<Material>()) {
			obj->AddComponent(mat);
		}
		else if (replace&& mat)
		{
			*obj->GetComponent<Material>() = *mat;
		}
	}
	for (auto c = obj->GetChildList().begin();c != obj->GetChildList().end();c++) {
		AssignMaterial(c->get(), mat, replace);
	}
}
