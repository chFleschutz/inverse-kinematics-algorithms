#include "CCD.h"
#include "FABRIK.h"

#include <iostream>

int main()
{
	Vector2 targetPos(1.0f, 1.0f);

	Skeleton skeleton;
	skeleton.addBone(1.5f, radians(30.0f));
	skeleton.addBone(1.0f, radians(30.0f));
	skeleton.addBone(1.0f, radians(30.0f));

	// Print input
	std::cout << "<< INPUT >> \n"
		<< "Targetposition: " << targetPos << "\n"
		<< "Pivotposition:  " << skeleton.pivotPosition() << "\n"
		<< "Starting Skeleton:\n";
	skeleton.print();

	// Solve IK
	std::cout << "<< SOLVING IK >> \n";

	//FABRIK solver;
	CCD solver;
	auto result = solver.solve(skeleton, targetPos, 10, 0.1f);

	if (result)
		std::cout << "IK successful\n\n";
	else
		std::cout << "IK failure\n\n";

	// Print results
	auto pivot = skeleton.pivotPosition();
	auto deviation = (targetPos - pivot).length();

	std::cout << "<< OUTPUT >> \n"
		<< "Pivotposition:   " << pivot << "\n"
		<< "Targetposition:  " << targetPos << "\n"
		<< "Targetdeviation: " << deviation << "\n"
		<< "Resulting Skeleton: " << "\n";
	skeleton.print();
}
