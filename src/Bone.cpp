#include "Bone.h"

#include <iostream>


Bone::Bone(float length, float angle)
{
	m_length = length;
	m_angle = angle;
}

Bone::~Bone()
{
	if (m_child) 
		delete m_child;
}

void Bone::addChild(Bone* child)
{
	if (child)
	{
		child->m_parent = this;
		m_child = child;
	}
}

void Bone::print(int indentDepth)
{
	for (int i = 0; i < indentDepth; i++) 
		std::cout << " ";

	std::cout << "angle  = " << m_angle << std::endl;

	for (int i = 0; i < indentDepth; i++) 
		std::cout << " ";

	std::cout << "length = " << m_length << std::endl;

	if (m_child)
		m_child->print(indentDepth + 4);
	else
		std::cout << std::endl;
}