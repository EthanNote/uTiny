#pragma once

#include "Component.h"

#ifndef UTINY_API

#define UTINY_API __declspec(dllimport)

#endif

typedef struct VertexFormat {
	union {
		struct {
			float x, y, z;
		};
		float Position[3];
	};
	union {
		struct {
			float nx, ny, nz;
		};
		float Normal[3];
	};
	union {
		struct {
			float u, v;
		};
		float UV[2];
	};
}VertexFormat;

typedef struct Triangle {
	union {
		struct {
			VertexFormat A;
			VertexFormat B;
			VertexFormat C;
		};
		VertexFormat V[3];
	};
}Triangle;

class UTINY_API Mesh :
	public Component
{

	Triangle* meshData;
	int triangleCount;
	//static const ComponentType ClassType = ComponentType::MeshComponent;
	USE_CLASS_INFO
		
public:
	void SetMeshData(void* buffer, int triangleCount);
	int GetTriangleCount();
	void* GetMeshData();
	//virtual int Type() override;
	std::vector<size_t> RequiredComponents() override;
	virtual void Update() override;
	Mesh();
	~Mesh();

	static Mesh* Quad(float width=1, float height=1);
	static Mesh* Cube(float size=1);
};

