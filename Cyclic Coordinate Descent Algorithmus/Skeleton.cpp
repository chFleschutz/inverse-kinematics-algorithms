#include "Skeleton.h"

Skeleton::Skeleton() : m_root(0) {

}

Skeleton::~Skeleton() {
	if (m_root)
	{
		delete m_root;
	}
}
SkeletonNode* Skeleton::getJoint(int index) {
	int idx = 0;
	return m_root->getJoint(idx, index);
}
void Skeleton::print() {
	if (m_root)
	{
		m_root->print(0);
	}
}
