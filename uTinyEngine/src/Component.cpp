#define UTINY_API __declspec(dllexport)

#include "../include/Component.h"
#include "../include/GameObject.h"

void Component::Update()
{
}

void Component::Start()
{
}

bool Component::CheckRequirement()
{
	auto r = this->RequiredComponents();
	auto l = gameObject->GetComponents();
	for (auto i = r.begin();i != r.end();i++) {
		auto find = false;
		for (auto j = l.begin();j != l.end();j++) {
			if (j->get()->hashcode() == *i)			{
				find = true;
				break;
			}
		}
		if (!find)
			return false;
	}
	return true;
}

Component::Component()
{
}


Component::~Component()
{
}
