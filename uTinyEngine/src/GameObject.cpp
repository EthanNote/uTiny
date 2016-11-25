#define UTINY_API __declspec(dllexport)

#include "../include/GameObject.h"
#include "../include/Renderer.h"
#include <iostream>


void GameObject::Start()
{
	for (auto component = components.begin();component != components.end();component++)
		component->get()->Start();
	for (auto child = children.begin();child != children.end();child++)
		child->get()->Start();

	if (script)
		script->Start();
}

void GameObject::Update()
{
	for (auto component = components.begin();component != components.end();component++)
		component->get()->Update();
	for (auto child = children.begin();child != children.end();child++)
		child->get()->Update();

	if (script)
		script->Update();
}

std::list<std::shared_ptr<GameObject>>& GameObject::GetChildList()
{
	return children;
}

std::vector<std::shared_ptr<GameObject>> GameObject::GetChild()
{
	std::vector<std::shared_ptr<GameObject>> ret;
	ret.assign(children.begin(), children.end());
	return ret;
}

std::vector<std::shared_ptr<GameObject>> GameObject::GetChild(std::string name)
{
	std::vector<std::shared_ptr<GameObject>> ret;
	for (auto child = children.begin();child != children.end();child++) {
		if (child->get()->name == name)
			ret.push_back(std::shared_ptr<GameObject>(child->get()));
	}
	return ret;
}

std::list<std::shared_ptr<Component>> GameObject::GetComponents()
{
	return std::list<std::shared_ptr<Component>>(components);
}

GameObject * GameObject::FindChild(std::string name)
{
	for (auto i = children.begin();i != children.end();i++)
		if ((*i)->name == name)
			return (*i).get();
	return nullptr;
}

GameObject * GameObject::FindChildRecursively(std::string name)
{
	for (auto i = children.begin();i != children.end();i++)
		if ((*i)->name == name)
			return (*i).get();
		else {
			auto f = (*i).get()->FindChildRecursively(name);
			if (f != nullptr)
				return f;
		}
	return nullptr;
}

void GameObject::AddComponent(Component * component)
{
	components.push_back(std::shared_ptr<Component>(component));
	component->gameObject = this;
}

void GameObject::AddChild(GameObject * child)
{
	if (child != nullptr)
	{
		children.push_back(std::shared_ptr<GameObject>(child));
		child->parent =std::shared_ptr<GameObject>(this);
	}
}

void GameObject::Dump(GameObject * obj, int level)
{
	for (int i = 0;i < level;i++) 
		std::cout << "  ";
	
	std::cout << "[" << obj->name << "]" << std::endl;
	Transform* t = obj->GetComponent<Transform>();
	

	for (auto com = obj->components.begin();com != obj->components.end();com++) {
		for (int i = 0;i < level;i++) 
			std::cout << "  ";
		std::cout << "  " << com->get()->classname() << std::endl;
	}

	for (auto i = obj->children.begin();i != obj->children.end();i++) {
		Dump(i->get(), level + 1);
	}

}

GameObject::GameObject()
{
	AddComponent(new Transform());
	this->script = nullptr;
}


GameObject::~GameObject()
{
}
