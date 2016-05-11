#include "snaaake.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>

#include <stdio.h>
#include <stdlib.h>

extern "C" int GetLocalHighScore();
extern "C" void SetLocalHighScore(int d);

SnakeApp::SnakeApp()
	// set up in ::Init
	: mDir( Geometry::uninitialised )
	, mPendingRemove( Geometry::uninitialised )
	, mPaused(false)
    , mSnakeController(new SnakePlayerController())
{
}

static CApp::Point sa( Geometry::uninitialised ),sb( Geometry::uninitialised );

void SnakeApp::Reset() 
{
	mPos.erase(mPos.begin(), mPos.end());
	mOther.erase(mOther.begin(), mOther.end());
	
	Geometry::Vector2d<int> pos = { mHorizontal/2, (mVertical-8)/2 };
	mPos.push_back(pos);
	
	Clear(0);
	*GetPx(pos) = 1;

	PrintString( "W\n^", mHorizontal/2 +1, 3*(mVertical-8)/4 +7, Center );
	PrintString( "|\nS", mHorizontal/2 +1, 1*(mVertical-8)/4 +4, Center );
	PrintString( "A<", mHorizontal/2 -4, (mVertical-8)/2 +2, Right );
	PrintString( ">D", mHorizontal/2 +6, (mVertical-8)/2 +2, Left );
	
	sa = SpawnPoint();		
	Spawn(sa, 2);
	
	sb = SpawnPoint();
	Spawn(sb, 2);
		
	mPendingGrowth = 1;
	mSpawnCooldown = 12;
	mDir[0] = 0;
	mDir[1] = 0;
	
	mScore = 0;
	mDiedOnFrame = 0;
	
    mAttract = false;
    if (mSnakeController) delete mSnakeController;
    mSnakeController = new SnakePlayerController();
    
    mLastKeyDown = mLoopCount;
}

bool SnakeApp::OnInit()
{
 	printf("SNAAAKE by @codemonkey_uk\nControls: WASD or Arrow Keys.\nSpace to Pause.\n");
    bool result = Base::OnInit();
    if (result)
    {
    	Reset();
        mHighScore=GetLocalHighScore();
    }
    return result;
}

void SnakeApp::OnEvent(SDL_Event* Event)
{
	Base::OnEvent(Event);
    
    mSnakeController->OnEvent(Event);
    
	if (Event->type==SDL_KEYDOWN)
    {
        mLastKeyDown = mLoopCount;
    	switch (Event->key.keysym.sym)
    	{
			case SDLK_SPACE:
				mPaused = !mPaused;
				break;
			default:
                if (mAttract) Reset();
				break;
		}
    }
}

bool SnakeApp::FreeRect(Point p, Point s)const
{
	Point d(Geometry::uninitialised);
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

int SnakeApp::SpawnDistance(Point p)const
{
	// spawns are 3x3 and p is on the 0,0,
	// so measure distance from centre of spawn
	p += {1,1};
	int r = p.ManhattenDistance(mPos.front());
	if (mOther.empty()==false)
		r = std::min(r, p.ManhattenDistance(mOther.front()));
	return r;
}

CApp::Point SnakeApp::SpawnPoint()
{
	// 3x3 spawns, plus 1px space around
	const int s=3+2;
	Point result( Geometry::uninitialised );
	do{
		int x = mRNG()%(mHorizontal-s);
		int y = 1 + mRNG()%(mVertical-(s+8));
		result = { x, y };
	}while( !FreeRect( result, {s,s} ) || SpawnDistance(result)<=(16+s) );
	result += {1,1};
	return result;
}

void SnakeApp::Spawn(int i)
{
	Spawn( SpawnPoint(), i );
}

void SnakeApp::Spawn(const Point& p, int i)
{
	if (i==2)
	{
		*GetPx(p+Point(1,0))=i;
		*GetPx(p+Point(0,1))=i;	
		*GetPx(p+Point(1,1))=i;
		*GetPx(p+Point(2,1))=i;
		*GetPx(p+Point(1,2))=i;	
	}
	else
	{
		*GetPx(p+Point(0,0))=i;
		*GetPx(p+Point(0,2))=i;
		*GetPx(p+Point(1,1))=i;
		*GetPx(p+Point(2,0))=i;
		*GetPx(p+Point(2,2))=i;
	}
}

int SnakeApp::Consume( Point::BaseType pos )
{
	int result = 0;
	int* p = GetPx( pos );
	if (*p==2)
	{
		*p=0;
		result ++;
		result += Consume( pos + Point(1,0) );
		result += Consume( pos + Point(0,1) );
		result += Consume( pos + Point(-1,0) );
		result += Consume( pos + Point(0,-1) );
	}
	return result;
}

// returns true if the snake lives on, false is death
bool SnakeApp::Occupy( Point pos )
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
			Spawn(2);
			mPendingGrowth += Consume(pos) * 2;
			mSpawnCooldown = 12;
			mPendingRemove = mPos.front();
		}
		
		*p = 1;
		
		return true;
	}
}

CApp::Point SnakeApp::Other(
	Point pos, 
	Point dir
) const
{
	Point other = pos;
	
	if (dir[1]==0) other[1]++;
	else other[0]++;
	
	return Wrap(other);
}

void SnakeApp::AdvanceTail()
{
	*GetPx( mPos.back() ) = 0;
	mPos.pop_back();
	if (mOther.empty()==false)
	{
		*GetPx( mOther.back() ) = 0;
		mOther.pop_back();
	}
}

CApp::Point SnakeApp::RemoveSpawn(int c, Point near)
{
	Point p(0,0), best(0,0);
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
						if (first || near.ManhattenDistance(p)<near.ManhattenDistance(best))
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

CApp::Point SnakeApp::Wrap(const Point::BaseType& _p)const
{
	Point p(_p);
	if (p[0]>=mHorizontal) p[0] -= mHorizontal;
	if (p[0]<0) p[0] += mHorizontal;
	if (p[1]>=mVertical) p[1] -= mVertical;
	if (p[1]<0) p[1] += mVertical;
	return p;
}

CApp::Point SnakeApp::Advance(
	const Point& p,
	const Point::BaseType& d) const
{
	Point next( p + d );
	return Wrap(next);
}

const char * GetMsg(bool paused, bool demo, int score)
{
    if (paused)
        return "PAUSED";
        
	if (score>=10 && score<21)
		return "YES";
	else if (score>=41 && score<61)
		return "KEEP GOING";
    else if (score>=81 && score<101)
		return "GOOD";
    else if (score>=181 && score<241)
		return "GREAT";
    else if (score>=281 && score<341)
		return "BRILLIANT";
    else if (score>=381)
        return "AMAZING";
    
    if (demo)
        return "DEMO";
    
	return "SNAAAKE";
}

//==============================================================================
void SnakeApp::OnLoop() 
{
	mLoopCount++;
		
	// clear score area
	ClearRows(mVertical-7, mVertical, 0);
	
    mSnakeController->Update(this);
    
	if (mPaused==false)
    {
		if (!mDiedOnFrame)
		{
            auto newDir = mSnakeController->GetDirection(mDir);
			// a change in direction, not reversing direction
			if (newDir!=-mDir && newDir!=mDir)
			{
				auto oldDir = mDir;
				mDir = newDir;
			
				// step over thickness
				if (mDir[1]==1 || mDir[0]==1) 
				{
					mPos.push_front( Advance( mPos.front(), mDir ) );
				
					Point other = Other(mPos.front(), mDir);
					if (mOther.empty() || other!=mOther.front())
						mOther.push_front( other );
				
					AdvanceTail();
				}
				if (oldDir[1]==1 || oldDir[0]==1) 
				{
					mPos.push_front( Advance( mPos.front(), -oldDir ) );
				
					Point other = Other(mPos.front(), mDir);
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
				
				// game start!
				if (oldDir.LengthSquare()==0) 
				{
					// clear instructions & redrawn spawns
					Clear(0);
					Spawn(sa, 2);
					Spawn(sb, 2);
				}
			}
		}
	
		if (mDir.LengthSquare()>0 && !mDiedOnFrame)
		{
			// constantly spawn bad spots
			if (mSpawnCooldown>0)
			{
				mSpawnCooldown--;
			}
			else if (mPendingGrowth==0 && (mRNG()%12)==0)
			{
				Spawn(1);
				mSpawnCooldown = 12;
			}
		
			Point next = Advance( mPos.front(), mDir );
			mPos.push_front( next );
		
			Point other = Other(next,mDir);
		
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
		else
		{
            // pre-game insrructions in screen
            if (!mPaused && IdleFrames()>=24*10)
            {
                delete mSnakeController;
                mSnakeController = new SnakeAIController();
                mAttract = true;
            }
		}
	}
	
	mScore=std::max(static_cast<int>(mPos.size())-1,mScore);

	// score area horizontal
	ClearRows(mVertical-8, mVertical-7, 1);
	// bottom border horizontal
	ClearRows(0, 1, 1);

	if (mAttract==false)
    {
        if (mScore > mHighScore)
        {
            mHighScore=mScore;
            SetLocalHighScore(mHighScore);
        }
    }

	PrintNumber( mScore, 1, mVertical-2, Left );
	PrintNumber( mHighScore, mHorizontal, mVertical-2, Right );	
	
	// on screen message during pause
    PrintString( GetMsg(mPaused, mAttract, mScore), mHorizontal/2, mVertical-2, Center );
}