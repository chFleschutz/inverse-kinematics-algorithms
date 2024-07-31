#pragma once

#include "Bone.h"
#include "Vector2.h"

/// @brief Represents a skeletal structure composed of a chain of bones
/// @see Bone
class Skeleton
{
public:
	/// @brief Creates a empty skeleton
	Skeleton();
	/// @brief Creates a empty skeleton at positon
	/// @param position Positon of the root of the skeleton
	Skeleton(Vector2 position);
	/// @brief Deletes the whole chain of bones
	~Skeleton();

	/// @brief Sets the root bone of the skeleton
	void setRootBone(Bone* root) { m_root = root; }
	/// @brief Sets the root position of the skeleton
	void setRootPosition(const Vector2& position) { m_position = position; }

	/// @brief Returns the root bone of the skeleton
	Bone* rootBone() { return m_root; }
	/// @brief Returns the last bone in the skeleton chain at the pivot
	Bone* pivotBone();
	/// @brief Returns the root positon
	Vector2 rootPosition() { return m_position; }

	/// @brief Returns the position at the base of bone
	Vector2 boneBasePosition(Bone* bone);

	/// @brief Returns the pivot position of the last bone
	Vector2 pivotPosition();

	/// @brief Returns the count of bones
	int numOfBones();

	/// @brief Prints each bone of the skeleton with its angle and length to the console
	void print();

private:
	Bone* m_root;
	Vector2 m_position;
};

