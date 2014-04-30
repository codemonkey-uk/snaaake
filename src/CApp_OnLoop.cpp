//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnLoop() 
{
	mX+=mDx;
	if (mX>mHorizontal) mX -= mHorizontal;
	if (mX<0) mX += mHorizontal;
	mY+=mDy;
	if (mY>mVertical) mY -= mVertical;
	if (mY<0) mX += mVertical;
	
    for (int x=0;x!=mHorizontal;x++)
    {
	    for (int y=0;y!=mVertical;y++)
    	{
    		int* p = (mPixels + x + y*mHorizontal);
    		*p = ((x==mX) || (y==mY));
    	}
    }
}

//==============================================================================
