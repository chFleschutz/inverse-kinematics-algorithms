#include "FABRIK.h"

FABRIK::FABRIK(Skeleton* skeleton, const Vector2D& target)
{
	m_skeleton = skeleton;
	m_targetPos = target;
}

bool FABRIK::apply(int maxIter, float eps)
{

	Bone* node;
	const int boneCount = m_skeleton->getNumOfBones();
	Vector2D* jointPos = new Vector2D[boneCount + 1];

	// Save Joint Positions
	node = m_skeleton->rootBone();
	jointPos[0] = m_skeleton->rootPosition();
	for (int i = 1; i < boneCount + 1; i++)
	{
		jointPos[i] = jointPos[i - 1] + Vector2D::makeVector(node->getLength(), node->getAngle());
		node = node->getChild();
	}

	for (int i = 0; i < maxIter; i++)
	{
		// Forward Reaching Inverse Kinematik
		node = m_skeleton->pivotBone();
		jointPos[boneCount] = m_targetPos;
		for (int i = boneCount - 1; i > 0; i--)
		{
			// Vector from last base to current Base with the length of the bone
			Vector2D vec = (jointPos[i] - jointPos[i + 1]).normalize() * node->getLength();
			// Set the joint Pos
			jointPos[i] = jointPos[i + 1] + vec;
			// Set Node to the previous Bone
			node = node->getParent();
		}

		// Backward Reaching Inverse Kinematik
		node = m_skeleton->rootBone();
		jointPos[0] = m_skeleton->rootPosition();
		for (int i = 1; i < boneCount - 1; i++)
		{
			// Vector from last Base to current Base with the length of the bone
			Vector2D vec = (jointPos[i] - jointPos[i - 1]).normalize() * node->getLength();
			jointPos[i] = jointPos[i - 1] + vec;

			node = node->getChild();
		}

		// Rotate Bones in the Skeleton
		node = m_skeleton->rootBone();
		Vector2D lastVec = Vector2D(1, 0);
		for (int i = 1; i < boneCount + 1; i++)
		{
			// Vector which represents the Bone direction
			Vector2D vec = (jointPos[i] - jointPos[i - 1]).normalize();
			// Angle between last bone and current bone
			float rotateAngle = acos(lastVec.dot(vec)) * 180.0f / M_PI;
			node->setAngle(rotateAngle);

			lastVec = vec;
			node = node->getChild();
		}

		// Return if Pivot is near enougth to the Target
		if ((m_targetPos - m_skeleton->getPivotPosition()).length() < eps) return true;
	}

	// Algorithm finished by reaching maxIter -> pivot not near enough to the target
	return false;
}
