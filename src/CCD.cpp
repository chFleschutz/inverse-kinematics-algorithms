#include "CCD.h"

#include <numbers>


bool CCD::solve(Skeleton& skeleton, const Vector2& targetPos, int maxIterations, float epsilon)
{
	for (int i = 0; i < maxIterations; i++)
	{
		Bone* node = skeleton.pivotBone();

		// Adjust rotation of each bone in the skeleton
		while (node != nullptr)
		{
			Vector2 pivotPos = skeleton.pivotPosition();
			Vector2 currrentBasePos = skeleton.boneBasePosition(node);
			Vector2 basePivotVec = (pivotPos - currrentBasePos).normalize();
			Vector2 baseTargetVec = (targetPos - currrentBasePos).normalize();

			float rotateAngle = acos(basePivotVec.dot(baseTargetVec)) * 180.0f / std::numbers::pi_v<float>;
			if (basePivotVec.cross(baseTargetVec) < 0.0f) rotateAngle *= -1.0f;

			node->angle = node->angle + rotateAngle;
			node = node->parent;
		}

		// Return if pivot is near enought to the target -> success
		if ((targetPos - skeleton.pivotPosition()).length() < epsilon)
			return true;
	}

	// Algorithm finished by reaching max Iterations -> pivot is not near enough to the target
	return false;
}
