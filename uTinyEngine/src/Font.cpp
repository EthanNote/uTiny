#include "../include/Font.h"
#include<ft2build.h>
#include<freetype\freetype.h>
#pragma comment(lib, "freetype27.lib")

Texture * Font::RenderChar(wchar_t unicode)
{
	Texture* cachedTex = cache[unicode];
	if (cachedTex)
		return cachedTex;
	FT_UInt  glyph_index;
	FT_Face face = (FT_Face)this->face;

	glyph_index = FT_Get_Char_Index(face, unicode);
	FT_Error error = 0;

	error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
	if (error) {
		//
	}

	error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
	if (error) {
		//
	}

	unsigned char* b = face->glyph->bitmap.buffer;
	int w = face->glyph->bitmap.width;
	int h = face->glyph->bitmap.rows;

	
	int outWidth = face->glyph->metrics.horiAdvance / 64;
	int outHeight = outWidth * 3;
	int boxOffsetX = face->glyph->metrics.horiBearingX / 64;
	int boxOffsetY = outWidth * 2 - face->glyph->metrics.horiBearingY / 64;

	Texture* tex = Texture::Create(outWidth, outHeight);
	for (int i = 0;i < outWidth*outHeight;i++) {
		tex->SetPixel(i, 0);
	}



	for (int i = 0;i < h;i++) {
		for (int j = 0;j < w;j++) {
			unsigned int byte = face->glyph->bitmap.buffer[i*w + j] & 0x000000ff;
			unsigned int value = byte << 24 | 0x0088ff88;
			tex->SetPixel((i + boxOffsetY)*outWidth + j + boxOffsetX, value);
		}
	}

	cache[unicode] = tex;

	return tex;
}

FT_Library library = 0;

Font * Font::Create()
{

	if (!library)
		FT_Init_FreeType(&library);
	Font* pFont = new Font;
	pFont->face = 0;
	FT_Error error = 0;
	error = FT_New_Face(library, "C:/freetype/consola.ttf", 0, (FT_Face*)&pFont->face);

	if (error) { delete pFont; return nullptr; }

	error = FT_Set_Pixel_Sizes(
		(FT_Face)pFont->face,   /* handle to face object */
		48,      /* pixel_width           */
		0);    /* pixel_height          */

	if (error) { delete pFont; return nullptr; }

	return pFont;
}

