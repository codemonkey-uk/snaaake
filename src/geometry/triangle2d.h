#ifndef GEOMETRY_TRIANGLE2D_H_INCLUDED_
#define GEOMETRY_TRIANGLE2D_H_INCLUDED_

#include "triangle.h"
#include "vector2d.h"

#include <math.h>

namespace Geometry
{
    //
    // Interface
    //
    template <typename Scalar>
    class Triangle2d : public Triangle< Vector2d<Scalar> >
    {
        public:
            typedef typename Triangle< Vector2d<Scalar> >::VectorType VectorType;
            typedef typename Triangle< Vector2d<Scalar> >::VertexType VertexType;
            
            Triangle2d(const VertexType& t1, const VertexType& t2, const VertexType& t3);
                        
            Scalar GetSurfaceArea() const;
            
            void ComputeCircumCenter( VectorType& result ) const;
            VectorType GetCircumCenter() const;
            Scalar GetCircumRadius() const;
    };
    
    //
    // Class Implementation
    // (in header as is a template)
    //
    
    template <typename Scalar>
    Triangle2d<Scalar>::Triangle2d(const VertexType& t1, const VertexType& t2, const VertexType& t3)
        : Triangle< Vector2d<Scalar> >(t1,t2,t3)
    {
        // nothing to do here
    }
    
    template <typename Scalar>
    Scalar Triangle2d<Scalar>::GetSurfaceArea() const
    {
        return fabs ( Scalar(0.5) * ( 
          this->mA.GetX() * ( this->mC.GetY() - this->mB.GetY() ) + 
          this->mB.GetX() * ( this->mA.GetY() - this->mC.GetY() ) + 
          this->mC.GetX() * ( this->mB.GetY() - this->mA.GetY() ) ) 
        );
    }

    template <typename Scalar>
    void Triangle2d<Scalar>::ComputeCircumCenter( typename Triangle2d<Scalar>::VectorType& result ) const
    {
        const Scalar asq = ( this->mB.GetX() - this->mA.GetX() ) * ( this->mB.GetX() - this->mA.GetX() ) + ( this->mB.GetY() - this->mA.GetY() ) * ( this->mB.GetY() - this->mA.GetY() );
        const Scalar csq = ( this->mC.GetX() - this->mA.GetX() ) * ( this->mC.GetX() - this->mA.GetX() ) + ( this->mC.GetY() - this->mA.GetY() ) * ( this->mC.GetY() - this->mA.GetY() );
        
        const Scalar top1 =  ( this->mB.GetY() - this->mA.GetY() ) * csq - ( this->mC.GetY() - this->mA.GetY() ) * asq;
        const Scalar top2 =  ( this->mB.GetX() - this->mA.GetX() ) * csq - ( this->mC.GetX() - this->mA.GetX() ) * asq;
        const Scalar bot  =  ( this->mB.GetY() - this->mA.GetY() ) * ( this->mC.GetX() - this->mA.GetX() )  - ( this->mC.GetY() - this->mA.GetY() ) * ( this->mB.GetX() - this->mA.GetX() );
        
        result.SetX( this->mA.GetX() + 0.5E+00 * top1 / bot);
        result.SetY( this->mA.GetY() - 0.5E+00 * top2 / bot);
    }

    template <typename Scalar>
    typename Triangle2d<Scalar>::VectorType Triangle2d<Scalar>::GetCircumCenter() const
    {
        VectorType result(uninitialised);
        ComputeCircumCenter(result);
        return result;
    }

    template <typename Scalar>
    Scalar Triangle2d<Scalar>::GetCircumRadius() const
    {
        Scalar asq = sqrt ( ( this->mB.GetX() - this->mA.GetX() ) * ( this->mB.GetX() - this->mA.GetX() ) + ( this->mB.GetY() - this->mA.GetY() ) * ( this->mB.GetY() - this->mA.GetY() ) );
        Scalar bsq = sqrt ( ( this->mC.GetX() - this->mB.GetX() ) * ( this->mC.GetX() - this->mB.GetX() ) + ( this->mC.GetY() - this->mB.GetY() ) * ( this->mC.GetY() - this->mB.GetY() ) );
        Scalar csq = sqrt ( ( this->mA.GetX() - this->mC.GetX() ) * ( this->mA.GetX() - this->mC.GetX() ) + ( this->mA.GetY() - this->mC.GetY() ) * (this-> mA.GetY() - this->mC.GetY() ) );
        
        Scalar bot = ( asq + bsq + csq ) * ( - asq + bsq + csq ) * ( asq - bsq + csq ) * ( asq + bsq - csq );
        
        assert ( bot > 0 );
        
        return asq * bsq * csq / sqrt ( bot );
    }

}

#endif