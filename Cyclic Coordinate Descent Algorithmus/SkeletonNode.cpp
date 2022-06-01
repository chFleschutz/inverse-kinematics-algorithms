#include "SkeletonNode.h"
#include <iostream>

using namespace std;

SkeletonNode::SkeletonNode() {
	m_parent = nullptr;
	m_child = nullptr;
	m_angle = 0.f;
}

SkeletonNode::~SkeletonNode() {
	if (m_child) delete m_child;
}

void SkeletonNode::addChild(SkeletonNode * c) {
	if (c) 
	{
		c->m_parent = this;
		m_child = c;
	}
}

SkeletonNode* SkeletonNode::getJoint(int& index, const int searchIndex) {
	if (index == searchIndex) 
	{
		return this;
	}
	else 
	{
		if (m_child == nullptr) 
		{
			return nullptr;
		} 
		else 
		{
			SkeletonNode* searchNode = nullptr;
			index += 1;
			searchNode = m_child->getJoint(index, searchIndex);
			if (searchNode != nullptr)
			{
				return searchNode;
			}
		}
	}
	return nullptr;
}

void SkeletonNode::print(int einruecktiefe) {
	for (int i = 0; i < einruecktiefe; i++)
	{
		cout << " ";
	}
	cout << "angle = " << m_angle << endl;
	if (m_child)
	{
		m_child->print(einruecktiefe + 4);
	}
}