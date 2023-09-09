#pragma once
#include "Vector2D.h"

class Bone
{
public:
	Bone();
	Bone(float length, float angle);
	~Bone();

	void addChild(Bone* child);
	inline Bone* getChild() { return m_child; }
	inline Bone* getParent() { return m_parent; }

	inline void setLength(float length) { m_length = length; }
	inline float getLength() { return m_length; }

	inline void setAngle(float angle) { m_angle = angle; }
	inline float getAngle() { return m_angle; }

	void print(int einruecktiefe);

private:
	Bone* m_child;
	Bone* m_parent;
	float m_length;
	float m_angle;
};
