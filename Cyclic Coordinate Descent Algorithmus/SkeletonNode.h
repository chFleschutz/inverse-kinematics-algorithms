#pragma once
#include <vector>

class SkeletonNode {
public:
	SkeletonNode();
	~SkeletonNode();

	void addChild(SkeletonNode* c);
	SkeletonNode* getJoint(int& index, const int searchIndex);
	void setAngle(float angle) { m_angle = angle; }
	float getAngle() { return m_angle; }
	void print(int einruecktiefe);

private:
	SkeletonNode* m_child;
	SkeletonNode* m_parent;
	float m_angle;
};
