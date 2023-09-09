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
	if (m_root)
		delete m_root;
}

Bone* Skeleton::pivotBone()
{
	Bone* node = m_root;
	while (node->child() != nullptr)
	{
		node = node->child();
	}
	return node;
}

Vector2D Skeleton::boneBasePosition(Bone* node)
{
	Bone* currentNode = m_root;
	Vector2D position = m_position;
	float angle = 0.0f;
	while (currentNode != node)
	{
		if (currentNode == nullptr) break;

		angle += currentNode->angle();
		position += Vector2D::makeVector(currentNode->length(), angle);
		currentNode = currentNode->child();
	}
	return position;
}

// Calculates the Pivot Position by iterating trought Nodes and adding their lengths 
Vector2D Skeleton::pivotPosition()
{
	if (m_root == nullptr) return m_position;

	Bone* currentBone = m_root;
	Vector2D pivotPos = m_position;
	float currentAngle = 0.0f;

	// Iterate through all Nodes
	while (currentBone != nullptr)
	{
		currentAngle += currentBone->angle();
		//float x = currentBone->length() * cos(currentAngle * static_cast<float>(M_PI) / 180.f);
		//float y = currentBone->length() * sin(currentAngle * static_cast<float>(M_PI) / 180.f);
		//pivotPos += Vector2D(x, y);
		pivotPos += Vector2D::makeVector(currentBone->length(), currentAngle);
		currentBone = currentBone->child();
	}
	return pivotPos;
}

int Skeleton::numOfBones()
{
	Bone* node = m_root;
	int boneCount = 0;
	while (node != nullptr)
	{
		node = node->child();
		boneCount++;
	}
	return boneCount;
}

void Skeleton::print()
{
	if (m_root) m_root->print(0);
}
