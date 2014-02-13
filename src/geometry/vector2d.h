#ifndef VECTOR2D_H_INCLUDED
#define VECTOR2D_H_INCLUDED

#include "geometry_uninitialised.h"
#include "vectorn.h"

namespace Geometry
{
    //
    // Interface
    //
    
    template<typename Scalar>
    class Vector2d : public VectorN<Scalar, 2>
    {
        public:
            typedef Vector2d<Scalar> VectorType;
            typedef VectorN<Scalar,2> BaseType;
            
            // simple construction
            Vector2d( Scalar a, Scalar b );

            //explicity uninitialised construction
            Vector2d(const Uninitialised&);
                        
            //upcast constructor
            explicit Vector2d( const VectorN<Scalar, 2>& rhs );
            
            //simple accessor functions
            //note !!! don't like non-const Scalar & Get but required by shaded_relief
            Scalar& GetX();
            const Scalar& GetX() const;
            void SetX( Scalar v );
            Scalar& GetY();
            const Scalar& GetY() const;
            void SetY( Scalar v );            
    };
    
    //
    // Class Implementation
    // (in header as is a template)
    //
    
    template<typename Scalar>
    Vector2d<Scalar>::Vector2d( Scalar a, Scalar b ) 
        : VectorN<Scalar, 2>(uninitialised) 
    { 
        (*this)[0]=a;
        (*this)[1]=b; 
    }

    template<typename Scalar>
    Vector2d<Scalar>::Vector2d( const VectorN<Scalar, 2>& rhs )
        : VectorN<Scalar, 2>(rhs)
    {
        // nothing to do here
    }
    
    template<typename Scalar>
    Vector2d<Scalar>::Vector2d(const Uninitialised&)
        : VectorN<Scalar, 2>(uninitialised) 
    {
        // nothing to do here
    }
    
    template<typename Scalar>
    Scalar& Vector2d<Scalar>::GetX() 
    {
        return (*this)[0];
    }

    template<typename Scalar>
    const Scalar& Vector2d<Scalar>::GetX() const 
    {
        return (*this)[0];
    }
    
    template<typename Scalar>
    void Vector2d<Scalar>::SetX( Scalar x ) 
    {
        (*this)[0] = x;
    }
    
    template<typename Scalar>
    Scalar& Vector2d<Scalar>::GetY() 
    {
        return (*this)[1];
    }
    
    template<typename Scalar>
    const Scalar& Vector2d<Scalar>::GetY() const 
    {
        return (*this)[1];
    }
    
    template<typename Scalar>
    void Vector2d<Scalar>::SetY( Scalar y ) 
    {
        (*this)[1] = y;
    }

	template< typename Scalar >
	class Line2d : public LineN< Vector2d<Scalar> >
	{
	public:
		typedef Vector2d<Scalar> VectorType;
		typedef Scalar ScalarType;

        Line2d( const VectorType& start, const VectorType& finish )
			: LineN<Vector2d<Scalar> >(start, finish)
		{
		}

		VectorType Normal()const
		{
			VectorType result(this->mFinish);
			result -= this->mStart;
			result.Normalise();
			ScalarType temp = result.Get(0);
			result.Set(0, -result.Get(1));
			result.Set(1, temp);
			return result;
		}

		ScalarType SignedDistance(const VectorType& p)const
		{
            VectorType v(p - this->mStart);
			return DotProduct(v, Normal());
		}
        
        ScalarType Side(const VectorType& p)const
        {
            VectorType ab(this->mFinish - this->mStart);
            VectorType ap(p - this->mStart);
            return (ab.GetX()*ap.GetY())-(ab.GetY()*ap.GetX());
        }
	};
}

#endif