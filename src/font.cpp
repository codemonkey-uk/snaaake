
#include "font.h"
#include <map>

namespace Font
{
	typedef const char* Glyph[6];

	namespace GlyphData
	{
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
	
		Glyph p = {
			"XXX ",
			"X X ",
			"XXX ",
			"X   ",
			"X   ",
			"    ",
		};
	
		Glyph a = {
			"XXX ",
			"X X ",
			"XXX ",
			"X X ",
			"X X ",
			"    ",
		};	
	
		Glyph u = {
			"X X ",
			"X X ",
			"X X ",
			"X X ",
			"XXX ",
			"    ",
		};	

		Glyph e = {
			"XXX ",
			"X   ",
			"XXX ",
			"X   ",
			"XXX ",
			"    ",
		};	
		
		Glyph d = {
			"XX  ",
			"X X ",
			"X X ",
			"X X ",
			"XX  ",
			"    ",
		};		
		// paused
		std::map< int, Glyph* > fontMap = {
			{ 'P', &p },
			{ 'A', &a },
			{ 'U', &u },
			{ 'S', &nums[5] },
			{ 'E', &e },
			{ 'D', &d },
			
			{ '0', &GlyphData::nums[0] },
			{ '1', &GlyphData::nums[1] },
			{ '2', &GlyphData::nums[2] },
			{ '3', &GlyphData::nums[3] },
			{ '4', &GlyphData::nums[4] },
			{ '5', &GlyphData::nums[5] },													
			{ '6', &GlyphData::nums[6] },
			{ '7', &GlyphData::nums[7] },
			{ '8', &GlyphData::nums[8] },
			{ '9', &GlyphData::nums[9] },			
		};
	}

	const Glyph& GetGlyph(int i)
	{
		return *GlyphData::fontMap[i];
	}
		
	const Glyph& GetDigit(int i)
	{
		return GlyphData::nums[i];
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