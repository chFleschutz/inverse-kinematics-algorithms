#pragma once
#include "Skeleton.h"
#include "Vector2D.h"

class FABRIK
{
public:
	FABRIK(Skeleton* skeleton, Vector2D target);

	bool apply();

private:
	Skeleton* m_skeleton;
	Vector2D m_target;
};

