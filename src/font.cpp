
#include "font.h"

namespace Font
{
	typedef const char* Glyph[6];

	Glyph nums[10] = {
	{
		"XXX ",
		"X X ",
		"X X ",
		"X X ",
		"XXX ",
		"    ",
	},
	{
		" X  ",
		"XX  ",
		" X  ",
		" X  ",
		"XXX ",
		"    ",
	}, {
		"XXX ",
		"  X ",
		"XXX ",
		"X   ",
		"XXX ",
		"    ",
	}, {
		"XXX ",
		"  X ",
		"XXX ",
		"  X ",
		"XXX ",
		"    ",
	}, {
		"X X ",
		"X X ",
		"XXX ",
		"  X ",
		"  X ",
		"    ",
	}, {
		"XXX ",
		"X   ",
		"XXX ",
		"  X ",
		"XXX ",
		"    ",
	}, {
		"XXX ",
		"X   ",
		"XXX ",
		"X X ",
		"XXX ",
		"    ",
	}, {
		"XXX ",
		"  X ",
		"  X ",
		"  X ",
		"  X ",
		"    ",
	}, {
		"XXX ",
		"X X ",
		"XXX ",
		"X X ",
		"XXX ",
		"    ",
	}, {
		"XXX ",
		"X X ",
		"XXX ",
		"  X ",
		"  X ",
		"    ",
	}};
	
	const Glyph& GetDigit(int i)
	{
		return nums[i];
	}
	
	int Blit(const Glyph& g, int x, int y, int* pixels, int w, int h) 
	{
		int mw=0;
		for (int l=0;l!=6;++l)
		{
			int* p = (pixels + x + (y-l)*w);
			const char* c = g[l];
			int w = 0;
			while(*c) 
			{
				*p = *c == ' ' ? 0 : 1;
				c++;
				p++;
				w++;
			}
			if (w>mw) mw=w;
		}
		return mw;
	}
}