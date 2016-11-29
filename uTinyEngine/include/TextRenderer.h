#pragma once
#include "Renderer.h"
#include "Font.h"

#include<memory>
#ifndef UTINY_API

#define UTINY_API __declspec(dllimport)

#endif

class UTINY_API TextRenderer :
	public Renderer
{
	std::vector<wchar_t> text;
	std::shared_ptr<Font> font;
public:
	TextRenderer();
	~TextRenderer();
};

