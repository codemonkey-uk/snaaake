//==============================================================================
#include "CApp.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
typedef const char* glyph[6];

glyph nums[10] = {
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

Geometry::Vector2d<int> CApp::SpawnPoint(Geometry::Vector2d<int> exclude)const
{
	Geometry::Vector2d<int> result( Geometry::uninitialised );
	do{
		result = { rand()%mHorizontal, (rand()>>4)%mVertical };
	}while( *GetPx( result ) || result.DistanceSquare(exclude)<4 );
	return result;
}

//==============================================================================
void CApp::OnLoop() 
{
	static int lastscore=0;
	static bool dead = false;
	
	int score=mPos.size();
	
	char buffer[8];
	int l=sprintf(buffer,"%i", mDir.LengthSquare() ? score : lastscore);
	int x=1;
	for (int i = 0 ; i!=l; ++i)
	{
		x+=Blit(nums[buffer[i]-'0'], x, mVertical-2, mPixels, mHorizontal, mVertical);
	}
	
	if (mDir.LengthSquare()>0 && !dead)
	{
		// constantly spawn bad spots
		if (rand()%10 == 0)
			*GetPx( SpawnPoint(mPos.front()) ) = 1;
		
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
			dead = true;
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
				*GetPx( SpawnPoint(mPos.front()) ) = 2;
				*GetPx( SpawnPoint(mPos.front()) ) = 2;
			}
			
			*p = 1;
		}
	}
	else if (mPos.size()>1)
	{
		*GetPx( mPos.back() ) = 0;
		mPos.pop_back();
	}
	else if (dead)
	{
		Reset();
		dead = false;
	}

}

//==============================================================================
