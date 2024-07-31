#include "CCD.h"

#include <numbers>

CCD::CCD(Skeleton* skeleton, const Vector2& target) : IKSolver(skeleton, target)
{
}

bool CCD::solve(const int maxIter, const float eps)
{
	// Check if skeleton is set
	if (m_skeleton == nullptr) 
		return false;

	// Find Last-Element in Skeleton
	Bone* lastNode = m_skeleton->rootBone();
	while (lastNode->child != nullptr)
	{
		lastNode = lastNode->child;
	}

	// Iterate until maxIter is reached
	for (int i = 0; i < maxIter; i++)
	{
		Bone* node = lastNode;

		// Do for each node of the skeleton
		while (node != nullptr)
		{
			// Calculating Vectors
			Vector2 pivotPos = m_skeleton->pivotPosition();
			Vector2 currrentBasePos = m_skeleton->boneBasePosition(node);
			Vector2 basePivotVec = (pivotPos - currrentBasePos).normalize();
			Vector2 baseTargetVec = (m_targetPos - currrentBasePos).normalize();

			// Angle between BasePivotVec and BaseTargetVec
			float rotateAngle = acos(basePivotVec.dot(baseTargetVec)) * 180.0f / std::numbers::pi_v<float>;
			if (basePivotVec.cross(baseTargetVec) < 0.0f) rotateAngle *= -1.0f;

			// Rotate Bone in direction of the Pivot
			node->angle = node->angle + rotateAngle;

			// Set node to its parent
			node = node->parent;
		}
		// If Pivot is near enought to the Target return true
		if ((m_targetPos - m_skeleton->pivotPosition()).length() < eps) 
			return true;
	}
	// If the max Interations are reached without the Pivot being near enough the Target return false
	return false;
}


