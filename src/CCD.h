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
		for (int i = 0; i < maxIterations; i++)
		{
			// Adjust rotation of each bone in the skeleton
			std::vector<glm::vec2> jointPositions = skeleton.computeJointPositions();
			for (int32_t i = static_cast<int32_t>(jointPositions.size() - 1); i > 0; i--)
			{
				glm::vec2 pivotPos = jointPositions.back();
				glm::vec2 currentBasePos = jointPositions[i - 1];
				glm::vec2 basePivotVec = glm::normalize(pivotPos - currentBasePos);
				glm::vec2 baseTargetVec = glm::normalize(targetPos - currentBasePos);
				float dot = glm::dot(basePivotVec, baseTargetVec);
				float det = basePivotVec.x * baseTargetVec.y - basePivotVec.y * baseTargetVec.x;
				float rotateAngle = atan2(det, dot);

				skeleton.bone(i - 1).angle += rotateAngle;
			}

			// Return if pivot is near enought to the target -> success
			if ((targetPos - skeleton.computePivotPosition()).length() < epsilon)
				return true;
		}

		// Algorithm finished by reaching max Iterations -> pivot is not near enough to the target
		return false;
	}
};
