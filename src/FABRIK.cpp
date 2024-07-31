#include "FABRIK.h"

#include <vector>
#include <numbers>


FABRIK::FABRIK(Skeleton* skeleton, const Vector2& target) : IKSolver(skeleton, target)
{
}

bool FABRIK::solve(int maxIterations, float epsilon)
{
	Bone* node;
	auto boneCount = m_skeleton->numOfBones();
	std::vector<Vector2> jointPos(boneCount + 1);

	// Save Joint Positions
	node = m_skeleton->rootBone();
	jointPos[0] = m_skeleton->position();
	for (int i = 1; i < boneCount + 1; i++)
	{
		jointPos[i] = jointPos[i - 1] + Vector2::makeVector(node->length, node->angle);
		node = node->child;
	}

	for (int i = 0; i < maxIterations; i++)
	{
		// Forward Reaching Inverse Kinematik
		node = m_skeleton->pivotBone();
		jointPos[boneCount] = m_targetPos;
		for (size_t j = boneCount - 1; j > 0; j--)
		{
			// Vector from last base to current Base with the length of the bone
			Vector2 vec = (jointPos[j] - jointPos[j + 1]).normalize() * node->length;
			// Set the joint Pos
			jointPos[j] = jointPos[j + 1] + vec;
			// Set Node to the previous Bone
			node = node->parent;
		}

		// Backward Reaching Inverse Kinematik
		node = m_skeleton->rootBone();
		jointPos[0] = m_skeleton->position();
		for (int k = 1; k < boneCount - 1; k++)
		{
			// Vector from last Base to current Base with the length of the bone
			Vector2 vec = (jointPos[k] - jointPos[k - 1]).normalize() * node->length;
			jointPos[k] = jointPos[k - 1] + vec; 

			node = node->child;
		}

		// Rotate Bones in the Skeleton
		node = m_skeleton->rootBone();
		Vector2 lastVec = Vector2(1, 0);
		for (int l = 1; l < boneCount + 1; l++)
		{
			// Vector which represents the Bone direction
			Vector2 vec = (jointPos[l] - jointPos[l - 1]).normalize();
			// Angle between last bone and current bone
			float rotateAngle = acos(lastVec.dot(vec)) * 180.0f / std::numbers::pi_v<float>;
			node->angle = rotateAngle;

			lastVec = vec;
			node = node->child;
		}

		// Return if Pivot is near enougth to the Target
		if ((m_targetPos - m_skeleton->pivotPosition()).length() < epsilon) 
			return true;
	}

	// Algorithm finished by reaching maxIter -> pivot not near enough to the target
	return false;
}
