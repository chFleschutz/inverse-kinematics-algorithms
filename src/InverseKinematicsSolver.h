#pragma once

#include "Skeleton.h"
#include "Vector2D.h"

/// @brief Base class for Inverse Kinematics Solvers
/// @note Each derived class has to implements solve() with a IK algorithm
class InverseKinematicsSolver
{
public:
	/// @brief Creates a solver for the Cyclic Coordinated Descend (CCD) algorithm
	/// @param skeleton Pointer to the skeleton which should be solved
	/// @param target Target position of the end effector
	InverseKinematicsSolver(Skeleton* skeleton, const Vector2D& target = Vector2D(0.0f, 0.0f));

	/// @brief Set a new target position for the end effector
	/// @param targetPos New target position
	void setTargetPosition(const Vector2D& targetPos) { m_targetPos = targetPos; }

	/// @brief Interface to solve the inverse kinematics problem
	/// @note Derived classes for implementations
	virtual bool solve(int maxItererations, float epsilon) = 0;

protected:
	Skeleton* m_skeleton;
	Vector2D m_targetPos;
};