#include "Vector2.h"

#include <cmath>
#include <numbers>
#include <iomanip>

Vector2& Vector2::normalize() 
{
	float length = this->length();
	m_x = m_x / length;
	m_y = m_y / length;
	return *this;
}

void Vector2::print() const 
{
	std::cout << "( " << m_x << ", " << m_y << " )" << std::endl;
}

Vector2 Vector2::makeVector(float length, float rotation)
{
	float x = length * cos(rotation * std::numbers::pi / 180.f);
	float y = length * sin(rotation * std::numbers::pi / 180.f);
	return Vector2(x, y);
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

std::ostream& operator<<(std::ostream& os, Vector2& other)
{
	return os << std::fixed << std::setprecision(3) << "( " << other.x() << ", " << other.y() << " )";
}
