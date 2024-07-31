#pragma once

#include "Skeleton.h"
#include "Vector2.h"

/// @brief Base class for Inverse Kinematics Solvers
/// @note Each derived class has to implements solve() with an IK algorithm
class IKSolver
{
public:
	/// @brief Creates a solver for the Cyclic Coordinated Descend (CCD) algorithm
	/// @param skeleton Pointer to the skeleton which should be manipulated
	/// @param target Desired target position of the end effector
	IKSolver(Skeleton* skeleton, const Vector2& target = Vector2(0.0f, 0.0f))
		: m_skeleton(skeleton), m_targetPos(target) {}

	/// @brief Set a new target position for the end effector
	/// @param targetPos New target position
	void setTargetPosition(const Vector2& targetPos) { m_targetPos = targetPos; }

	/// @brief Interface to solve the inverse kinematics problem
	virtual bool solve(int maxItererations, float epsilon) = 0;

protected:
	Skeleton* m_skeleton;
	Vector2 m_targetPos;
};