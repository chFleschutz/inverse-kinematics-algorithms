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

	// Returns the Position of the Skeleten 
	inline Vector2D getPosition() { return m_position; }

	// Returns the Position of the Base of node
	Vector2D& getNodeBasePosition(SkeletonNode* node);

	// Returns the Pivot-Position of the last node
	Vector2D& getPivotPosition();
	
	void print();

private:
	SkeletonNode* m_root;
	Vector2D m_position;
};

