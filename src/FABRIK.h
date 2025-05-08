#pragma once

#include "IKSolver.h"

/// @brief Implementation of the Forward And Backward Reaching Inverse Kinematics (FABRIK) algorithm for solving inverse kinematics
class FABRIK : public IKSolver
{
public:
	/// @brief Trys to set the end effector of the skeleton to the target position by rotating the bones of the skeleton
	virtual bool solve(Skeleton& skeleton, const glm::vec2& targetPos, int maxIterations, float epsilon) override
	{
		std::vector<glm::vec2> jointPositions = skeleton.computeJointPositions();
		for (int iter = 0; iter < maxIterations; iter++)
		{
			// Forward Reaching Inverse Kinematics
			jointPositions.back() = targetPos;
			for (int32_t i = static_cast<int32_t>(skeleton.boneCount() - 1); i > 0; i--)
			{
				float boneLength = skeleton.bone(i).length;
				glm::vec2 jointVec = glm::normalize(jointPositions[i + 1] - jointPositions[i]);
				jointPositions[i] = jointPositions[i + 1] - (jointVec * boneLength);
			}

			// Backward Reaching Inverse Kinematics
			jointPositions.front() = glm::vec2{ 0.0f };
			for (int32_t i = 1; i < static_cast<int32_t>(skeleton.boneCount() - 1); i++)
			{
				float boneLength = skeleton.bone(i - 1).length;
				glm::vec2 jointVec = glm::normalize(jointPositions[i] - jointPositions[i - 1]);
				jointPositions[i] = jointPositions[i - 1] + (jointVec * boneLength);
			}

			// Update bone angles
			glm::vec2 lastVec{ 1.0f, 0.0f };
			for (int32_t i = 0; i < static_cast<int32_t>(skeleton.boneCount()); i++)
			{
				glm::vec2 vec = glm::normalize(jointPositions[i + 1] - jointPositions[i]);
				skeleton.bone(i).angle = acos(glm::dot(lastVec, vec));
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
