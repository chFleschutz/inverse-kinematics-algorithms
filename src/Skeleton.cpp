#include "Skeleton.h"

void Skeleton::addBone(float length, float angle)
{
	BoneHandle parent;
	if (!m_bones.empty())
	{
		parent = BoneHandle{ static_cast<uint32_t>(m_bones.size() - 1) };
	}

	m_bones.emplace_back(parent, BoneHandle{}, length, angle);
}

auto Skeleton::computeBoneBasePosition(BoneHandle handle) -> Vector2
{
	Vector2 basePosition;
	for (const auto& bone : m_bones)
	{
		basePosition += Vector2::makeVector(bone.length, bone.angle);

		if (bone.parent == handle)
			break;
	}
	return basePosition;
}

auto Skeleton::computePivotPosition() -> Vector2
{
	Vector2 pivotPos;
	float currentAngle = 0.0f;
	for (const auto& bone : m_bones)
	{
		currentAngle += bone.angle;
		pivotPos += Vector2::makeVector(bone.length, currentAngle);
	}
	return pivotPos;
}

auto Skeleton::computeJointPositions() -> std::vector<Vector2>
{
	std::vector<Vector2> jointPositions;
	jointPositions.reserve(m_bones.size() + 1);
	jointPositions.emplace_back(0.0f, 0.0f); // Add the root position
	float currentAngle = 0.0f;
	for (const auto& bone : m_bones)
	{
		currentAngle += bone.angle;
		Vector2 basePos = jointPositions.back();
		Vector2 endPos = basePos + Vector2::makeVector(bone.length, currentAngle);
		jointPositions.emplace_back(endPos);
	}
	return jointPositions;
}
