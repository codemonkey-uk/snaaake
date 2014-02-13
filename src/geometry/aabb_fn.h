#ifndef GEOMETRY_AABBFN_H_INCLUDED_
#define GEOMETRY_AABBFN_H_INCLUDED_

#include "aabb.h"

namespace Geometry
{
	// difference 
	// outputs the set of AABBs that cover the space in B not already covered by A
	template <typename AABB, typename insertion_iterator>
	void AABB_Difference( 
		AABB a, AABB b,
		insertion_iterator& ii 
	)
	{
		// for each dimention that this AABB exists in
		AABB bb = b;
		for(size_t d=0;d!=AABB::VectorType::sDimensions;++d)
		{
			if (b.GetMinBound().Get(d) < a.GetMinBound().Get(d))
			{
				typename AABB::VectorType newMax( b.GetMaxBound() );
				newMax[d] = a.GetMinBound().Get(d);
				AABB result( bb.GetMinBound(), newMax );
				*ii++ = result; 
				typename AABB::VectorType newMin( bb.GetMinBound() );
				newMin[d] = newMax[d];
				bb.SetMinBound( newMin );			
			}
		}
		//assert( a.GetMinBound()==bb.GetMinBound() );
		for(size_t d=0;d!=AABB::VectorType::sDimensions;++d)
		{
			if (b.GetMaxBound().Get(d) > a.GetMaxBound().Get(d))
			{
				typename AABB::VectorType newMin( a.GetMinBound() );
				newMin[d] = a.GetMaxBound().Get(d);
				*ii++ = AABB( newMin, bb.GetMaxBound() );
				typename AABB::VectorType newMax( bb.GetMaxBound() );
				newMax[d] = newMin[d];
				bb.SetMaxBound( newMax );			
			}
		}
		//assert( a==bb );
	}
}

#endif