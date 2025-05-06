#pragma once

#include "IKSolver.h"

/// @brief Implementation of the Forward And Backward Reaching Inverse Kinematics (FABRIK) algorithm for solving inverse kinematics
class FABRIK : public IKSolver
{
public:
	/// @brief Trys to set the end effector of the skeleton to the target position by rotating the bones of the skeleton
	virtual bool solve(Skeleton& skeleton, const Vector2& targetPos, int maxIterations, float epsilon) override
	{
		std::vector<Vector2> jointPositions = skeleton.computeJointPositions();
		for (int i = 0; i < maxIterations; i++)
		{
			// Forward Reaching Inverse Kinematics
			jointPositions.back() = targetPos;
			for (size_t j = skeleton.boneCount() - 1; j > 0; j--)
			{
				float boneLength = skeleton.bone(BoneHandle{ j }).length;
				Vector2 jointVec = (jointPositions[j + 1] - jointPositions[j]).normalize();
				jointPositions[j] = jointPositions[j + 1] - (jointVec * boneLength);
			}

			// Backward Reaching Inverse Kinematics
			jointPositions.front() = Vector2(0.0f, 0.0f);
			for (size_t j = 1; j < skeleton.boneCount() - 1; j++)
			{
				float boneLength = skeleton.bone(BoneHandle{ j - 1 }).length;
				Vector2 jointVec = (jointPositions[j] - jointPositions[j - 1]).normalize();
				jointPositions[j] = jointPositions[j - 1] + (jointVec * boneLength);
			}

			// Update bone angles
			Vector2 lastVec(1.0f, 0.0f);
			for (size_t j = 0; j < skeleton.boneCount(); j++)
			{
				Vector2 vec = (jointPositions[j + 1] - jointPositions[j]).normalize();
				skeleton.bone(BoneHandle{ j }).angle = acos(lastVec.dot(vec));
				lastVec = vec;
			}

			// Return if Pivot is near enougth to the target
			if ((targetPos - skeleton.computePivotPosition()).length() < epsilon)
				return true;
		}

		// Algorithm finished by reaching max Iterations -> pivot is not near enough to the target
		return false;
	}
};
