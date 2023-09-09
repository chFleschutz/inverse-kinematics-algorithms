#pragma once
#include "Bone.h"
#include "Vector2D.h"

class Skeleton
{
public:
	/// @brief Creates a empty skeleton
	Skeleton();
	/// @brief Creates a empty skeleton at positon
	/// @param position Positon of the root of the skeleton
	Skeleton(Vector2D position);
	~Skeleton();

	/// @brief Sets the root Bone of the skeleton
	void setRootBone(Bone* root) { m_root = root; }
	/// @brief Sets the root position of the skeleton
	void setRootPosition(const Vector2D& position) { m_position = position; }

	/// @brief Returns the root bone of the skeleton
	Bone* rootBone() { return m_root; }
	/// @brief Returns the last bone in the skeleton chain at the pivot
	Bone* pivotBone();
	/// @brief Returns the root positon
	Vector2D rootPosition() { return m_position; }

	/// @brief Returns the position at the base of bone
	Vector2D boneBasePosition(Bone* bone);

	/// @brief Returns the pivot position of the last bone
	Vector2D pivotPosition();

	/// @brief Returns the count of bones
	int numOfBones();

	/// @brief Prints each bone of the skeleton with its angle and length to the console
	void print();

private:
	Bone* m_root;
	Vector2D m_position;
};

