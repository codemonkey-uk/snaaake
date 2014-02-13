#ifndef GEOMETRY_AABB2D_H_INCLUDED_
#define GEOMETRY_AABB2D_H_INCLUDED_

#include "vector2d.h"
#include "triangle2d.h"
#include "aabb.h"

#include <math.h>

namespace Geometry
{
    //
    // Interface
    //
    template <typename Scalar>
    class AxisAlignedBoundingBox2d : public AxisAlignedBoundingBox< Vector2d<Scalar> >
    {
        public:
            typedef typename AxisAlignedBoundingBox< Vector2d<Scalar> >::VectorType VectorType;
            
            AxisAlignedBoundingBox2d(const VectorType& minBound, const VectorType& maxBound)
                : AxisAlignedBoundingBox< Vector2d<Scalar> >( minBound, maxBound ) 
            { }
            
            AxisAlignedBoundingBox2d(Scalar x1, Scalar y1, Scalar x2, Scalar y2)
                : AxisAlignedBoundingBox< Vector2d<Scalar> >( VectorType(x1, y1), VectorType(x2, y2) ) 
            { }
            
            AxisAlignedBoundingBox2d(const Uninitialised& u)
             : AxisAlignedBoundingBox< Vector2d<Scalar> >(u) {}
            typename VectorType::ScalarType GetWidth() const
            {
                return this->GetAxisExtent(0);
            }
            
            typename VectorType::ScalarType GetHeight() const
            {
                return this->GetAxisExtent(1);
            }
			
			Triangle2d<Scalar> GetEnclosingTriangle()const
			{
				typename Triangle2d<Scalar>::VertexType
				    a( this->mA.GetX() + this->GetWidth()/2, this->mA.GetY() - this->GetWidth() ), 
					b( this->mB.GetX() + this->GetHeight(),  this->mB.GetY() ), 
					c( this->mA.GetX() - this->GetHeight(),  this->mB.GetY() );
				return Triangle2d<Scalar>( a, b, c );
			}
    };
}    

#endif//GEOMETRY_AABB2D_H_INCLUDED_