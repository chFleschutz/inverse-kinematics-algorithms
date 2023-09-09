#include "InverseKinematicsSolver.h"

InverseKinematicsSolver::InverseKinematicsSolver(Skeleton* skeleton, const Vector2D& target) :
	m_skeleton{ skeleton },
	m_targetPos{ target }
{
}
