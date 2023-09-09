#include "Vector2D.h"

Vector2D::Vector2D() : m_x(0.0f), m_y(0.0f)
{
}

Vector2D::Vector2D(float x, float y) : m_x(x), m_y(y)
{
}

Vector2D& Vector2D::normalize() 
{
	float length = this->length();
	m_x = m_x / length;
	m_y = m_y / length;
	return *this;
}

void Vector2D::print()
{
	std::cout << "( " << m_x << ", " << m_y << " )" << std::endl;
}

Vector2D Vector2D::makeVector(float length, float rotation)
{
	float x = length * cos(rotation * static_cast<float>(M_PI) / 180.f);
	float y = length * sin(rotation * static_cast<float>(M_PI) / 180.f);
	return Vector2D(x, y);
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

Vector2D Vector2D::operator+(const Vector2D& other)
{
	return Vector2D(m_x + other.x(), m_y + other.y());
}

Vector2D Vector2D::operator-(const Vector2D& other) 
{
	return Vector2D(m_x - other.x(), m_y - other.y());
}

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

Vector2D Vector2D::operator*(float other)
{
	return Vector2D(m_x * other, m_y * other);
}

std::ostream& operator<<(std::ostream& os, Vector2D& other)
{
	return os << std::fixed << std::setprecision(3) << "( " << other.x() << ", " << other.y() << " )";
}
