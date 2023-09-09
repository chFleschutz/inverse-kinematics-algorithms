#include "FABRIK.h"

#include <vector>

FABRIK::FABRIK(Skeleton* skeleton, const Vector2D& target)
{
	m_skeleton = skeleton;
	m_targetPos = target;
}

bool FABRIK::apply(int maxIterations, float epsilon)
{
	Bone* node;
	const int boneCount = m_skeleton->numOfBones();
	std::vector<Vector2D> jointPos(boneCount + 1);

	// Save Joint Positions
	node = m_skeleton->rootBone();
	jointPos[0] = m_skeleton->rootPosition();
	for (int i = 1; i < boneCount + 1; i++)
	{
		jointPos[i] = jointPos[i - 1] + Vector2D::makeVector(node->length(), node->angle());
		node = node->child();
	}

	for (int i = 0; i < maxIterations; i++)
	{
		// Forward Reaching Inverse Kinematik
		node = m_skeleton->pivotBone();
		jointPos[boneCount] = m_targetPos;
		for (int j = boneCount - 1; j > 0; j--)
		{
			// Vector from last base to current Base with the length of the bone
			Vector2D vec = (jointPos[j] - jointPos[j + 1]).normalize() * node->length();
			// Set the joint Pos
			jointPos[j] = jointPos[j + 1] + vec;
			// Set Node to the previous Bone
			node = node->parent();
		}

		// Backward Reaching Inverse Kinematik
		node = m_skeleton->rootBone();
		jointPos[0] = m_skeleton->rootPosition();
		for (int k = 1; k < boneCount - 1; k++)
		{
			// Vector from last Base to current Base with the length of the bone
			Vector2D vec = (jointPos[k] - jointPos[k - 1]).normalize() * node->length();
			jointPos[k] = jointPos[k - 1] + vec; 

			node = node->child();
		}

		// Rotate Bones in the Skeleton
		node = m_skeleton->rootBone();
		Vector2D lastVec = Vector2D(1, 0);
		for (int l = 1; l < boneCount + 1; l++)
		{
			// Vector which represents the Bone direction
			Vector2D vec = (jointPos[l] - jointPos[l - 1]).normalize();
			// Angle between last bone and current bone
			float rotateAngle = acos(lastVec.dot(vec)) * 180.0f / static_cast<float>(M_PI);
			node->setAngle(rotateAngle);

			lastVec = vec;
			node = node->child();
		}

		// Return if Pivot is near enougth to the Target
		if ((m_targetPos - m_skeleton->pivotPosition()).length() < epsilon) return true;
	}

	// Algorithm finished by reaching maxIter -> pivot not near enough to the target
	return false;
}
