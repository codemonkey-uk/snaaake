#ifndef GEOMETRY_TRIANGLE_H_INCLUDED_
#define GEOMETRY_TRIANGLE_H_INCLUDED_

#include "vector3d.h"

#include <math.h>

namespace Geometry
{
    //
    // Interface
    //
    
    template<typename T>
    class Triangle
    {
        public:
            typedef T VertexType;
            typedef typename VertexType::VectorType VectorType;
            typedef typename VectorType::ScalarType ScalarType;
            
            Triangle( const Geometry::Uninitialised& ) 
                : mA( Geometry::uninitialised )
                , mB( Geometry::uninitialised )
                , mC( Geometry::uninitialised )
            { }
            
            Triangle(const VertexType& t1, const VertexType& t2, const VertexType& t3);
            
            const VertexType& GetA() const;
            const VertexType& GetB() const;
            const VertexType& GetC() const;
            
            void SetA(const VertexType& a) ;
            void SetB(const VertexType& b) ;
            void SetC(const VertexType& c) ;
            
            // determine the angles of the triangle 
            void ComputeAngles(Vector3d<ScalarType> & result) const;
            Vector3d<ScalarType> GetAngles() const;
            
            // determine the centroid (center of gravity) of the triangle
            void ComputeCentroid( VectorType & result ) const;
            VectorType GetCentroid( ) const;
        
        protected:
            VertexType mA,mB,mC;
    };

    //
    // Class Implementation
    // (in header as is a template)
    //
    template<typename T>
    Triangle<T>::Triangle(const VertexType& t1, const VertexType& t2, const VertexType& t3)
        : mA(t1), mB(t2), mC(t3) 
    {
        // nothing to do here
    }
    
    template<typename T>
    const typename Triangle<T>::VertexType& Triangle<T>::GetA() const
    {
        return mA;
    }
    
    template<typename T>
    const typename Triangle<T>::VertexType& Triangle<T>::GetB() const
    {
        return mB;        
    }
    
    template<typename T>
    const typename Triangle<T>::VertexType& Triangle<T>::GetC() const
    {
        return mC;
    }
    
    template<typename T>
    void Triangle<T>::SetA(const VertexType& a_) 
    {
        mA = a_;
    }
    
    template<typename T>
    void Triangle<T>::SetB(const VertexType& b_) 
    {
        mB = b_;
    }
    
    template<typename T>
    void Triangle<T>::SetC(const VertexType& c_) 
    {
        mC = c_;
    }
    
    // computes the angles of the triangle into argument 'result'
    template<typename T>
    void Triangle<T>::ComputeAngles(Vector3d<ScalarType> & result) const
    {
        const ScalarType d1s(mA.DistanceSquare(mB)), d2s(mB.DistanceSquare(mC)), d3s(mC.DistanceSquare(mA));
        const ScalarType d1(sqrt(d1s)), d2(sqrt(d2s)), d3(sqrt(d3s));
        
        assert( d1>0 && d2>0 && d3>0 );
        result[0] = acos ( ( d3s + d1s - d2s ) / ( 2.0E+00 * d3 * d1 ) );
        result[1] = acos ( ( d1s + d2s - d3s ) / ( 2.0E+00 * d1 * d2 ) );
        result[2] = acos ( ( d2s + d3s - d1s ) / ( 2.0E+00 * d2 * d3 ) );
    }
    
    // computes the angles of the triangle and returns the result
    template<typename T>
    Vector3d< typename Triangle<T>::ScalarType > Triangle<T>::GetAngles() const
    {
        Vector3d<ScalarType> result(uninitialised);
        ComputeAngles( result );
        return result;
    }
    
    template<typename T>
    void Triangle<T>::ComputeCentroid( VectorType & result ) const
    {
		const ScalarType divisor(3.0);
        for(size_t i=0;i!=VectorType::GetSize();++i)
        {
            result[i] = (mA[i]+mB[i]+mC[i])/divisor;
        }
    }
    
    template<typename T>
    typename Triangle<T>::VectorType Triangle<T>::GetCentroid( ) const
    {
        VectorType result(uninitialised);
        ComputeCentroid( result );
        return result;
    }
    
}

#endif//GEOMETRY_TRIANGLE_H_INCLUDED_