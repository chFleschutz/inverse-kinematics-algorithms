#include "Skeleton.h"

auto polarToCartesian(float length, float angle) -> glm::vec2
{
	return glm::vec2{ length * std::cos(angle), length * std::sin(angle) };
}

void Skeleton::addBone(float length, float angle)
{
	int32_t parent = m_bones.empty() ? -1 : static_cast<int32_t>(m_bones.size() - 1);
	m_bones.emplace_back(parent, length, angle);
}

auto Skeleton::computeBoneBasePosition(int32_t index) const -> glm::vec2
{
	glm::vec2 basePosition{};
	for (const auto& bone : m_bones)
	{
		basePosition += polarToCartesian(bone.length, bone.angle);

		if (bone.parent == index)
			break;
	}
	return basePosition;
}

auto Skeleton::computePivotPosition() const -> glm::vec2
{
	glm::vec2 pivotPos{};
	float currentAngle = 0.0f;
	for (const auto& bone : m_bones)
	{
		currentAngle += bone.angle;
		pivotPos += polarToCartesian(bone.length, currentAngle);
	}
	return pivotPos;
}

auto Skeleton::computeJointPositions() const -> std::vector<glm::vec2>
{
	std::vector<glm::vec2> jointPositions;
	jointPositions.reserve(m_bones.size() + 1);
	jointPositions.emplace_back(0.0f, 0.0f); // Add the root position
	float currentAngle = 0.0f;
	for (const auto& bone : m_bones)
	{
		currentAngle += bone.angle;
		glm::vec2 basePos = jointPositions.back();
		glm::vec2 endPos = basePos + polarToCartesian(bone.length, currentAngle);
		jointPositions.emplace_back(endPos);
	}
	return jointPositions;
}
