//==============================================================================
#include "CApp.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
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
	int score=mPos.size();
	
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
		
		Geometry::Vector2d<int> next( mPos.front() + mDir );
		if (next[0]>=mHorizontal) next[0] -= mHorizontal;
		if (next[0]<0) next[0] += mHorizontal;
		if (next[1]>=mVertical) next[1] -= mVertical;
		if (next[1]<0) next[1] += mVertical;
		mPos.push_front( next );
		
		int* p = GetPx( mPos.front() );
		if (*p==1)
		{
			lastscore = score;
			score = 0;
			mDir = {0,0};
		}
		else
		{
			if (*p==0)
			{
				*GetPx( mPos.back() ) = 0;
				mPos.pop_back();
			}
			else
			{
				Geometry::Vector2d<int> prize( Geometry::uninitialised );
				do{
					prize = {rand()%mHorizontal, rand()%mVertical};
				}while( *GetPx( prize ) );
				*GetPx( prize ) = 2;
			}
			
			*p = 1;
		}
	}

}

//==============================================================================
