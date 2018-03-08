#pragma once

#ifndef __AVR__
#include <cstddef>
#include <cmath>
#endif

#include "Macro.h"

class Vec2f;
class Vec3f;
// #include "ofConstants.h"

class Vec4f {
public:
    /// \cond INTERNAL
    static constexpr int DIM = 4;
    /// \endcond

    union {
    	float data[4];
    	struct {
			float x;
			float y;
			float z;
			float w;
		};
	};

	//---------------------
	/// \name Construct a 4D vector
	/// \{

	Vec4f();
	explicit Vec4f( float _scalar );
	Vec4f( float _x, float _y, float _z = 0.0f, float _w = 0.0f );
	Vec4f( const Vec2f& vec);
	Vec4f( const Vec3f& vec);

    /// \}

	//---------------------
	/// \name Access components
	/// \{


	float * getPtr() {
		return data;
	}
	const float * getPtr() const {
		return data;
	}

	float& operator[]( size_t n ){
		return data[n];
	}

	float operator[]( size_t n ) const {
		return data[n];
	}

	void set( float _scalar );
    void set( float _x, float _y, float _z = 0.0f, float _w = 0.0f );
    void set( const Vec4f& vec );


	/// \}

    //---------------------
	/// \name Comparison
	/// \{


    bool operator==( const Vec4f& vec ) const;
    bool operator!=( const Vec4f& vec ) const;
    bool match( const Vec4f& vec, float tolerance = 0.0001f) const;

	/// \}

	//---------------------
	/// \name Operators
	/// \{

    Vec4f  operator+( const Vec4f& vec ) const;
    Vec4f  operator+( const float f ) const;
    Vec4f& operator+=( const Vec4f& vec );
    Vec4f& operator+=( const float f );
    Vec4f  operator-( const float f ) const;
    Vec4f  operator-( const Vec4f& vec ) const;
    Vec4f  operator-() const;
    Vec4f& operator-=( const float f );
    Vec4f& operator-=( const Vec4f& vec );


    Vec4f  operator*( const Vec4f& vec ) const;
    Vec4f  operator*( const float f ) const;
    Vec4f& operator*=( const Vec4f& vec );
    Vec4f& operator*=( const float f );
    Vec4f  operator/( const Vec4f& vec ) const;
    Vec4f  operator/( const float f ) const;
    Vec4f& operator/=( const Vec4f& vec );
    Vec4f& operator/=( const float f );

	/// \cond INTERNAL
	// friend ostream& operator<<(ostream& os, const Vec4f& vec);
	// friend istream& operator>>(istream& is, const Vec4f& vec);
	/// \endcond

    /// \}

	//---------------------
	/// \name Simple manipulations
	/// \{

    /// \brief Returns a new Vec4f that is the result of scaling this vector up or down so that it has the requested length.
    ///
    /// \param length The desired length of the new Vec4f object.
    /// \returns The result of scaling the this vector up or down.
    Vec4f  getScaled( const float length ) const;

    /// \brief Scales this vector up or down so that it has the requested length.
    ///
    /// \param length The desired length of the vector.
    Vec4f& scale( const float length );

	/// \}


	//---------------------
	/// \name Distance
	/// \{

    /// \brief Treats this vector and 'pnt' as points in 4D space and calculates the distance between them.
    ///
    /// \param pnt The vector used in the distance calculation with the current vector.
    /// \returns The distance between the two vectors in 4D space.
    float distance( const Vec4f& pnt) const;
    float squareDistance( const Vec4f& pnt ) const;

	/// \}

	//---------------------
	/// \name Interpolation
	/// \{


    /// \brief Performs a linear interpolation of this vector towards 'pnt'.
    ///
    /// \param pnt The vector the interpolation will be performed on.
    /// \param p The amount to move towards 'pnt'; 'p' is normally between 0 and 1 and where 0 means stay the original position and 1 means move all the way to 'pnt', but you can also have 'p' greater than 1 overshoot 'pnt', or less than 0 to move backwards away from 'pnt'.
    /// \returns The interpolation as an Vec4f.
    Vec4f   getInterpolated( const Vec4f& pnt, float p ) const;

    /// \brief Performs a linear interpolation of this vector towards 'pnt'. This modifies the current vector to the interpolated value.
    ///
    /// \param pnt The vector the interpolation will be performed on.
    /// \param p The amount to move towards 'pnt'; 'p' is normally between 0 and 1 and where 0 means stay the original position and 1 means move all the way to 'pnt', but you can also have 'p' greater than 1 overshoot 'pnt', or less than 0 to move backwards away from 'pnt'.
    Vec4f&  interpolate( const Vec4f& pnt, float p );

    /// \brief Calculates and returns the midpoint (as a vector) between this vector and 'pnt'.
    ///
    /// \param pnt The vector used in the midpoint calculation with this vector.
    /// \returns The midpoint between this vector and 'pnt' as an Vec4f.
    Vec4f   getMiddle( const Vec4f& pnt ) const;

    /// \brief Calculates and returns the midpoint (as a vector) between this vector and 'pnt'. This modifies the current vector to the midpoint value.
    ///
    /// \param pnt The vector used in the midpoint calculation with this vector.
    /// \returns The midpoint between this vector and 'pnt' as an Vec4f.
    Vec4f&  middle( const Vec4f& pnt );

    /// \brief Sets this vector to be the average (center of gravity or centroid) of a given array of 'Vec4f's.
    ///
    /// \param points The array of 'Vec4f's used in the average calculation.
    /// \param num The number of Vec4f objects in the array.
    Vec4f&  average( const Vec4f* points, int num );

    /// \}

    //---------------------
	/// \name Limit
	/// \{

    /// \brief Returns a normalized copy of this vector.
    ///
    /// Normalization means to scale the vector so that its length (magnitude) is exactly 1,
    /// at which stage all that is left is the direction. A normalized vector is usually called
    /// a unit vector, and can be used to represent a pure direction (heading).
    ///
    /// \returns The normalized copy of the current vector.
    Vec4f  getNormalized() const;

    /// \brief Normalizes the vector. This changes the current vector to its normalized value.
    ///
    /// Normalization means to scale the vector so that its length (magnitude) is exactly 1,
    /// at which stage all that is left is the direction. A normalized vector is usually called
    /// a unit vector, and can be used to represent a pure direction (heading).
    Vec4f& normalize();


    /// \brief Returns a copy of this vector with its length (magnitude) restricted to a maximum of 'max' units by scaling down if necessary.
    ///
    /// \param max The maximum length of the new vector.
    /// \returns A copy of the current vector that is at most 'max' units long.
    Vec4f  getLimited(float max) const;
    /// \brief Restrict the length (magnitude) of this vector to a maximum of 'max' units by scaling down if necessary.
    ///
    /// \param max The maximum length of the current vector.
    Vec4f& limit(float max);

	/// \}

	//---------------------
	/// \name Measurement
	/// \{

    /// \brief Returns the length (magnitude) of this vector.
    ///
    /// \returns The magnitude of the current vector.
    float length() const;
    float lengthSquared() const;


  	/// \}

	//---------------------
	/// \name Calculations
	/// \{


    /// \brief Calculates and returns the dot product of this vector with 'vec'.
    ///
    /// Dot product (less commonly known as Euclidean inner product) expresses the angular
    /// relationship between two vectors. In other words it is a measure of how parallel two vectors
    /// are. If they are completely perpendicular the dot product is 0; if they are completely parallel
    /// their dot product is either 1 if they are pointing in the same direction, or -1 if they are pointing
    /// in opposite directions.
    ///
    /// \param vec The vector used in the dot product calculation with this vector.
    /// \returns The dot product of this vector with 'vec'.
    float dot( const Vec4f& vec ) const;

	/// \}




    //---------------------------------------
    // this methods are deprecated in 006 please use:
	/// \cond INTERNAL

    // // getScaled
    // OF_DEPRECATED_MSG("Use member method getScaled() instead.", Vec4f rescaled( const float length ) const);
    //
    // // scale
    // OF_DEPRECATED_MSG("Use member method scale() instead.", Vec4f& rescale( const float length ));
    //
    // // getNormalized
    // OF_DEPRECATED_MSG("Use member method getNormalized() instead.", Vec4f normalized() const);
    //
    // // getLimited
    // OF_DEPRECATED_MSG("Use member method getLimited() instead.", Vec4f limited(float max) const);
    //
    // // use squareDistance
    // OF_DEPRECATED_MSG("Use member method squareDistance() instead.", float  distanceSquared( const Vec4f& pnt ) const);
    //
    // // use getInterpolated
    // OF_DEPRECATED_MSG("Use member method getInterpolated() instead.", Vec4f interpolated( const Vec4f& pnt, float p ) const);
    //
    // // use getMiddle
    // OF_DEPRECATED_MSG("Use member method getMiddle() instead.", Vec4f middled( const Vec4f& pnt ) const);

    // return all zero vector
    static Vec4f zero() { return Vec4f(0, 0, 0, 0); }

    // return all one vector
    static Vec4f one() { return Vec4f(1, 1, 1, 1); }
    /// \endcond
};


/// \cond INTERNAL


// Non-Member operators
//
//
Vec4f operator+( float f, const Vec4f& vec );
Vec4f operator-( float f, const Vec4f& vec );
Vec4f operator*( float f, const Vec4f& vec );
Vec4f operator/( float f, const Vec4f& vec );







/////////////////
// Implementation
/////////////////

inline Vec4f::Vec4f(): x(0), y(0), z(0), w(0) {}
inline Vec4f::Vec4f(float _s): x(_s), y(_s), z(_s), w(_s) {}
inline Vec4f::Vec4f( float _x,
						float _y,
						float _z,
						float _w ):x(_x), y(_y), z(_z), w(_w) {}

// Getters and Setters.
//
//
inline void Vec4f::set( float _scalar) {
	x = _scalar;
	y = _scalar;
	z = _scalar;
	w = _scalar;
}

inline void Vec4f::set( float _x, float _y, float _z, float _w ) {
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

inline void Vec4f::set( const Vec4f& vec ) {
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = vec.w;
}


// Check similarity/equality.
//
//
inline bool Vec4f::operator==( const Vec4f& vec ) const {
	return (x == vec.x) && (y == vec.y) && (z == vec.z) && (w == vec.w);
}

inline bool Vec4f::operator!=( const Vec4f& vec ) const {
	return (x != vec.x) || (y != vec.y) || (z != vec.z) || (w != vec.w);
}

inline bool Vec4f::match( const Vec4f& vec, float tolerance) const {
	return (fabs(x - vec.x) < tolerance)
	&& (fabs(y - vec.y) < tolerance)
	&& (fabs(z - vec.z) < tolerance)
	&& (fabs(w - vec.w) < tolerance);
}




// Additions and Subtractions.
//
//
inline Vec4f Vec4f::operator+( const Vec4f& vec ) const {
	return Vec4f( x+vec.x, y+vec.y, z+vec.z, w+vec.w);
}

inline Vec4f& Vec4f::operator+=( const Vec4f& vec ) {
	x += vec.x;
	y += vec.y;
	z += vec.z;
	w += vec.w;
	return *this;
}

inline Vec4f Vec4f::operator-( const float f ) const {
	return Vec4f( x-f, y-f, z-f, w-f );
}

inline Vec4f& Vec4f::operator-=( const float f ) {
	x -= f;
	y -= f;
	z -= f;
	w -= f;
	return *this;
}

inline Vec4f Vec4f::operator-( const Vec4f& vec ) const {
	return Vec4f( x-vec.x, y-vec.y, z-vec.z, w-vec.w );
}

inline Vec4f& Vec4f::operator-=( const Vec4f& vec ) {
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	w -= vec.w;
	return *this;
}

inline Vec4f Vec4f::operator+( const float f ) const {
	return Vec4f( x+f, y+f, z+f, w+f );
}

inline Vec4f& Vec4f::operator+=( const float f ) {
	x += f;
	y += f;
	z += f;
	w += f;
	return *this;
}

inline Vec4f Vec4f::operator-() const {
	return Vec4f( -x, -y, -z, -w );
}


// Scalings
//
//
inline Vec4f Vec4f::operator*( const Vec4f& vec ) const {
	return Vec4f( x*vec.x, y*vec.y, z*vec.z, w*vec.w );
}

inline Vec4f& Vec4f::operator*=( const Vec4f& vec ) {
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	w *= vec.w;
	return *this;
}

inline Vec4f Vec4f::operator*( const float f ) const {
	return Vec4f( x*f, y*f, z*f, w*f );
}

inline Vec4f& Vec4f::operator*=( const float f ) {
	x *= f;
	y *= f;
	z *= f;
	w *= f;
	return *this;
}

inline Vec4f Vec4f::operator/( const Vec4f& vec ) const {
	return Vec4f( vec.x!=0 ? x/vec.x : x , vec.y!=0 ? y/vec.y : y, vec.z!=0 ? z/vec.z : z, vec.w!=0 ? w/vec.w : w  );
}

inline Vec4f& Vec4f::operator/=( const Vec4f& vec ) {
	vec.x!=0 ? x/=vec.x : x;
	vec.y!=0 ? y/=vec.y : y;
	vec.z!=0 ? z/=vec.z : z;
	vec.w!=0 ? w/=vec.w : w;
	return *this;
}

inline Vec4f Vec4f::operator/( const float f ) const {
	if(f == 0) return Vec4f(x, y, z, w);

	return Vec4f( x/f, y/f, z/f, w/f );
}

inline Vec4f& Vec4f::operator/=( const float f ) {
	if(f == 0)return *this;

	x /= f;
	y /= f;
	z /= f;
	w /= f;
	return *this;
}


// inline ostream& operator<<(ostream& os, const Vec4f& vec) {
// 	os << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w;
// 	return os;
// }
//
// inline istream& operator>>(istream& is, Vec4f& vec) {
// 	is >> vec.x;
// 	is.ignore(2);
// 	is >> vec.y;
// 	is.ignore(2);
// 	is >> vec.z;
// 	is.ignore(2);
// 	is >> vec.w;
// 	return is;
// }


// inline Vec4f Vec4f::rescaled( const float length ) const {
// 	return getScaled(length);
// }

inline Vec4f Vec4f::getScaled( const float length ) const {
	float l = (float)sqrt(x*x + y*y + z*z + w*w);
	if( l > 0 )
		return Vec4f( (x/l)*length, (y/l)*length,
					   (z/l)*length, (w/l)*length );
	else
		return Vec4f();
}

// inline Vec4f& Vec4f::rescale( const float length ) {
// 	return scale(length);
// }

inline Vec4f& Vec4f::scale( const float length ) {
	float l = (float)sqrt(x*x + y*y + z*z + w*w);
	if (l > 0) {
		x = (x/l)*length;
		y = (y/l)*length;
		z = (z/l)*length;
		w = (w/l)*length;
	}
	return *this;
}



// Distance between two points.
//
//
inline float Vec4f::distance( const Vec4f& pnt) const {
	float vx = x-pnt.x;
	float vy = y-pnt.y;
	float vz = z-pnt.z;
	float vw = w-pnt.w;
	return (float)sqrt( vx*vx + vy*vy + vz*vz + vw*vw );
}

// inline float Vec4f::distanceSquared( const Vec4f& pnt ) const {
// 	return squareDistance(pnt);
// }

inline float Vec4f::squareDistance( const Vec4f& pnt ) const {
	float vx = x-pnt.x;
	float vy = y-pnt.y;
	float vz = z-pnt.z;
	float vw = w-pnt.w;
	return vx*vx + vy*vy + vz*vz + vw*vw;
}



// Linear interpolation.
//
//
/**
 * p==0.0 results in this point, p==0.5 results in the
 * midpoint, and p==1.0 results in pnt being returned.
 */
// inline Vec4f Vec4f::interpolated( const Vec4f& pnt, float p ) const{
// 	return getInterpolated(pnt,p);
// }

inline Vec4f Vec4f::getInterpolated( const Vec4f& pnt, float p ) const {
	return Vec4f( x*(1-p) + pnt.x*p,
				   y*(1-p) + pnt.y*p,
				   z*(1-p) + pnt.z*p,
				   w*(1-p) + pnt.w*p );
}

inline Vec4f& Vec4f::interpolate( const Vec4f& pnt, float p ) {
	x = x*(1-p) + pnt.x*p;
	y = y*(1-p) + pnt.y*p;
	z = z*(1-p) + pnt.z*p;
	w = w*(1-p) + pnt.w*p;
	return *this;
}

// inline Vec4f Vec4f::middled( const Vec4f& pnt ) const {
// 	return getMiddle(pnt);
// }

inline Vec4f Vec4f::getMiddle( const Vec4f& pnt ) const {
	return Vec4f( (x+pnt.x)/2.0f, (y+pnt.y)/2.0f,
				   (z+pnt.z)/2.0f, (w+pnt.w)/2.0f );
}

inline Vec4f& Vec4f::middle( const Vec4f& pnt ) {
	x = (x+pnt.x)/2.0f;
	y = (y+pnt.y)/2.0f;
	z = (z+pnt.z)/2.0f;
	w = (w+pnt.w)/2.0f;
	return *this;
}


// Average (centroid) among points.
// (Addition is sometimes useful for calculating averages too)
//
//
inline Vec4f& Vec4f::average( const Vec4f* points, int num ) {
	x = 0.f;
	y = 0.f;
	z = 0.f;
	w = 0.f;
	for( int i=0; i<num; i++) {
		x += points[i].x;
		y += points[i].y;
		z += points[i].z;
		w += points[i].w;
	}
	x /= num;
	y /= num;
	z /= num;
	w /= num;
	return *this;
}



// Normalization
//
//
// inline Vec4f Vec4f::normalized() const {
// 	return getNormalized();
// }

inline Vec4f Vec4f::getNormalized() const {
	float length = sqrt(x*x + y*y + z*z + w*w);
	if( length > 0 ) {
		return Vec4f( x/length, y/length, z/length, w/length );
	} else {
		return Vec4f();
	}
}

inline Vec4f& Vec4f::normalize() {
	float length = sqrt(x*x + y*y + z*z + w*w);
	if( length > 0 ) {
		x /= length;
		y /= length;
		z /= length;
		w /= length;
	}
	return *this;
}



// Limit length.
//
//
// inline Vec4f Vec4f::limited(float max) const {
// 	return getLimited(max);
// }

inline Vec4f Vec4f::getLimited(float max) const {
    Vec4f limited;
    float lengthSquared = (x*x + y*y + z*z + w*w);
    if( lengthSquared > max*max && lengthSquared > 0 ) {
        float ratio = max/sqrt(lengthSquared);
        limited.set( x*ratio, y*ratio, z*ratio, w*ratio );
    } else {
        limited.set(x,y,z,w);
    }
    return limited;
}

inline Vec4f& Vec4f::limit(float max) {
    float lengthSquared = (x*x + y*y + z*z + w*w);
    if( lengthSquared > max*max && lengthSquared > 0 ) {
        float ratio = max/sqrt(lengthSquared);
        x *= ratio;
        y *= ratio;
        z *= ratio;
        w *= ratio;
    }
    return *this;
}



// Length
//
//
inline float Vec4f::length() const {
	return sqrt(lengthSquared());
}

inline float Vec4f::lengthSquared() const {
	return (x*x + y*y + z*z + w*w);
}




/**
 * Dot Product.
 */
inline float Vec4f::dot( const Vec4f& vec ) const {
	return x*vec.x + y*vec.y + z*vec.z + w*vec.w;
}





// Non-Member operators
//
//
inline Vec4f operator+( float f, const Vec4f& vec ) {
    return Vec4f( f+vec.x, f+vec.y, f+vec.z, f+vec.w );
}

inline Vec4f operator-( float f, const Vec4f& vec ) {
    return Vec4f( f-vec.x, f-vec.y, f-vec.z, f-vec.w );
}

inline Vec4f operator*( float f, const Vec4f& vec ) {
    return Vec4f( f*vec.x, f*vec.y, f*vec.z, f*vec.w );
}

inline Vec4f operator/( float f, const Vec4f& vec ) {
    return Vec4f( f/vec.x, f/vec.y, f/vec.z, f/vec.w);
}


/// \endcond
