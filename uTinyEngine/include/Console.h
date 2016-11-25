#pragma once
#include<vector>
#include<list>

#include"Font.h"

#ifndef UTINY_API

#define UTINY_API __declspec(dllimport)

#endif

class UTINY_API Console
{
	static Console* current;
	std::list< std::vector<wchar_t> > content;
	int width;
	int height;

	Font* font;
public:
	static Console* Current();
	void SetAsCurrent();
	Font* GetFont();
	std::list< std::vector<wchar_t>>* GetContent();
	void Resize(int width, int height);
	void WriteLine(const wchar_t* text, int length);
	void WriteLine(const char* text, int length);
	void WriteChar(const wchar_t c);

	void Clear();

	int Width();
	int Height();

	Console();
	~Console();
};

