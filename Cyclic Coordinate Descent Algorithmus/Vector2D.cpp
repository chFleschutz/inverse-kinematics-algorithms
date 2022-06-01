#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D() : x(0.0f), y(0.0f)
{
}

float Vector2D::norm() {
	return sqrt(x * x + y * y);
}

Vector2D operator-(Vector2D& o1, Vector2D& o2) {
	Vector2D res;
	res.x = o1.x - o2.x;
	res.y = o1.y - o2.y;
	return res;
}

float operator*(Vector2D& o1, Vector2D& o2) {
	return o1.x * o2.x + o1.y * o2.y;
}