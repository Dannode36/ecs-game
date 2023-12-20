#include "Types.h"

//Vector on other
Vector2 operator*(Vector2 a, float b){
	 a.x *= b;
	 a.y *= b;
	 return a;
}
Vector2 operator/(Vector2 a, float b) {
	a.x /= b;
	a.y /= b;
	return a;
}

//Vector on Vector
Vector2 operator*(Vector2 a, Vector2 b) {
	a.x *= b.x;
	a.y *= b.y;
	return a;
}
Vector2 operator-(Vector2 a, Vector2 b) {
	a.x -= b.x;
	a.y -= b.y;
	return a;
}
