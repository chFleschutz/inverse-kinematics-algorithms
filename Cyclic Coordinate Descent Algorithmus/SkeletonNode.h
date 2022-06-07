#pragma once
#include "Vector2D.h"

class SkeletonNode {
public:
	SkeletonNode();
	SkeletonNode(float length, float angle);
	~SkeletonNode();

	void addChild(SkeletonNode* child);
	inline SkeletonNode* getChild() { return m_child; }
	inline SkeletonNode* getParent() { return m_parent; }

	SkeletonNode* getJoint(int& index, const int searchIndex);

	inline void setLength(float length) { m_length = length; }
	inline float getLength() { return m_length; }

	inline void setAngle(float angle) { m_angle = angle; }
	inline float getAngle() { return m_angle; }

	void print(int einruecktiefe);

private:
	SkeletonNode* m_child;
	SkeletonNode* m_parent;
	float m_length;
	float m_angle;
};
