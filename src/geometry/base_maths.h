#ifndef BASIC_MATHS_HEADER_INCLUDED
#define BASIC_MATHS_HEADER_INCLUDED

#include <limits>
#include <math.h>

namespace Geometry
{
	inline float Sqrt( float f )
	{
		return sqrtf( f );
	}

	inline double Sqrt( double f )
	{
		return sqrt( f );
	}

	// http://www.codecodex.com/wiki/index.php?title=Calculate_an_integer_square_root
	inline int Sqrt( int x )
	{
		register unsigned long op, res, one;
		op = x;
	    res = 0;
		
		one = 1 << 30;
		while (one > op) one >>= 2;
	    while (one != 0) {
		    if (op >= res + one) {
			    op = op - (res + one);
				res = res +  2 * one;
			}
			res >>= 1;
			one >>= 2;
		}
		return(res);
	}


}

#endif //BASIC_MATHS_HEADER_INCLUDED