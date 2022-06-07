#include "SkeletonNode.h"
#include <iostream>

SkeletonNode::SkeletonNode() {
	m_parent = nullptr;
	m_child = nullptr;
	m_length = 1.0f;
	m_angle = 0.f;
}

SkeletonNode::SkeletonNode(float length, float angle)
{
	m_parent = nullptr;
	m_child = nullptr;
	m_length = length;
	m_angle = angle;
}

SkeletonNode::~SkeletonNode() {
	if (m_child) delete m_child;
}

void SkeletonNode::addChild(SkeletonNode* child) {
	if (child) 
	{
		child->m_parent = this;
		m_child = child;
	}
}

void SkeletonNode::print(int einruecktiefe) {
	for (int i = 0; i < einruecktiefe; i++)
	{
		std::cout << " ";
	}
	std::cout << "angle = " << m_angle << std::endl;
	if (m_child)
	{
		m_child->print(einruecktiefe + 4);
	}
}