#pragma once

#include "Vector2.h"

#include <vector>
#include <limits>

struct BoneHandle
{
	BoneHandle() = default;
	BoneHandle(uint32_t id) : id(id) {}
	BoneHandle(size_t id) : id(static_cast<uint32_t>(id)) {}

	uint32_t id{ std::numeric_limits<uint32_t>::max() };

	[[nodiscard]] auto operator==(const BoneHandle& other) const -> bool { return id == other.id; }
	[[nodiscard]] auto operator!=(const BoneHandle& other) const -> bool { return id != other.id; }
};

/// @brief Represents a bone in a skeleton
struct Bone
{
	BoneHandle parent;
	BoneHandle child;
	float length = 1.0f;
	float angle = 0.0f;
};

/// @brief A simple skeletal structure composed of a chain of bones
class Skeleton
{
public:
	Skeleton() = default;
	~Skeleton() = default;

	[[nodiscard]] auto bone(BoneHandle handle) -> Bone& { return m_bones[handle.id]; }
	[[nodiscard]] auto bone(BoneHandle handle) const -> const Bone& { return m_bones[handle.id]; }
	[[nodiscard]] auto boneCount() const -> size_t { return m_bones.size(); }
	[[nodiscard]] auto bones() const -> const std::vector<Bone>& { return m_bones; }

	[[nodiscard]] auto computeBoneBasePosition(BoneHandle handle) const-> Vector2;
	[[nodiscard]] auto computePivotPosition() const -> Vector2;
	[[nodiscard]] auto computeJointPositions() const -> std::vector<Vector2>;

	void addBone(float length, float angle);

private:
	std::vector<Bone> m_bones;
};
