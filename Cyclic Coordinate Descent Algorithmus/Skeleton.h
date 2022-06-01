#pragma once
#include "SkeletonNode.h"

class Skeleton {
public:
	Skeleton();
	~Skeleton();

	inline void setRoot(SkeletonNode* root) { m_root = root; }
	inline SkeletonNode* getRoot() { return m_root; }
	SkeletonNode* getJoint(int index);
	void print();

private:
	SkeletonNode* m_root;
};

