#pragma once

#include <iostream>

#include <cmath>
#include <numbers>

/// @brief Converts a value from radians to degrees
template <typename T>
constexpr T degrees(T value) { return value * 180.0f / std::numbers::pi_v<T>; }

/// @brief Converts a value from degrees to radians
template <typename T>
constexpr T radians(T value) { return value * std::numbers::pi_v<T> / 180.0f; }

/// @brief Small convenient helper class representing a two-dimensional vector
class Vector2 
{
public:
	Vector2() = default;
	Vector2(float x, float y) : m_x(x), m_y(y) {}

	float x() const { return m_x; }
	float y() const { return m_y; }

	/// @brief Normalize the Vector2D so it has a length of one
	/// @return A reference to this
	Vector2& normalize();

	/// @brief Prints the Vector2D to the console formated like this ( x, y )
	void print() const;
	
	/// @brief Creates and returns a Vector2D of length and rotation
	static Vector2 makeVector(float length, float rotation);

	/// @brief Calculates and returns the dot product of this vector and other
	float dot(Vector2& other) const { return (m_x * other.x()) + (m_y * other.y()); }

	/// @brief Calculates and returns the cross product of this vector and other
	float cross(Vector2& other) const { return (m_x * other.y()) - (m_y * other.x()); }

	/// @brief Returns the length of this Vector2D
	float length() const;

	/// @brief Adds two Vector2D and returns the result
	Vector2 operator+(const Vector2& other) const { return Vector2(m_x + other.x(), m_y + other.y()); }
	/// @brief Adds other to this vector and returns a refrence to this
	Vector2& operator+=(Vector2 other);

	/// @brief Subtracts two Vector2D and returns the result
	Vector2 operator-(const Vector2& other) const { return Vector2(m_x - other.x(), m_y - other.y()); }
	/// @brief Subtracts other from this vector and returns a refrence to this
	Vector2& operator-=(Vector2 other);

	/// @brief Divides this Vector2D by a float and returns the result
	Vector2 operator/(float other) const { return Vector2(m_x / other, m_y / other); }
	/// @brief Multiplies this Vector2D with a float and returns the result
	Vector2 operator*(float other) const { return Vector2(m_x * other, m_y * other); }

	/// @brief Prints the Vector2D to the console formated like this ( x, y )
	friend std::ostream& operator<<(std::ostream& os, Vector2& other);
	friend std::ostream& operator<<(std::ostream& os, Vector2&& other);

private:
	float m_x = 0.0f;
	float m_y = 0.0f;
};


