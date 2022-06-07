#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <iomanip>

class Vector2D {
public:
	Vector2D();
	Vector2D(float x, float y);

	inline float x() { return m_x; }
	inline float y() { return m_y; }

	float norm();
	void print();

	// Creates a Vector with the length and rotation provided
	static Vector2D makeVector(float length, float rotation);
	// Returns the Length of the Vector
	float length();

	// Adds two Vectors together
	Vector2D operator+(Vector2D& other);
	Vector2D operator+(Vector2D other);

	// Subtracts other from this vector
	Vector2D operator-(Vector2D& other);
	// Adds other to this Vector
	Vector2D& operator+=(Vector2D other);
	// Vector Dot-Product
	float operator*(Vector2D& other);
	// Prints the Vector in Form: ( x, y )
	friend std::ostream& operator<<(std::ostream& os, Vector2D& other);

private:
	float m_x;
	float m_y;
};


