#include "CCD.h"

CCD::CCD()
{
	m_skeleton = nullptr;
	m_targetPos = Vector2D(0.0f, 0.0f);
}

CCD::CCD(Skeleton* skeleton, Vector2D target)
{
	m_skeleton = skeleton;
	m_targetPos = target;
}

Skeleton* CCD::getSkeleton()
{
	return m_skeleton;
}

void CCD::setTargetPosition(float tx, float ty)
{
	m_targetPos = Vector2D(tx, ty);
}

bool CCD::apply(const int maxIter, const float eps)
{
	// Check if skeleton is set
	if (m_skeleton == nullptr) return false;
	
	// Iterate until maxIter is reached
	for (int i = 0; i < maxIter; i++)
	{
		// Find Last-Element in Skeleton
		SkeletonNode* node = m_skeleton->getRoot();
		while (node->getChild() != nullptr)
		{
			node = node->getChild();
		}

		// Do for each node of the skeleton
		while (node != nullptr)
		{
			// Calculating Vectors
			Vector2D pivotPos = m_skeleton->getPivotPosition();
			Vector2D currrentBasePos = m_skeleton->getNodeBasePosition(node);
			Vector2D basePivotVec = (pivotPos - currrentBasePos).normalize();
			Vector2D baseTargetVec = (m_targetPos - currrentBasePos).normalize();

			// Angle between BasePivotVec and BaseTargetVec
			float rotateAngle = acos(basePivotVec.dot(baseTargetVec)) * 180.0f / M_PI;
			if (basePivotVec.cross(baseTargetVec) < 0.0f) rotateAngle *=  -1.0f;
	
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
