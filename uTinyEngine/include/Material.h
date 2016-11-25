#pragma once
#include "Component.h"
#include "Texture.h"
#include<vector>
#include<map>
#include<memory>

#ifndef UTINY_API

#define UTINY_API __declspec(dllimport)

#endif

typedef struct UVTransform {
	float uvOffset[2];
	float uvScale[2];
	float uvRotation;
}UVTransform;

class UTINY_API Material :
	public Component
{
	std::vector<size_t> Material::RequiredComponents() override;
	USE_CLASS_INFO
public:
	//void Update() override;
	//void Apply();

	bool lighting;

	std::vector<std::shared_ptr<Texture>> texture;
	std::shared_ptr<UVTransform> uvTransform;
	std::map<std::string, float[]> parameters;
	Material();
	~Material();

	static void AssignMaterial(GameObject* obj, Material* mat, bool replace = false);
};

