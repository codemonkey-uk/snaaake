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

Geometry::Vector2d<int> Above( const Geometry::Vector2d<int>& first, Geometry::Vector2d<int> next )
{
	auto d = next - first;
	next += Geometry::Vector2d<int>(d[1], d[0]);
	return next;
}

void CApp::PrintNumber( int num, int h, int v, bool ralign)	
{
	char buffer[8];
	int l=sprintf(buffer,"%i", num);
	int x = 1;
	if (ralign) x = h - l*4;
	for (int i = 0 ; i!=l; ++i)
	{
		x+=Blit(nums[buffer[i]-'0'], x, v, mPixels, mHorizontal, mVertical);
	}
}

// returns true if the snake lives on, false is death
bool CApp::Occupy( Geometry::Vector2d<int> pos )
{
	int* p = GetPx( pos );
	if (*p==1)
	{
		return false;
	}
	else
	{
		if (*p==2)
		{
			// spawn two new good spots
			*GetPx( SpawnPoint(mPos.front()) ) = 2;
			*GetPx( SpawnPoint(mPos.front()) ) = 2;
			mPendingGrowth+=8;
		}
		
		*p = 1;
		
		return true;
	}
}

Geometry::Vector2d<int> Other(Geometry::Vector2d<int> pos, Geometry::Vector2d<int> dir)
{
	Geometry::Vector2d<int> other = pos;
	
	if (dir[1]==0) other[1]++;
	else other[0]++;
	
	return other;
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

	static int best = 0;
	if (score>best) best=score;

	PrintNumber( deadFrame==0 ? score : lastscore, 1, mVertical-2, false );
	PrintNumber( best, mHorizontal, mVertical-2, true );

	static Geometry::VectorN<int,2> latchDir {0,0};
	static int latch = 0;
	if (latch) latch--;
	if (!mEvents.empty() && (latch==0 || mEvents.front()!=latchDir)) 
	{
		// a change in direction, not reversing direction
		if (mEvents.front()!=-mDir && mEvents.front()!=mDir)
		{
			auto oldDir = mDir;
			mDir = mEvents.front();
			// step over thickness
			if (mDir[1]==1 || mDir[0]==1) 
			{
				mPos.push_front( Geometry::Vector2d<int>(mPos.front() + mDir) );
				
				Geometry::Vector2d<int> other = Other(mPos.front(), mDir);
				if (mOther.empty() || other!=mOther.front())
					mOther.push_front( other );
			}
			if (oldDir[1]==1 || oldDir[0]==1) 
			{
				mPos.push_front( Geometry::Vector2d<int>(mPos.front() - oldDir) );
				
				Geometry::Vector2d<int> other = Other(mPos.front(), mDir);
				if (mOther.empty() || other!=mOther.front())
					mOther.push_front( other );				
			}
			latchDir=-oldDir;
			latch=2;
		}
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
		
		Geometry::Vector2d<int> other = Other(next,mDir);
		
		if (mOther.empty() || other!=mOther.front())
			mOther.push_front( other );
		
		if (!Occupy(next) || !Occupy(other))
		{
			lastscore = score;
			score = 0;
			deadFrame = mLoopCount;
			mDir = {0,0};
		}


		// grow if growing		
		if (mPendingGrowth>0)
		{
			mPendingGrowth--;
		}
		else
		{
			// clear up tail
			*GetPx( mPos.back() ) = 0;
			mPos.pop_back();
			if (mOther.empty()==false)
			{
				*GetPx( mOther.back() ) = 0;
				mOther.pop_back();
			}
		}		
	}
	else if (deadFrame) 
	{
		if (mLoopCount >= deadFrame+16)
		{
			if (mPos.size()>0)
			{
				*GetPx( mPos.back() ) = 0;
				if (mLoopCount%2) mPos.pop_back();
				for (int i=0;i!=mPos.size();++i)
					*GetPx( mPos[i] ) = 1;
			}
			if (mOther.size()>0)
			{
				*GetPx( mOther.back() ) = 0;
				if (mLoopCount%2) mOther.pop_back();
				for (int i=0;i!=mOther.size();++i)
					*GetPx( mOther[i] ) = 1;
			}
			
			if (mPos.empty() && mOther.empty())
			{
				Reset();
				deadFrame = 0;
			}
		}
		else 
		{
			for (int i=0;i!=mPos.size();++i)
				*GetPx( mPos[i] ) = mLoopCount%2;
			for (int i=0;i!=mOther.size();++i)
				*GetPx( mOther[i] ) = mLoopCount%2;
		}
	}
}

//==============================================================================
