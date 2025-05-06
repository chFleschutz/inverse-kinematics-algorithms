#include "Vector2.h"

Vector2& Vector2::normalize() 
{
	float length = this->length();
	m_x = m_x / length;
	m_y = m_y / length;
	return *this;
}

Vector2 Vector2::makeVector(float length, float rotation)
{
	return Vector2(length * cos(rotation), length * sin(rotation));
}

float Vector2::length() const
{
	return sqrt((m_x * m_x) + (m_y * m_y)); 
}

Vector2& Vector2::operator+=(Vector2 other)
{
	m_x += other.x();
	m_y += other.y();
	return *this;
}

Vector2& Vector2::operator-=(Vector2 other)
{
	m_x -= other.x();
	m_y -= other.y();
	return *this;
}
