#ifndef GEOMETRY_AABB3D_H_INCLUDED_
#define GEOMETRY_AABB3D_H_INCLUDED_

#include "vector3d.h"
#include "aabb.h"
#include "aabb2d.h"

#include <math.h>

namespace Geometry
{
    //
    // Interface
    //    
    
    template <typename Scalar>
    class AxisAlignedBoundingBox3d : public AxisAlignedBoundingBox< Vector3d<Scalar> >
    {
        public:
            typedef typename AxisAlignedBoundingBox< Vector3d<Scalar> >::VectorType VectorType;
            AxisAlignedBoundingBox3d( const Uninitialised& ) 
				: AxisAlignedBoundingBox< Vector3d<Scalar> >( uninitialised )
			{ }
			
            AxisAlignedBoundingBox3d(const VectorType& minBound, const VectorType& maxBound)
                : AxisAlignedBoundingBox< Vector3d<Scalar> >( minBound, maxBound ) 
            { }
            
            typename VectorType::ScalarType GetWidth() const
            {
                return this->GetAxisExtent(0);
            }
            
            typename VectorType::ScalarType GetHeight() const
            {
                return this->GetAxisExtent(1);
            }
            
            typename VectorType::ScalarType GetDepth() const
            {
                return this->GetAxisExtent(2);
            }
			
			AxisAlignedBoundingBox2d<Scalar> AxisAlignedBoundingBox2dXY()const
			{
				return AxisAlignedBoundingBox2d<Scalar>( 
					this->GetMinBound().Vector2dXY(),
					this->GetMaxBound().Vector2dXY()
				);
			}
    };
}

#endif//GEOMETRY_AABB3D_H_INCLUDED_