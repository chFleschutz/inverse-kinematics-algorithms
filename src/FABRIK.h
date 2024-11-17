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

		// Save positions of each joint in the skeleton
		Bone* node = skeleton.rootBone();
		for (size_t i = 1; i < boneCount + 1; i++)
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
				// Vector from next joint to current joint
				Vector2 vec = (jointPos[j] - jointPos[j + 1]).normalize();
				jointPos[j] = jointPos[j + 1] + (vec * node->length);
				node = node->parent;
			}

			// Backward Reaching Inverse Kinematik
			node = skeleton.rootBone();
			jointPos[0] = Vector2(0.0f, 0.0f);
			for (size_t k = 1; k < boneCount - 1; k++)
			{
				// Vector from previous joint to current joint
				Vector2 vec = (jointPos[k] - jointPos[k - 1]).normalize();
				jointPos[k] = jointPos[k - 1] + (vec * node->length);
				node = node->child;
			}

			// Adjust rotation of each bone in the skeleton based on the new joint positions
			node = skeleton.rootBone();
			Vector2 lastVec(1.0f, 0.0f);
			for (size_t l = 1; l < boneCount + 1; l++)
			{
				Vector2 vec = (jointPos[l] - jointPos[l - 1]).normalize();
				node->angle = acos(lastVec.dot(vec));

				lastVec = vec;
				node = node->child;
			}

			// Return if Pivot is near enougth to the target
			if ((targetPos - skeleton.pivotPosition()).length() < epsilon)
				return true;
		}

		// Algorithm finished by reaching maxIterations -> pivot is not near enough to the target
		return false;
	}
};
