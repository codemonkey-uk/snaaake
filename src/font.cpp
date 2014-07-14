
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

		Glyph n = {
			"XXX ",
			"X X ",
			"X X ",
			"X X ",
			"X X ",
			"    ",
		};	

		Glyph k = {
			"X X ",
			"XX  ",
			"X   ",
			"XX  ",
			"X X ",
			"    ",
		};	

		Glyph w = {
			"X   X ",
			"X   X ",
			"X X X ",
			"X X X ",
			" X X  ",
			"      ",
		};	
					
		Glyph up = {
			" X  ",
			"XXX ",
			" X  ",
			" X  ",
			" X  ",
			"    ",
		};	
		Glyph down = {
			" X  ",
			" X  ",
			" X  ",
			"XXX ",
			" X  ",
			"    ",
		};	
		Glyph left = {
			"      ",
			" X    ",
			"XXXXX ",
			" X    ",
			"      ",
			"      "
		};	
		Glyph right = {
			"      ",
			"   X  ",
			"XXXXX ",
			"   X  ",
			"      ",
			"      "
		};
		
		Glyph space = {
			"    ",
			"    ",
			"    ",
			"    ",
			"    ",
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
			
			{ 'N', &n },
			{ 'K', &k },
            
            { 'W', &w },
						
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
			
			{ ' ', &space },

			{ '<', &left },
			{ '>', &right },
			{ '^', &up },
			{ '|', &down },
			
			{ 2190, &left },
			{ 2192, &right },
			{ 2191, &up },
			{ 2193, &down },
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