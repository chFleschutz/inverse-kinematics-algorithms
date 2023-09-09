#include "CCD.h"

CCD::CCD(Skeleton* skeleton, const Vector2D& target)
{
	m_skeleton = skeleton;
	m_targetPos = target;
}

bool CCD::apply(const int maxIter, const float eps)
{
	// Check if skeleton is set
	if (m_skeleton == nullptr) return false;

	// Find Last-Element in Skeleton
	Bone* lastNode = m_skeleton->rootBone();
	while (lastNode->getChild() != nullptr)
	{
		lastNode = lastNode->getChild();
	}

	// Iterate until maxIter is reached
	for (int i = 0; i < maxIter; i++)
	{
		Bone* node = lastNode;

		// Do for each node of the skeleton
		while (node != nullptr)
		{
			// Calculating Vectors
			Vector2D pivotPos = m_skeleton->getPivotPosition();
			Vector2D currrentBasePos = m_skeleton->boneBasePosition(node);
			Vector2D basePivotVec = (pivotPos - currrentBasePos).normalize();
			Vector2D baseTargetVec = (m_targetPos - currrentBasePos).normalize();

			// Angle between BasePivotVec and BaseTargetVec
			float rotateAngle = acos(basePivotVec.dot(baseTargetVec)) * 180.0f / M_PI;
			if (basePivotVec.cross(baseTargetVec) < 0.0f) rotateAngle *= -1.0f;

			// Rotate Bone in direction of the Pivot
			node->setAngle(node->getAngle() + rotateAngle);

			// Set node to its parent
			node = node->getParent();
		}
		// If Pivot is near enought to the Target return true
		if ((m_targetPos - m_skeleton->getPivotPosition()).length() < eps) return true;

		//m_skeleton->print();
	}
	// If the max Interations are reached without the Pivot being near enough the Target return false
	return false;
}


