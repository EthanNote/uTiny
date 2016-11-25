#define UTINY_API __declspec(dllexport)
#include "../include/Console.h"

Console* Console::current;

Console * Console::Current()
{
	return current;
}

void Console::SetAsCurrent()
{
	current = this;
}

Font * Console::GetFont()
{
	return font;
}

std::list<std::vector<wchar_t>>* Console::GetContent()
{
	return &content;
}

void Console::Resize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Console::WriteLine(const wchar_t * text, int length)
{
	if (length <= 0)
		return;
	if (content.size() <= 0)
	{
		std::vector<wchar_t> line;
		content.push_back(line);		
	}
	
	auto line = content.back();
	int remain = width-line.size();
	if (remain > 0) {
		for (int i = 0;i < remain&&i < length;i++)
			content.back().push_back(text[i]);
		content.push_back(std::vector<wchar_t>());
		WriteLine(text+remain, length-remain);
	}
	else
	{
		content.push_back(std::vector<wchar_t>());
		WriteLine(text, length);
	}


}

void Console::WriteLine(const char * text, int length)
{
	std::vector<wchar_t> line;
	for (int i = 0;i < length;i++) {
		line.push_back(text[i]);
	}
	Console::WriteLine(line.data(), length);
}



void Console::WriteChar(const wchar_t c)
{
	std::vector<wchar_t> tail = content.back();
	if (tail.size() <= width)
		tail.push_back(c);
	else {
		content.push_back(std::vector<wchar_t>());
		WriteChar(c);
	}
}

void Console::Clear()
{
	content.clear();
}

int Console::Width()
{
	return width;
}

int Console::Height()
{
	return height;
}

Console::Console()
{
	font = Font::Create();
	Resize(32, 24);
}


Console::~Console()
{
}
