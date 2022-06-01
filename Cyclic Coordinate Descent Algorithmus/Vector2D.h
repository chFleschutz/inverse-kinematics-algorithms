#pragma once
#include <iostream>

class Vector2D {
public:
	float x, y;
	Vector2D();
	float norm();

	void print() {
		std::cout << "Vector2D: (x: " << x << ", y: " << y << ")\n";
	}

	friend Vector2D operator-(Vector2D& o1, Vector2D& o2);
	friend float operator*(Vector2D& o1, Vector2D& o2);
};


