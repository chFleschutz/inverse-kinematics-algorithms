#pragma once

#include "IKSolver.h"

/// @brief Implementation of the Forward And Backward Reaching Inverse Kinematics (FABRIK) algorithm for solving inverse kinematics
class FABRIK : public IKSolver
{
public:
	/// @brief Trys to set the end effector of the skeleton to the target position by rotating the bones of the skeleton
	virtual bool solve(Skeleton& skeleton, const glm::vec2& targetPos, int maxIterations, float epsilon) override
	{
		// Check if the target is reachable
		if (skeleton.maxReach() < glm::length(targetPos))
		{
			skeleton.bone(0).angle = atan2(targetPos.y, targetPos.x);
			for (int32_t i = 1; i < static_cast<int32_t>(skeleton.boneCount()); i++)
			{
				skeleton.bone(i).angle = 0.0f;
			}
			return false;
		}

		std::vector<glm::vec2> joints = skeleton.computeJointPositions();
		int32_t tipJointIndex = static_cast<int32_t>(joints.size() - 1);
		bool targetReached = false;
		for (int iter = 0; iter < maxIterations; iter++)
		{
			// Forward Reaching - adjust from the end effector
			joints.back() = targetPos;
			for (int32_t i = tipJointIndex - 1; i > 0; i--)
			{
				glm::vec2& currentJoint = joints[i];
				const glm::vec2& nextJoint = joints[i + 1];
				currentJoint = nextJoint + glm::normalize(currentJoint - nextJoint) * skeleton.bone(i).length;
			}

			// Backward Reaching - adjust from the root
			joints.front() = glm::vec2{ 0.0f };
			for (int32_t i = 1; i <= tipJointIndex; i++)
			{
				glm::vec2& currentJoint = joints[i];
				const glm::vec2& prevJoint = joints[i - 1];
				currentJoint = prevJoint + glm::normalize(currentJoint - prevJoint) * skeleton.bone(i - 1).length;
			}

			// Break if close enough to the target
			if (glm::length(joints.back() - targetPos) < epsilon)
			{
				targetReached = true;
				break;
			}
		}

		// Update bone angles
		glm::vec2 lastVec{ 1.0f, 0.0f };
		for (int32_t i = 0; i < static_cast<int32_t>(skeleton.boneCount()); i++)
		{
			glm::vec2 vec = glm::normalize(joints[i + 1] - joints[i]);
			skeleton.bone(i).angle = atan2(vec.y, vec.x) - atan2(lastVec.y, lastVec.x);
			lastVec = vec;
		}

		return targetReached;
	}
};
