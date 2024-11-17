#include "CCD.h"
#include "FABRIK.h"

#include <iostream>

int main()
{
	// Input
	Vector2 targetPos(1.0f, 1.0f);

	Skeleton skeleton;
	skeleton.addBone(1.5f, 30.0f);
	skeleton.addBone(1.0f, 30.0f);
	skeleton.addBone(1.0f, 30.0f);

	// Print input
	std::cout << "<< INPUT >> \n";
	std::cout << "Starting Skeleton: " "\n";
	skeleton.print();
	std::cout << "Pivotposition:  " << skeleton.pivotPosition() << "\n";
	std::cout << "Targetposition: " << targetPos << "\n\n";


	// Inverse kinematics solver (use CDD / FABRIK)
	std::cout << "<< SOLVING IK >> \n";
	//FABRIK ikSolver;
	CCD ikSolver;
	auto result = ikSolver.solve(skeleton, targetPos, 10, 0.1f);

	if (result)
		std::cout << "IK successful" << std::endl << std::endl;
	else
		std::cout << "IK failure" << std::endl << std::endl;


	// Print results
	auto pivot = skeleton.pivotPosition();
	auto deviation = (targetPos - pivot).length();

	std::cout << "<< OUTPUT >> \n";
	std::cout << "Resulting Skeleton: " << "\n";
	skeleton.print();
	std::cout << "Pivotposition:   " << pivot << "\n";
	std::cout << "Targetposition:  " << targetPos << "\n";
	std::cout << "Targetdeviation: " << deviation << "\n";
}
