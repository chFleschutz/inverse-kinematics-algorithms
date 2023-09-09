#pragma once
#include "Vector2D.h"

class Bone
{
public:
	Bone();
	Bone(float length, float angle);
	~Bone();

	/// @brief Adds child as the child-pointer
	void addChild(Bone* child);
	/// @brief Returns the child bone
	Bone* child() { return m_child; }
	/// @brief Returns the parent bone
	Bone* parent() { return m_parent; }

	/// @brief Sets the length of the bone
	void setLength(float length) { m_length = length; }
	/// @brief Returns the length of the bone
	float length() { return m_length; }

	/// @brief Sets the rotation angle of the bone
	void setAngle(float angle) { m_angle = angle; }
	/// @brief Returns the rotation angle of the bone
	float angle() { return m_angle; }

	/// @brief Prints the bone indented according to its position in the bone chain
	void print(int indentDepth);

private:
	Bone* m_child;
	Bone* m_parent;
	float m_length;
	float m_angle;
};
