#pragma once

#include "IKSolver.h"

#include <numbers>
#include <cmath>
#include <ranges>

/// @brief Implementation of the Cyclic Coordinated Descend (CCD) algorithm for solving inverse kinematics
class CCD : public IKSolver
{
public:
	/// @brief Trys to set the end effector of the skeleton to the desired target position by rotating the bones of the skeleton
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

		for (int32_t i = 0; i < maxIterations; i++)
		{
			// Adjust rotation of each bone in the skeleton
			for (int32_t i = static_cast<int32_t>(skeleton.boneCount()); i > 0; i--)
			{
				std::vector<glm::vec2> joints = skeleton.computeJointPositions();
				glm::vec2 pivotPos = joints.back();
				glm::vec2 currentBasePos = joints[i - 1];
				glm::vec2 basePivotVec = glm::normalize(pivotPos - currentBasePos);
				glm::vec2 baseTargetVec = glm::normalize(targetPos - currentBasePos);
				float dot = glm::dot(basePivotVec, baseTargetVec);
				float det = basePivotVec.x * baseTargetVec.y - basePivotVec.y * baseTargetVec.x;
				skeleton.bone(i - 1).angle += atan2(det, dot);;
			}

			// Return if pivot is near enought to the target -> success
			if ((targetPos - skeleton.computePivotPosition()).length() < epsilon)
				return true;
		}

		// Algorithm finished by reaching max Iterations -> pivot is not near enough to the target
		return false;
	}
};
