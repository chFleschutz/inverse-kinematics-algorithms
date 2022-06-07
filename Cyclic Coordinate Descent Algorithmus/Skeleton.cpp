#include "Skeleton.h"


Skeleton::Skeleton() 
{
	m_root = nullptr;
	m_position = Vector2D(0.0f, 0.0f);
}

Skeleton::Skeleton(Vector2D position)
{
	m_root = nullptr;
	m_position = position;
}

Skeleton::~Skeleton() {
	if (m_root)	delete m_root;
}

SkeletonNode* Skeleton::getJoint(int index) {
	int idx = 0;
	return m_root->getJoint(idx, index);
}

// Calculates the Pivot Position by iterating trought Nodes and adding their lengths 
Vector2D& Skeleton::getPivotPosition()
{
	if (m_root == nullptr) return m_position;

	SkeletonNode* currentNode = m_root;
	Vector2D pivotPos = m_position;
	float currentAngle = 0.0f;

	// Iterate through all Nodes
	while (currentNode != nullptr)
	{
		currentAngle += currentNode->getAngle();
		pivotPos += Vector2D(currentNode->getLength() * cos(currentAngle * M_PI / 180), currentNode->getLength() * sin(currentAngle * M_PI / 180));
		currentNode = currentNode->getChild();
	} 
	return pivotPos;
}

int Skeleton::getNumOfNodes()
{
	int boneCount = 0;
	SkeletonNode* node = m_root;
	while (node != nullptr)
	{
		boneCount++;
		node = node->getChild();
	}
	return boneCount;
}

void Skeleton::print() {
	if (m_root) m_root->print(0);
}
