#include "InverseKinematicsSolver.h"

InverseKinematicsSolver::InverseKinematicsSolver(Skeleton* skeleton, const Vector2& target) :
	m_skeleton{ skeleton },
	m_targetPos{ target }
{
}
