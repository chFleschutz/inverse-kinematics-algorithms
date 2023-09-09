#pragma once

#include "Skeleton.h"
#include "Vector2D.h"

class FABRIK
{
public:
	/// @brief Creates a solver for the Forward And Backward Reaching Inverse Kinematics (FABRIK) algorithm
	/// @param skeleton Pointer to the skeleton which should be solved
	/// @param target Target position of the end effector
	FABRIK(Skeleton* skeleton, const Vector2D& target);

	/// @brief Set a new target position for the end effector
	/// @param targetPos New target position
	void setTargetPosition(const Vector2D& targetPos) { m_targetPos = targetPos; }

	/// @brief Trys to set the end effector of the skeleton to the target position by rotating the bones of the skeleton
	/// @param maxItererations Max iterations of the algorithm
	/// @param epsilon Max deviation from the target position
	/// @return Returns true if the end effector is within epsilon from the target before max Iterations are reached else returns false
	bool apply(int maxItererations, float epsilon);

private:
	Skeleton* m_skeleton;
	Vector2D m_targetPos;
};

