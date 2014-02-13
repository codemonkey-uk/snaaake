#ifndef VECTOR3D_H_INCLUDED
#define VECTOR3D_H_INCLUDED

#include "geometry_uninitialised.h"
#include "vectorn.h"
#include "vector2d.h"

#include <assert.h>
#include <math.h>

namespace Geometry
{
    //
    // Interface
    //
    
    template<typename Scalar>
    class Vector3d : public VectorN<Scalar, 3>
    {
        public:
            typedef Vector3d<Scalar> VectorType;
            typedef VectorN<Scalar,3> BaseType;
            
            //explicity uninitialised construction
            Vector3d(const Uninitialised&);
            
            // normal constructor
            Vector3d( Scalar a, Scalar b, Scalar c );
            
            //type conversion constructor
            template< typename OtherScalar >
			explicit Vector3d<Scalar>( const Vector3d<OtherScalar>& rhs )
				: VectorN<Scalar, 3>(rhs)
			{ 
				// nothing to do here
			}
            
            //upcast constructor
            explicit Vector3d( const VectorN<Scalar, 3>& rhs );
            Vector3d& operator = (const VectorN<Scalar, 3>& rhs);
			
            // simple accessors
            Scalar GetX() const;
            void SetX( Scalar v );
            Scalar GetY() const;
            void SetY( Scalar v );
            Scalar GetZ() const;
            void SetZ( Scalar v );
            
            // dealing with conversion to / mapping to 2d vector
            // !!! note, not using Get/Compute naming convention
            Vector2d< Scalar > Vector2dXY() const;
            Scalar LengthXY() const;
            Scalar DistanceSquareXY(const Vector3d<Scalar>& rhs) const;
            Scalar DistanceXY(const Vector3d<Scalar>& rhs) const;
    };

    //
    // Free-functions
    //
    
    template<typename Scalar>
    Vector3d<Scalar> CrossProduct( const Vector3d<Scalar>& a, const Vector3d<Scalar>& b ) {  
        return Vector3d<Scalar>(
            a.GetY()*b.GetZ() - b.GetY()*a.GetZ(),
            a.GetZ()*b.GetX() - b.GetZ()*a.GetX(),
            a.GetX()*b.GetY() - b.GetX()*a.GetY()
        );
    }
    
    //
    // Class Implementation
    // (in header as is a template)
    //
    template<typename Scalar>
    Vector3d<Scalar>::Vector3d(const Uninitialised&)
        : VectorN<Scalar, 3>(uninitialised) 
    {
        // nothing to do here
    }
    
    template<typename Scalar>
    Vector3d<Scalar>::Vector3d( Scalar a, Scalar b, Scalar c )
        : VectorN<Scalar, 3>(uninitialised) 
    { 
        (*this)[0]=a;
        (*this)[1]=b; 
        (*this)[2]=c; 
    }
    
    //type conversion constructor
	/*
    template<typename Scalar>
    template< typename OtherScalar >
    Vector3d<Scalar>::Vector3d<Scalar>( const Vector3d<OtherScalar>& rhs )
        : VectorN<Scalar, 3>(rhs)
    { 
        // nothing to do here
    }
	*/
    
    //upcast constructor
    template<typename Scalar>
    Vector3d<Scalar>::Vector3d( const VectorN<Scalar, 3>& rhs )
        : VectorN<Scalar, 3>(rhs)
    {
        // nothing to do here
    }
	
    template<typename Scalar>
	Vector3d<Scalar>& Vector3d<Scalar>::operator = (const VectorN<Scalar, 3>& rhs)
	{
		this->BaseType::operator=(rhs);
		return *this;
	}
	
    template<typename Scalar>
    Scalar Vector3d<Scalar>::GetX() const
    {
        return this->Get(0);
    }
    
    template<typename Scalar>
    void Vector3d<Scalar>::SetX( Scalar v ) 
    {
        this->Set(0,v);
    }
    
    template<typename Scalar>
    Scalar Vector3d<Scalar>::GetY() const
    {
        return this->Get(1);
    }
    
    template<typename Scalar>
    void Vector3d<Scalar>::SetY( Scalar v )
    {
        this->Set(1,v);
    }
    
    template<typename Scalar>
    Scalar Vector3d<Scalar>::GetZ() const
    {
        return this->Get(2);
    }
    
    template<typename Scalar>
    void Vector3d<Scalar>::SetZ( Scalar v ) 
    {
        this->Set(2,v);
    }
    
    template<typename Scalar>
    Vector2d< Scalar > Vector3d<Scalar>::Vector2dXY() const {
        return Vector2d< Scalar >(GetX(),GetY());
    }
    
    template<typename Scalar>
    Scalar Vector3d<Scalar>::LengthXY() const {
        return Scalar(sqrt(GetX()*GetX()+GetY()*GetY()));
    }
    
    template<typename Scalar>
    Scalar Vector3d<Scalar>::DistanceSquareXY(const Vector3d<Scalar>& rhs) const {
        Scalar d,l2 = 0;
        d = rhs.GetX() - GetX();
        l2 += d*d;
        d = rhs.GetY() - GetY();
        l2 += d*d;
        
        return l2;
    }
    
    template<typename Scalar>
    Scalar Vector3d<Scalar>::DistanceXY(const Vector3d<Scalar>& rhs) const {
        return Sqrt( DistanceSquareXY(rhs) );
    }
    
}

#endif