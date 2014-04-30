//==============================================================================
#include "CApp.h"
#include <algorithm>
//==============================================================================
void CApp::OnLoop() 
{
	if (mDx || mDy)
	{
		mX+=mDx;
		if (mX>=mHorizontal) mX -= mHorizontal;
		if (mX<0) mX += mHorizontal;
		mY+=mDy;
		if (mY>=mVertical) mY -= mVertical;
		if (mY<0) mY += mVertical;

		int* p = (mPixels + mX + mY*mHorizontal);
		if (*p)
		{
			std::fill(mPixels, mPixels+(mHorizontal*mVertical),0);
		}
		
		*p = 1;
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
