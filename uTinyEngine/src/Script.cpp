#define UTINY_API __declspec(dllexport)

#include "../include/Script.h"



GameObject * Script::gameObject()
{
	return _gameObject;
}

Transform * Script::transform()
{
	return _transform;
}

void Script::Start()
{
}

void Script::Update()
{
}

Script::Script()
{
}


Script::~Script()
{
}
