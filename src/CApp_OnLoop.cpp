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

Geometry::Vector2d<int> CApp::SpawnPoint(Geometry::Vector2d<int> exclude)
{
	Geometry::Vector2d<int> result( Geometry::uninitialised );
	do{
		result = { mRNG()%mHorizontal, mRNG()%(mVertical-8) };
	}while( *GetPx( result ) || result.DistanceSquare(exclude)<6 );
	return result;
}

//==============================================================================
void CApp::OnLoop() 
{
	static int lastscore=1;
	static int deadFrame = 0;

	mLoopCount++;
	
	int score=mPos.size();
	
	// clear score area
	std::fill(mPixels+(mHorizontal*(mVertical-7)), mPixels+(mHorizontal*mVertical),0);
	// score area horizontal
	std::fill(mPixels+(mHorizontal*(mVertical-8)), mPixels+(mHorizontal*(mVertical-7)),1);
	// bottom border horizontal
	std::fill(mPixels, mPixels+mHorizontal,1);

	char buffer[8];
	int l=sprintf(buffer,"%i", deadFrame==0 ? score : lastscore);
	int x=1;	
	for (int i = 0 ; i!=l; ++i)
	{
		x+=Blit(nums[buffer[i]-'0'], x, mVertical-2, mPixels, mHorizontal, mVertical);
	}

	static int best = 0;
	if (score>best) best=score;
	l=sprintf(buffer,"%i", best);
	x=mHorizontal - l*4;
	for (int i = 0 ; i!=l; ++i)
	{
		x+=Blit(nums[buffer[i]-'0'], x, mVertical-2, mPixels, mHorizontal, mVertical);
	}
		
	if (!mEvents.empty()) 
	{
		if (mEvents.front() != -mDir)
			mDir = mEvents.front();
		mEvents.pop_front();
	}
	
	if (mDir.LengthSquare()>0 && !deadFrame)
	{
		// constantly spawn bad spots
		if (mRNG()%10 == 0)
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
			deadFrame = mLoopCount;
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
				// spawn two new good spots
				*GetPx( SpawnPoint(mPos.front()) ) = 2;
				*GetPx( SpawnPoint(mPos.front()) ) = 2;
			}
			
			*p = 1;
		}
	}
	else if (deadFrame) 
	{
		if (mLoopCount >= deadFrame+16)
		{
			if (mPos.size()>1)
			{
				*GetPx( mPos.back() ) = 0;
				if (mLoopCount%2) mPos.pop_back();
				for (int i=0;i!=mPos.size();++i)
					*GetPx( mPos[i] ) = 1;
			}
			else 
			{
				Reset();
				deadFrame = 0;
			}
		}
		else 
		{
			for (int i=0;i!=mPos.size();++i)
				*GetPx( mPos[i] ) = mLoopCount%2;
		}
	}
}

//==============================================================================
