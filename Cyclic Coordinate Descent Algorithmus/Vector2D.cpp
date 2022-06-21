#include "Vector2D.h"

Vector2D::Vector2D() : m_x(0.0f), m_y(0.0f)
{
}

Vector2D::Vector2D(float x, float y) : m_x(x), m_y(y)
{
}

// Normalizes the Vector
Vector2D& Vector2D::normalize() 
{
	float length = this->length();
	m_x = m_x / length;
	m_y = m_y / length;
	return *this;
}

// Prints the Vector to Console in shape of: ( x, y)
void Vector2D::print()
{
	std::cout << "( " << m_x << ", " << m_y << " )" << std::endl;
}

// Returns a Vector which is rotated around rotation and has the length length
Vector2D Vector2D::makeVector(float length, float rotation)
{
	return Vector2D(length * cos(rotation * M_PI / 180), length * sin(rotation * M_PI / 180));
}

float Vector2D::dot(Vector2D& vector)
{
	return (m_x * vector.x()) + (m_y * vector.y());
}

float Vector2D::cross(Vector2D& vector)
{
	return (m_x * vector.y()) - (m_y * vector.x());
}

float Vector2D::length()
{
	return sqrt((m_x * m_x) + (m_y * m_y));
}

// Vector Addition (x1 + x2, y1 + y2)
Vector2D Vector2D::operator+(Vector2D& other)
{
	return Vector2D(m_x + other.x(), m_y + other.y());
}

Vector2D Vector2D::operator+(Vector2D other)
{
	return Vector2D(m_x + other.x(), m_y + other.y());
}

 //Vector Subtraction (x1 - x2, y1 - y2)
Vector2D Vector2D::operator-(Vector2D& other) 
{
	return Vector2D(m_x - other.x(), m_y - other.y());
}

// Vector Addition to this Vector
Vector2D& Vector2D::operator+=(Vector2D other)
{
	m_x += other.x();
	m_y += other.y();
	return *this;
}

Vector2D& Vector2D::operator-=(Vector2D other)
{
	m_x -= other.x();
	m_y -= other.y();
	return *this;
}

Vector2D Vector2D::operator/(float other)
{
	return Vector2D(m_x / other, m_y / other);
}

std::ostream& operator<<(std::ostream& os, Vector2D& other)
{
	return os << std::fixed << std::setprecision(3) << "( " << other.x() << ", " << other.y() << " )";
}