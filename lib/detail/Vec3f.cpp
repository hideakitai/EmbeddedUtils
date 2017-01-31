#include "Vec2f.h"
#include "Vec3f.h"
#include "Vec4f.h"

Vec3f::Vec3f( const Vec2f& vec ):x(vec.x), y(vec.y), z(0) {}
Vec3f::Vec3f( const Vec4f& vec ):x(vec.x), y(vec.y), z(vec.z) {}
