//==============================================================================
#include "CApp.h"
#include <algorithm>
#include <cstdio>

typedef const char* glyph[6];

glyph nums[10] = {
{
	" XX ",
	"X  X ",
	"X  X ",
	"X  X ",
	"X  X ",
	" XX ",
},
{
	" X  ",
	"XX  ",
	" X  ",
	" X  ",
	" X  ",
	"XXX ",
}, {
	" XX ",
	"X  X ",
	"   X ",
	" XX ",
	"X   ",
	"XXXX ",
}, {
	"XXX ",
	"   X ",
	"XXX ",
	"   X ",
	"   X ",
	"XXX ",
}, {
	"X   ",
	"X   ",
	"X X ",
	"XXXX ",
	"  X ",
	"  X ",
}, {
	"XXXX ",
	"X  X ",
	"X   ",
	"XXXX ",
	"   X ",
	"XXXX ",
}, {
	" XX ",
	"X  X ",
	"X   ",
	"XXX ",
	"X  X ",
	" XX ",
}, {
	"XXXX ",
	"   X ",
	"  X ",
	" X  ",
	" X  ",
	" X  ",
}, {
	" XX ",
	"X  X ",
	"X  X ",
	" XX ",
	"X  X ",
	" XX ",
}, {
	" XXX ",
	"X  X ",
	" XXX ",
	"   X ",
	"   X ",
	"   X ",
}};

int Blit(const glyph& g, int x, int y, int* pixels, int w, int h) 
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

//==============================================================================
void CApp::OnLoop() 
{
	static int lastscore=0;
	static int score=0;
	
	char buffer[8];
	int l=sprintf(buffer,"%i",score>0 ? score : lastscore);
	int x=1;
	for (int i = 0 ; i!=l; ++i)
	{
		x+=Blit(nums[buffer[i]-'0'], x, mVertical-2, mPixels, mHorizontal, mVertical);
	}
	
	if (mDir.LengthSquare()>0)
	{
		if (score==0)
		{
			std::fill(mPixels, mPixels+(mHorizontal*mVertical),0);
		}
		
		mPos += mDir;
		if (mPos[0]>=mHorizontal) mPos[0] -= mHorizontal;
		if (mPos[0]<0) mPos[0] += mHorizontal;
		if (mPos[1]>=mVertical) mPos[1] -= mVertical;
		if (mPos[1]<0) mPos[1] += mVertical;

		int* p = GetPx(mPos);
		if (*p)
		{
			lastscore = score;
			score = 0;
			mDir = {0,0};
		}
		else
		{
			*p = 1;
			score ++;
		}
	}
	
	/*
    for (int x=0;x!=mHorizontal;x++)
    {
	    for (int y=0;y!=mVertical;y++)
    	{
    		
    	}
    }
    */
}

//==============================================================================
