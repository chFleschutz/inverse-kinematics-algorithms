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

	// Gives the Vector the length 1 
	Vector2D& normalize();

	// Prints the Vector to Console in form: ( x, y )
	void print();

	// Creates a Vector with the length and rotation provided
	static Vector2D makeVector(float length, float rotation);

	// Dot-Product
	float dot(Vector2D& vector);

	// Cross-Product
	float cross(Vector2D& vector);

	// Returns the Length of the Vector
	float length();

	Vector2D operator+(Vector2D other);
	Vector2D operator-(Vector2D& other);
	Vector2D& operator+=(Vector2D other);
	Vector2D& operator-=(Vector2D other);
	Vector2D operator/(float other);
	Vector2D operator*(float other);


	// Prints the Vector in Form: ( x, y )
	friend std::ostream& operator<<(std::ostream& os, Vector2D& other);

private:
	float m_x;
	float m_y;
};


