#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <limits>

/// @brief Represents a bone in a skeleton
struct Bone
{
	int32_t parent = -1; 
	float length = 1.0f;
	float angle = 0.0f;
};

/// @brief A simple skeletal structure composed of a chain of bones
class Skeleton
{
public:
	Skeleton() = default;
	~Skeleton() = default;

	[[nodiscard]] auto bone(int32_t index) -> Bone& { return m_bones[index]; }
	[[nodiscard]] auto bone(int32_t index) const -> const Bone& { return m_bones[index]; }
	[[nodiscard]] auto boneCount() const -> size_t { return m_bones.size(); }
	[[nodiscard]] auto bones() const -> const std::vector<Bone>& { return m_bones; }
	[[nodiscard]] auto maxReach() const -> float { return m_maxReach; }

	[[nodiscard]] auto computeBoneBasePosition(int32_t index) const->glm::vec2;
	[[nodiscard]] auto computePivotPosition() const -> glm::vec2;
	[[nodiscard]] auto computeJointPositions() const -> std::vector<glm::vec2>;

	void addBone(float length, float angle);

private:
	std::vector<Bone> m_bones;
	float m_maxReach = 0.0f;
};
