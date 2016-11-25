#define _CRT_SECURE_NO_WARNINGS
#define UTINY_API __declspec(dllexport)

#include "../include/Texture.h"
#include<stdio.h>


Texture::Texture()
{
	
}


Texture::~Texture()
{
}

int Texture::Width()
{
	return width;
}

int Texture::Height()
{
	return height;
}


void Texture::SetPixel(int index, int pixel)
{
	pixelData[index] = pixel;
}

const int * Texture::GetPixel()
{
	return pixelData;
}

Texture * Texture::CreateFromFile(const char * filename)
{
	FILE* fp = fopen(filename, "rb");
	if (!fp)return nullptr;
	int wh[2];
	fread(wh, sizeof(int), 2, fp);
	int w = wh[0];
	int h = wh[1];

	auto tex = Texture::Create(w, h);
	fread(tex->pixelData, sizeof(int), w * h, fp);
	fclose(fp);



	//reverse rows
	for (int r = 0;r < h - r;r++) {
		int temp = 0;
		int* line_up = tex->pixelData + r*w;
		int* line_down = tex->pixelData + (h - r-1)*w;
		for (int c = 0;c < w;c++) {
			temp = line_up[c];
			line_up[c] = line_down[c];
			line_down[c] = temp;
		}
	}

	return tex;
}

Texture * Texture::Create(int width, int height)
{
	Texture* tex = new Texture;
	tex->width = width;
	tex->height = height;
	tex->pixelData = new int[width*height];
	
	//memset(tex->pixelData, 0xffff0000, sizeof(width*height * sizeof(int)));
	
	return tex;
}
