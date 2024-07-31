#pragma once

#include "IKSolver.h"
#include "Skeleton.h"
#include "Vector2.h"

/// @brief Implementation of the Forward And Backward Reaching Inverse Kinematics (FABRIK) algorithm
class FABRIK : public IKSolver
{
public:
	/// @brief Creates a solver for the Forward And Backward Reaching Inverse Kinematics (FABRIK) algorithm
	/// @param skeleton Pointer to the skeleton which should be manipulated
	/// @param target Desired target position of the end effector
	FABRIK(Skeleton* skeleton, const Vector2& target = Vector2(0.0f, 0.0f));

	/// @brief Trys to set the end effector of the skeleton to the target position by rotating the bones of the skeleton
	/// @param maxItererations Max iterations of the algorithm
	/// @param epsilon Max deviation from the target position
	/// @return Returns true if the end effector is within epsilon from the target before max iterations are reached else returns false
	bool solve(int maxItererations, float epsilon) override;
};

