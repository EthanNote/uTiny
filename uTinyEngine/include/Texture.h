#pragma once
#include<memory>
#ifndef UTINY_API

#define UTINY_API __declspec(dllimport)

#endif

class UTINY_API Texture
{
	friend class Renderer;
	friend class Material;
	int* pixelData;
	int width;
	int height;	

public:
	/*int xoffset;
	int yoffset;
	int clipWidth;
	int clipHeight;*/
	
	Texture();
	~Texture();
	int Width();
	int Height();

	void SetPixel(int index, int pixel);
	const int* GetPixel();

	static Texture* CreateFromFile(const char* filename);
	static Texture* Create(int width, int height);
};

