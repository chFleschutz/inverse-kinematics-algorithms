#include "CCD.h"

CCD::CCD()
{
	m_skeleton = nullptr;
	m_numBones = 0;
	m_targetPos = Vector2D(0.0f, 0.0f);
}

CCD::CCD(Skeleton* skeleton, Vector2D target)
{
	m_skeleton = skeleton;
	m_numBones = m_skeleton->getNumOfNodes();
	m_targetPos = target;
}

Skeleton* CCD::getSkeleton()
{
	return m_skeleton;
}

void CCD::getPivotPositions(int count, Vector2D*& pivot)
{
}

void CCD::setTargetPosition(float tx, float ty)
{
	m_targetPos = Vector2D(tx, ty);
}

bool CCD::apply(const int maxIter, const float eps)
{
	// Check if skeleton is set
	if (m_skeleton == nullptr) return false;
	
	// Iterate till maxIter
	for (int i = 0; i < maxIter; i++)
	{
		// Find Pivot-Element of the Skeleton
		SkeletonNode* node = m_skeleton->getRoot();
		while (node->getChild() != nullptr)
		{
			node = node->getChild();
		}
		
		// Do for each node of the skeleton
		Vector2D basePos = m_skeleton->getPosition();
		
		while (node != nullptr)
		{
			// Calculate current Pivot Position
			Vector2D pivotPos = m_skeleton->getPivotPosition();

			// Vector Pivot-Target
			Vector2D basePivotVec = pivotPos - basePos;

			// Vector Base-Target
			Vector2D baseTargetVec = m_targetPos - basePos;

			// Angle between BasePivotVec and BaseTargetVec
			float rotateAngle = basePivotVec * baseTargetVec;

			// Rotate Bone in direction of the Pivot
			node->setAngle(node->getAngle() + rotateAngle);

			// Set node and base to next child
			basePos += Vector2D::makeVector(node->getLength(), node->getAngle());
			node = node->getParent();
		}
		// If Pivot is near enought to the Target return true
		if ((m_targetPos - m_skeleton->getPivotPosition()).length() < eps) return true;
	}
	// If the max Interations are reached without the Pivot being near enough the Target return false
	return false;
}
