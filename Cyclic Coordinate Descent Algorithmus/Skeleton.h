#pragma once
#include "SkeletonNode.h"
#include "Vector2D.h"

class Skeleton {
public:
	Skeleton();
	Skeleton(Vector2D position);
	~Skeleton();

	inline void setRoot(SkeletonNode* root) { m_root = root; }
	inline SkeletonNode* getRoot() { return m_root; }

	inline Vector2D getPosition() { return m_position; }

	Vector2D& getNodeBasePosition(SkeletonNode* node);

	SkeletonNode* getJoint(int index);
	Vector2D& getPivotPosition();

	int getNumOfNodes();
	
	void print();

private:
	SkeletonNode* m_root;
	Vector2D m_position;
};

