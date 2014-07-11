//==============================================================================
#include "CApp.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>

#include "font.h"

bool CApp::FreeRect(Geometry::Vector2d<int> p, Geometry::Vector2d<int> s)
{
	Geometry::Vector2d<int> d(Geometry::uninitialised);
	for (d[0]=0;d[0]!=s[0];++d[0])
	{
		for (d[1]=0;d[1]!=s[1];++d[1])
		{
			if (*GetPx(p+d))
				return false;
		}
	}
	return true;
}

Geometry::Vector2d<int> CApp::SpawnPoint(Geometry::Vector2d<int> exclude)
{
	const int s=3;
	Geometry::Vector2d<int> result( Geometry::uninitialised );
	do{
		result = { mRNG()%(mHorizontal-s), 1 + mRNG()%(mVertical-(s+8)) };
	}while( !FreeRect( result, {s,s} ) || result.DistanceSquare(exclude)<=(8+s) );
	return result;
}

void CApp::Spawn(Geometry::Vector2d<int> e, int i)
{
	Geometry::Vector2d<int> p = SpawnPoint(e);
	if (i==2)
	{
		*GetPx(p+Geometry::Vector2d<int>(1,0))=i;
		*GetPx(p+Geometry::Vector2d<int>(0,1))=i;	
		*GetPx(p+Geometry::Vector2d<int>(1,1))=i;
		*GetPx(p+Geometry::Vector2d<int>(2,1))=i;
		*GetPx(p+Geometry::Vector2d<int>(1,2))=i;	
	}
	else
	{
		*GetPx(p+Geometry::Vector2d<int>(0,0))=i;
		*GetPx(p+Geometry::Vector2d<int>(0,2))=i;
		*GetPx(p+Geometry::Vector2d<int>(1,1))=i;
		*GetPx(p+Geometry::Vector2d<int>(2,0))=i;
		*GetPx(p+Geometry::Vector2d<int>(2,2))=i;
	}
}

void CApp::PrintString( const char* buffer, int h, int v, HAlign align)	
{
	using namespace Font;
	
	int l=strlen(buffer);
	int x = h;
	if (align==Right) x = h - l*4;
	else if (align==Center) x = h - (l*4)/2;
	for (int i = 0 ; i!=l; ++i)
	{
		x+=Blit(GetGlyph(buffer[i]), x, v, mPixels, mHorizontal, mVertical);
	}
}

void CApp::PrintNumber( int num, int h, int v, HAlign align)	
{
	char buffer[8];
	sprintf(buffer,"%i", num);
	PrintString(buffer, h, v, align);
}

int CApp::Consume( Geometry::Vector2d<int>::BaseType pos )
{
	int result = 0;
	int* p = GetPx( pos );
	if (*p==2)
	{
		*p=0;
		result ++;
		result += Consume( pos + Geometry::Vector2d<int>(1,0) );
		result += Consume( pos + Geometry::Vector2d<int>(0,1) );
		result += Consume( pos + Geometry::Vector2d<int>(-1,0) );
		result += Consume( pos + Geometry::Vector2d<int>(0,-1) );
	}
	return result;
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
			Spawn(mPos.front(),2);
			mPendingGrowth += Consume(pos) * 2;
			mSpawnCooldown = 12;
			mPendingRemove = mPos.front();
		}
		
		*p = 1;
		
		return true;
	}
}

Geometry::Vector2d<int> CApp::Other(
	Geometry::Vector2d<int> pos, 
	Geometry::Vector2d<int> dir
)
{
	Geometry::Vector2d<int> other = pos;
	
	if (dir[1]==0) other[1]++;
	else other[0]++;
	
	return Wrap(other);
}

void CApp::AdvanceTail()
{
	*GetPx( mPos.back() ) = 0;
	mPos.pop_back();
	if (mOther.empty()==false)
	{
		*GetPx( mOther.back() ) = 0;
		mOther.pop_back();
	}
}

Geometry::Vector2d<int> CApp::RemoveSpawn(int c, Geometry::Vector2d<int> near)
{
	Geometry::Vector2d<int> p(0,0), best(0,0);
	bool first = true;
	
    for (p[0]=0;p[0]!=mHorizontal;p[0]++)
    {
	    for (p[1]=1;p[1]!=mVertical-8;p[1]++)
    	{
    		int i = *GetPx( p );
    		if (i==c)
    		{
    			if (std::find(mPos.begin(), mPos.end(), p)==mPos.end())
    			{
					if (std::find(mOther.begin(), mOther.end(), p)==mOther.end())
					{
						if (first || near.Distance(p)<near.Distance(best))
						{
							best=p;
							first=false;
						}
					}
    			}
    		}
    	}
    }
    *GetPx( best ) = 0;
    return best;
}

Geometry::Vector2d<int> CApp::Wrap(const Geometry::Vector2d<int>::BaseType& _p)const
{
	Geometry::Vector2d<int> p(_p);
	if (p[0]>=mHorizontal) p[0] -= mHorizontal;
	if (p[0]<0) p[0] += mHorizontal;
	if (p[1]>=mVertical) p[1] -= mVertical;
	if (p[1]<0) p[1] += mVertical;
	return p;
}

Geometry::Vector2d<int> CApp::Advance(
	const Geometry::Vector2d<int>& p,
	const Geometry::Vector2d<int>::BaseType& d)
{
	Geometry::Vector2d<int> next( p + d );
	return Wrap(next);
}

//==============================================================================
void CApp::OnLoop() 
{
	mLoopCount++;
	
	mScore=std::max(static_cast<int>(mPos.size())-1,mScore);
	
	// clear score area
	std::fill(mPixels+(mHorizontal*(mVertical-7)), mPixels+(mHorizontal*mVertical),0);
	// score area horizontal
	std::fill(mPixels+(mHorizontal*(mVertical-8)), mPixels+(mHorizontal*(mVertical-7)),1);
	// bottom border horizontal
	std::fill(mPixels, mPixels+mHorizontal,1);

	mHighScore=std::max(mScore, mHighScore);

	PrintNumber( mScore, 1, mVertical-2, Left );
	PrintNumber( mHighScore, mHorizontal, mVertical-2, Right );
	
	if (mPaused)
	{
		// all game input events are dropped while paused
		if (!mEvents.empty()) mEvents.pop_front();
		// on screen message during pause
		PrintString( "PAUSED", mHorizontal/2, mVertical-2, Center );		
	}
	else
	{
		PrintString( "SNAAAKE", mHorizontal/2, mVertical-2, Center );		
		mInputLatch.Update();
		if (!mEvents.empty() && !mInputLatch.IsLocked(mEvents.front())) 
		{
			// a change in direction, not reversing direction
			if (mEvents.front()!=-mDir && mEvents.front()!=mDir)
			{
				auto oldDir = mDir;
				mDir = mEvents.front();
			
				// step over thickness
				if (mDir[1]==1 || mDir[0]==1) 
				{
					mPos.push_front( Advance( mPos.front(), mDir ) );
				
					Geometry::Vector2d<int> other = Other(mPos.front(), mDir);
					if (mOther.empty() || other!=mOther.front())
						mOther.push_front( other );
				
					AdvanceTail();
				}
				if (oldDir[1]==1 || oldDir[0]==1) 
				{
					mPos.push_front( Advance( mPos.front(), -oldDir ) );
				
					Geometry::Vector2d<int> other = Other(mPos.front(), mDir);
					if (mOther.empty() || other!=mOther.front())
					{
						if (mOther.empty()==false)
						{
							if (*GetPx(mOther.front())==0)
							{
								mOther.pop_front();
								mOther.push_front( other );
							}
						}
						mOther.push_front( other );
					}
					
					AdvanceTail();
				}
				mInputLatch.Lock(2, -oldDir);
			}
			mEvents.pop_front();
		}
	
		if (mDir.LengthSquare()>0 && !mDiedOnFrame)
		{
			// constantly spawn bad spots
			if (mSpawnCooldown>0)
			{
				mSpawnCooldown--;
			}
			else if (mRNG()%12 == 0)
			{
				Spawn(mPos.front(),1);
				mSpawnCooldown = 12;
			}
		
			Geometry::Vector2d<int> next = Advance( mPos.front(), mDir );
			mPos.push_front( next );
		
			Geometry::Vector2d<int> other = Other(next,mDir);
		
			if (mOther.empty() || other!=mOther.front())
				mOther.push_front( other );
		
			if (!Occupy(next) || !Occupy(other))
			{
				mDiedOnFrame = mLoopCount;
				mDir = {0,0};
			}


			// grow if growing		
			if (mPendingGrowth>0)
			{
				mPendingGrowth--;
				mPendingRemove = RemoveSpawn(1, mPendingRemove);
			}
			else
			{
				// clear up tail
				AdvanceTail();
			}		
		}
		else if (mDiedOnFrame) 
		{
			if (mLoopCount >= mDiedOnFrame+16)
			{
				Reset();
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
}

//==============================================================================
