#include "Vec2f.h"
#include "Vec3f.h"
#include "Vec4f.h"

Vec4f::Vec4f(const Vec3f& vec) {
	x = vec.x;
	y = vec.y;
	z = vec.z;
	w = 0;
}

Vec4f::Vec4f(const Vec2f& vec) {
	x = vec.x;
	y = vec.y;
	z = 0;
	w = 0;
}
