#pragma once
#include<map>
#include"Texture.h"

class Font
{
	std::map<wchar_t, Texture*> cache;
	void* face;
public:
	Texture* RenderChar(wchar_t unicode);
	static Font* Create();
	
};

