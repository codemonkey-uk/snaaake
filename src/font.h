// font.h

#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

namespace Font
{
	typedef const char* Glyph[6];
	int Blit(const Glyph& g, int x, int y, int* pixels, int w, int h);
	const Glyph& GetGlyph(int i);
	const Glyph& GetDigit(int i);
}

#endif // FONT_H_INCLUDED