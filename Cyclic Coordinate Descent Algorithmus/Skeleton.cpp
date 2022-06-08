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

Skeleton::~Skeleton() 
{
	if (m_root)	delete m_root;
}

Vector2D& Skeleton::getNodeBasePosition(SkeletonNode* node)
{
	SkeletonNode* currentNode = m_root;
	Vector2D position = m_position;
	float angle = 0.0f;
	while (currentNode != node)
	{
		if (currentNode == nullptr) break;

		angle += currentNode->getAngle();
		position += Vector2D::makeVector(currentNode->getLength(), angle);
		currentNode = currentNode->getChild();
	}
	return position;
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

void Skeleton::print() {
	if (m_root) m_root->print(0);
}
