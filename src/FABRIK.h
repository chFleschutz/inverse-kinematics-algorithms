#pragma once

#include "IKSolver.h"

/// @brief Implementation of the Forward And Backward Reaching Inverse Kinematics (FABRIK) algorithm for solving inverse kinematics
class FABRIK : public IKSolver
{
public:
	/// @brief Trys to set the end effector of the skeleton to the target position by rotating the bones of the skeleton
	virtual bool solve(Skeleton& skeleton, const Vector2& targetPos, int maxIterations, float epsilon) override
	{
		auto boneCount = skeleton.numOfBones();
		std::vector<Vector2> jointPos(boneCount + 1);

		// Save Joint Positions
		Bone* node = skeleton.rootBone();
		jointPos[0] = skeleton.position();
		for (int i = 1; i < boneCount + 1; i++)
		{
			jointPos[i] = jointPos[i - 1] + Vector2::makeVector(node->length, node->angle);
			node = node->child;
		}

		for (int i = 0; i < maxIterations; i++)
		{
			// Forward Reaching Inverse Kinematik
			node = skeleton.pivotBone();
			jointPos[boneCount] = targetPos;
			for (size_t j = boneCount - 1; j > 0; j--)
			{
				// Vector from last base to current Base with the length of the bone
				Vector2 vec = (jointPos[j] - jointPos[j + 1]).normalize() * node->length;
				jointPos[j] = jointPos[j + 1] + vec;
				node = node->parent;
			}

			// Backward Reaching Inverse Kinematik
			node = skeleton.rootBone();
			jointPos[0] = skeleton.position();
			for (int k = 1; k < boneCount - 1; k++)
			{
				// Vector from last Base to current Base with the length of the bone
				Vector2 vec = (jointPos[k] - jointPos[k - 1]).normalize() * node->length;
				jointPos[k] = jointPos[k - 1] + vec;

				node = node->child;
			}

			// Rotate Bones in the Skeleton
			node = skeleton.rootBone();
			Vector2 lastVec = Vector2(1, 0);
			for (int l = 1; l < boneCount + 1; l++)
			{
				Vector2 vec = (jointPos[l] - jointPos[l - 1]).normalize();
				float rotateAngle = acos(lastVec.dot(vec));
				node->angle = rotateAngle;

				lastVec = vec;
				node = node->child;
			}

			// Return if Pivot is near enougth to the Target
			if ((targetPos - skeleton.pivotPosition()).length() < epsilon)
				return true;
		}

		// Algorithm finished by reaching max Iterations -> pivot is not near enough to the target
		return false;
	}
};

