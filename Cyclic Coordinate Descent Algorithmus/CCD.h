#pragma once
#include <math.h>
#include "skeleton.h"
#include "vector2d.h"

class CCD {

public:
	CCD();
	CCD(Skeleton* skeleton, Vector2D target = Vector2D(0.0f, 0.0f));
	
	Skeleton* getSkeleton();

	void setTargetPosition(float tx, float ty);

	// Trys to set the Pivot Position of the Skeleton to the Target Position by rotating the bones of the Skeleton
	// Returns true if the Pivot is within the eps distance from the Target
	// Retunrs false if the max Iterations are reached without the Pivot being near enough the Target
	bool apply(const int maxIter, const float eps);

private:
	Skeleton* m_skeleton;
	Vector2D m_targetPos;
};
