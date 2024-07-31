#include "Skeleton.h"

#include <iostream>
#include <iomanip>

Skeleton& Skeleton::addBone(float length, float angle)
{
	m_bones.emplace_back(std::make_unique<Bone>(m_pivot, nullptr, length, angle));
	auto bone = m_bones.back().get();
	if (m_root == nullptr)
	{
		m_root = bone;
		m_pivot = bone;
	}
	else
	{
		m_pivot->child = bone;
		m_pivot = bone;
	}

	return *this;
}

Vector2 Skeleton::boneBasePosition(Bone* node)
{
	auto currentBone = m_root;
	float currentAngle = 0.0f;
	Vector2 basePosition = m_position;
	while (currentBone != node && currentBone != nullptr)
	{
		currentAngle += currentBone->angle;
		basePosition += Vector2::makeVector(currentBone->length, currentAngle);
		currentBone = currentBone->child;
	}

	return basePosition;
}

// Calculates the Pivot Position by iterating trought Nodes and adding their lengths 
Vector2 Skeleton::pivotPosition()
{
	auto currentBone = m_root;
	float currentAngle = 0.0f;
	Vector2 pivotPos = m_position;
	while (currentBone != nullptr)
	{
		currentAngle += currentBone->angle;
		pivotPos += Vector2::makeVector(currentBone->length, currentAngle);
		currentBone = currentBone->child;
	}

	return pivotPos;
}

void Skeleton::print()
{
	int indentation = 10;
	auto bone = m_root;
	while (bone != nullptr)
	{
		std::cout << std::setprecision(3) << std::fixed << "\tangle:  " << bone->angle << ", length: " << bone->length << "\n";

		bone = bone->child;
		indentation += 5;
	}
	std::cout << std::endl;
}
