#pragma once

#include "Vector2.h"

#include <vector>


/// @brief Represents a bone in a skeleton
struct Bone
{
	Bone* parent = nullptr;
	Bone* child = nullptr;
	float length = 1.0f;
	float angle = 0.0f;
};

/// @brief A simple skeletal structure composed of a chain of bones
class Skeleton
{
public:
	Skeleton() = default;
	~Skeleton() = default;

	/// @brief Adds a bone at the end of the skeleton chain
	Skeleton& addBone(float length, float angle);

	/// @brief Returns the root bone of the skeleton
	Bone* rootBone() { return m_root; }
	/// @brief Returns the last bone in the skeleton chain at the pivot
	Bone* pivotBone() { return m_pivot; }

	/// @brief Returns the position at the base of bone
	Vector2 boneBasePosition(Bone* bone);

	/// @brief Returns the pivot position of the last bone
	Vector2 pivotPosition();

	/// @brief Returns the count of bones
	size_t numOfBones() { return m_bones.size(); }

	/// @brief Prints each bone of the skeleton with its angle and length to the console
	void print();

private:
	Bone* m_root = nullptr;
	Bone* m_pivot = nullptr;
	std::vector<std::unique_ptr<Bone>> m_bones;
};
