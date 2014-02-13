#ifndef GEOMETRY_TRIANGLE3D_H_INCLUDED_
#define GEOMETRY_TRIANGLE3D_H_INCLUDED_

#include "triangle.h"
#include "vector3d.h"

#include <math.h>

namespace Geometry
{
    //
    // Interface
    //
    
    template <typename Scalar>
    class Triangle3d : public Triangle< Vector3d<Scalar> >
    {
        public:
            typedef typename Triangle< Vector3d<Scalar> >::VectorType VectorType;
            typedef typename Triangle< Vector3d<Scalar> >::VertexType VertexType;
            
            Triangle3d(const VertexType& t1, const VertexType& t2, const VertexType& t3)
                : Triangle< Vector3d<Scalar> >(t1,t2,t3) {}
            
            Scalar GetSurfaceArea_HeronsForumla() const;
            Scalar GetSurfaceArea() const;
    };
    
    //
    // Free-functions
    //

    template<typename Triangle>
    typename Triangle::VectorType FaceNormal( const Triangle& t )
    {
        const typename Triangle::VectorType ab = t.GetB() - t.GetA();
        const typename Triangle::VectorType ac = t.GetC() - t.GetA();
        typename Triangle::VectorType cross = CrossProduct( ab, ac );
        cross.Normalise();
        return cross;
    }
    
    //
    // Class Implementation
    // (in header as is a template)
    //
    /*
    template <typename Scalar>
    Scalar Triangle3d<Scalar>::GetSurfaceArea_HeronsForumla() const 
    {
        const Scalar sa = b.Distance(c);
        const Scalar sb = c.Distance(a);
        const Scalar sc = a.Distance(b);
        const Scalar s = (sa+sb+sc)/2;
        return Scalar( sqrt( s*(s-sa)*(s-sb)*(s-sc) ) );
    }
    */
    template <typename Scalar>
    Scalar Triangle3d<Scalar>::GetSurfaceArea() const 
    {
        //  Find the projection of (c-a) onto (b-a).
        Scalar dot = DotProduct(this->GetB()-this->GetA(), this->GetC()-this->GetA());
        Scalar base = this->GetA().Distance( this->GetB() );
        assert ( base > 0.0 );
        
        //  The height of the triangle is the length of (P3-P1) after its
        //  projection onto (P2-P1) has been subtracted.
        Scalar alpha = dot / ( base * base );
        
        Scalar sa = this->mC.GetX() - this->mA.GetX() - alpha * ( this->mB.GetX() - this->mA.GetX() );
        Scalar sb = this->mC.GetY() - this->mA.GetY() - alpha * ( this->mB.GetY() - this->mA.GetY() );
        Scalar sc = this->mC.GetZ() - this->mA.GetZ() - alpha * ( this->mB.GetZ() - this->mA.GetZ() );
        
        return Scalar(0.5) * base * sqrt ( sa * sa + sb * sb + sc * sc );
    }
}    

#endif