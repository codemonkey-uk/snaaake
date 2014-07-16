
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
        
		Glyph c = {
			"XXX ",
			"X   ",
			"X   ",
			"X   ",
			"XXX ",
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

        Glyph h = {
			"X X ",
			"X X ",
			"XXX ",
			"X X ",
			"X X ",
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
        
		Glyph f = {
			"XXX ",
			"X   ",
			"XXX ",
			"X   ",
			"X   ",
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
		Glyph r = {
			"XXX ",
			"X X ",
			"XX  ",
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
		Glyph m = {
			" X X  ",
			"X X X ",
			"X X X ",
			"X   X ",
			"X   X ",
			"      ",
        };
        Glyph i = {
			"XXX ",
			" X  ",
			" X  ",
			" X  ",
			"XXX ",
			"    ",
		};
        Glyph t = {
			"XXX ",
			" X  ",
			" X  ",
			" X  ",
			" X  ",
			"    ",
		};
        Glyph l = {
			"X   ",
			"X   ",
			"X   ",
			"X   ",
			"XXX ",
			"    ",
		};

        Glyph g = {
            "XXX ",
            "X   ",
            "X X ",
            "X X ",
            "XXX ",
            "    ",
        };
        
        Glyph z = {
            "XXX ",
            "  X ",
            " X  ",
            "X   ",
            "XXX ",
            "    ",
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
			{ 'A', &a },
            { 'B', &GlyphData::nums[8] },
            { 'C', &GlyphData::nums[8] },
			{ 'D', &d },
			{ 'E', &e },
			{ 'F', &f },
			{ 'G', &g },
            { 'H', &h },
            { 'I', &i },
            // J
			{ 'K', &k },
            { 'L', &l },
			{ 'M', &m },
			{ 'N', &n },
            { 'O', &GlyphData::nums[0] },
			{ 'P', &p },
            // Q
            { 'R', &r },
			{ 'S', &nums[5] },
            { 'T', &t },
            { 'U', &u },
            // V
            { 'W', &w },
            // X
            { 'Y', &GlyphData::nums[4] },
            { 'Z', &z },
            // Z
						
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