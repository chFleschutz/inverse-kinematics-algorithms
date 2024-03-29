#include "CCD.h"
#include "FABRIK.h"

#include <iostream>

/// Demo for ik algorithms
void runCCD(Skeleton& armature, Vector2D& target);
void runFABRIK(Skeleton& armature, Vector2D& target);

void setupSkeleton(Skeleton& skeleton);
void printResults(Skeleton& arm, Vector2D& target);


int main()
{
	Skeleton arm{};
	setupSkeleton(arm);

	Vector2D target = Vector2D(1.0f, 1.0f);
	std::cout << "Targetlocation: " << target << std::endl << std::endl;

	// Inverse kinematics solver
	runCCD(arm, target);
	//runFABRIK(arm, target);
	
	printResults(arm, target);
}

void runCCD(Skeleton& skeleton, Vector2D& target)
{
	// Apply the CCD algorithm
	std::cout << "<< Running CCD >>" << std::endl;
	CCD ccd_solver = CCD(&skeleton, target);
	if (ccd_solver.solve(10, 0.01f))
		std::cout << "CCD successful" << std::endl << std::endl;
	else
		std::cout << "CCD failure" << std::endl << std::endl;
}

void runFABRIK(Skeleton& skeleton, Vector2D& target)
{
	// Apply the FABRIK algorithm
	std::cout << "<< Running FABRIK >>" << std::endl;
	FABRIK fabrik_solver = FABRIK(&skeleton, target);
	if (fabrik_solver.solve(10, 0.1f))
		std::cout << "FABRIK succesful" << std::endl << std::endl;
	else
		std::cout << "FABRIK failure" << std::endl << std::endl;
}

void setupSkeleton(Skeleton& skeleton)
{
	std::cout << "<< Input Values >>" << std::endl;
	Bone* bone1 = new Bone(1.5f, 30.0f);
	Bone* bone2 = new Bone(1.0f, 30.0f);
	Bone* bone3 = new Bone(1.0f, 30.0f);
	skeleton.setRootBone(bone1);
	bone1->addChild(bone2);
	bone2->addChild(bone3);
	std::cout << "Skeleton: " << std::endl;
	skeleton.print();
	Vector2D pivot = skeleton.pivotPosition();
	std::cout << "Pivotposition:  " << pivot << std::endl;
}

void printResults(Skeleton& skeleton, Vector2D& target)
{
	std::cout << "<< Result Values >>" << std::endl;
	std::cout << "Skeleton: " << std::endl;
	skeleton.print();
	Vector2D pivot = skeleton.pivotPosition();
	std::cout << "Pivotposition:   " << pivot << std::endl;
	std::cout << "Targetposition:  " << target << std::endl;
	std::cout << "Targetdeviation: " << (target - pivot).length() << std::endl;
}
