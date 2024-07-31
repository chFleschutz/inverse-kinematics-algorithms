#pragma once

#include "Skeleton.h"
#include "Vector2.h"

/// @brief Base class for Inverse Kinematics Solvers
/// @note Each derived class has to implements solve() with an IK algorithm
class IKSolver
{
public:
	IKSolver() = default;
	virtual ~IKSolver() = default;

	/// @brief Interface to solve the inverse kinematics problem
	/// @param skeleton The skeleton to solve
	/// @param targetPos The target position to reach
	/// @param maxIterations The maximum number of iterations to solve the problem
	/// @param epsilon The maximum deviation from the target position
	/// @return Returns true if the end effector is within epsilon from the target before max iterations are reached else returns false
	virtual bool solve(Skeleton& skeleton, const Vector2& targetPos, int maxIterations, float epsilon) = 0;
};