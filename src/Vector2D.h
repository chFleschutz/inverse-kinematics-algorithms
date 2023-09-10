#pragma once

#define _USE_MATH_DEFINES

#include <iomanip>
#include <iostream>
#include <math.h>

/// @brief Small convenient helper class representing a two-dimensional vector
class Vector2D {
public:
	Vector2D();
	Vector2D(float x, float y);

	inline float x() const { return m_x; }
	inline float y() const { return m_y; }

	/// @brief Normalize the Vector2D so it has a length of one
	/// @return A reference to this
	Vector2D& normalize();

	/// @brief Prints the Vector2D to the console formated like this ( x, y )
	void print();
	
	/// @brief Creates and returns a Vector2D of length and rotation
	static Vector2D makeVector(float length, float rotation);

	/// @brief Calculates and returns the dot product of this vector and other
	float dot(Vector2D& other);

	/// @brief Calculates and returns the cross product of this vector and other
	float cross(Vector2D& other);

	/// @brief Returns the length of this Vector2D
	float length();

	/// @brief Adds two Vector2D and returns the result
	Vector2D operator+(const Vector2D& other);
	/// @brief Adds other to this vector and returns a refrence to this
	Vector2D& operator+=(Vector2D other);

	/// @brief Subtracts two Vector2D and returns the result
	Vector2D operator-(const Vector2D& other);
	/// @brief Subtracts other from this vector and returns a refrence to this
	Vector2D& operator-=(Vector2D other);

	/// @brief Divides this Vector2D by a float and returns the result
	Vector2D operator/(float other);
	/// @brief Multiplies this Vector2D with a float and returns the result
	Vector2D operator*(float other);

	/// @brief Prints the Vector2D to the console formated like this ( x, y )
	friend std::ostream& operator<<(std::ostream& os, Vector2D& other);

private:
	float m_x;
	float m_y;
};


