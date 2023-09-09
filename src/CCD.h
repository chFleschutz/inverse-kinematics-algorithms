#pragma once
#include <math.h>
#include "skeleton.h"
#include "vector2d.h"

class CCD
{

public:
	/// @brief Creates a solver for the Cyclic Coordinated Descend (CCD) algorithm
	/// @param skeleton Pointer to the skeleton which should be solved
	/// @param target Target position of the end effector
	CCD(Skeleton* skeleton, const Vector2D& target = Vector2D(0.0f, 0.0f));

	/// @brief Set a new target position for the end effector
	/// @param targetPos New target position
	void setTargetPosition(const Vector2D& targetPos) { m_targetPos = targetPos; }

	/// @brief Trys to set the end effector of the skeleton to the target position by rotating the bones of the skeleton
	/// @param maxIter Max iterations of the algorithm
	/// @param eps Max deviation from the target position
	/// @return Returns true if the end effector is within eps from the target before max Iterations are reached else returns false
	bool apply(const int maxIter, const float eps);

private:
	Skeleton* m_skeleton;
	Vector2D m_targetPos;
};
