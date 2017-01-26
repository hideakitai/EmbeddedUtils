#include "Vec2f.h"
#include "Vec3f.h"
#include "Vec4f.h"

Vec2f::Vec2f( const Vec3f& vec ) {
	x = vec.x;
	y = vec.y;
}

Vec2f::Vec2f( const Vec4f& vec ) {
	x = vec.x;
	y = vec.y;
}
