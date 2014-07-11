/*
 *  InputLatch.h
 *  Handles directional input filtering for SNAAAKE
 *  Created by Thaddaeus Frogley on 11/07/2014.
 *  Copyright 2014 Thaddaeus Frogley. All rights reserved.
 *
 */

#ifndef INPUTLATCH_H_INCLUDED
#define INPUTLATCH_H_INCLUDED

class InputLatch
{
	public:
	InputLatch() 
		: mDir({0,0})
		, mCount(0)
	{
	}
	
	void Update()
	{
		if (mCount>0) mCount--;
	}
	
	bool IsLocked(const Geometry::VectorN<int,2>& d)
	{
		return (mCount>0 && d==mDir);
	}
	
	void Lock(int c, const Geometry::VectorN<int,2>& d)
	{
		mCount = c;
		mDir = d;
	}
	
	private:
	Geometry::VectorN<int,2> mDir;
	int mCount;
};

#endif // INPUTLATCH_H_INCLUDED