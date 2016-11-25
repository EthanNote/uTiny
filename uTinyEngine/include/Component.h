#pragma once
#include <string>
#include <vector>
#define class_name(c) typeid(c).name()
#define class_hashcode(c) typeid(c).hash_code()

#define USE_CLASS_INFO \
virtual std::string classname(){ return typeid(*this).name(); }\
virtual size_t hashcode() { return typeid(*this).hash_code(); }

#ifndef UTINY_API

#define UTINY_API __declspec(dllimport)

#endif

class GameObject;
class UTINY_API Component
{
	
protected:
	GameObject* gameObject;
	std::string name;

	virtual void Update();
	virtual void Start();

	USE_CLASS_INFO
public:
			
	virtual std::vector<size_t> RequiredComponents()=0;
	bool CheckRequirement();

	Component();
	~Component();

	friend class GameObject;

	template<class T>
	static Component* Create();

	template<class T>
	static Component* Create(GameObject* gameObject);
		
};

template<class T>
inline Component * Component::Create()
{
	Component* pcom = new T;

	return pcom;
}

template<class T>
inline Component * Component::Create(GameObject * gameObject)
{
	auto pcom = Component::Create<T>();
	if (pcom != nullptr && gameObject != nullptr)
		gameObject->AddComponent(pcom);
	return pcom;
}
