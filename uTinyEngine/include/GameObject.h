#pragma once
#include"Component.h"
#include<memory>
#include<list>
#include<vector>

#include "Transform.h"
#include "Camera.h"
#include "Mesh.h"
#include "Script.h"

#ifndef UTINY_API

#define UTINY_API __declspec(dllimport)

#endif


class UTINY_API GameObject
{
	std::shared_ptr<GameObject> parent;
	std::list<std::shared_ptr<GameObject>> children;
	std::list<std::shared_ptr<Component>> components;
	
	Script* script;
public:
	std::string name;

	void Start();
	void Update();
	std::list<std::shared_ptr<GameObject>>& GetChildList();

	std::vector<std::shared_ptr<GameObject>> GetChild();
	std::vector<std::shared_ptr<GameObject>> GetChild(std::string name);

	template<class T>	
	T* GetComponent();

	std::list<std::shared_ptr<Component>> GetComponents();

	template<class T>	
	void SetScript();

	template<class T>
	T* GetScript();

	GameObject* FindChild(std::string name);
	GameObject* FindChildRecursively(std::string name);
	void AddComponent(Component* component);
	void AddChild(GameObject* child);

	static void Dump(GameObject* obj, int level=0);
	GameObject();
	~GameObject();
};

template<class T>
inline T * GameObject::GetComponent()
{
	for (auto i = components.begin();i != components.end();i++) {
		
		if (i->get()->hashcode() == class_hashcode(T)) {
			return(T*)i->get();
		}
	}
	return NULL;
}

template<class T>
inline void GameObject::SetScript()
{
	Script* s = new T();
	if (s != nullptr)
	{
		script = s;
		s->_transform = this->GetComponent<Transform>();
		s->_gameObject = this;
	}
}

template<class T>
inline T * GameObject::GetScript()
{
	return (T*)script;
}
