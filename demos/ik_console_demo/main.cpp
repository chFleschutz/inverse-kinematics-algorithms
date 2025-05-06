#include "CCD.h"
#include "FABRIK.h"

#include <iostream>
#include <format>

void printSkeleton(const Skeleton& skeleton)
{
	for (const auto& bone : skeleton.bones())
	{
		std::cout << std::format("\tangle: {:>6.2f}, length: {:>6.2f}\n", degrees(bone.angle), bone.length);
	}
}

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
		<< "Pivotposition:  " << skeleton.computePivotPosition() << "\n"
		<< "Starting Skeleton:\n";
	printSkeleton(skeleton);

	// Solve IK
	std::cout << "\n<< SOLVING IK >> \n";

	FABRIK solver;
	//CCD solver;
	auto success = solver.solve(skeleton, targetPos, 10, 0.1f);
	std::cout << (success ? "IK successful\n" : "IK failure\n");

	// Print results
	auto pivot = skeleton.computePivotPosition();
	auto deviation = (targetPos - pivot).length();
	std::cout << "\n<< OUTPUT >> \n"
		<< "Pivotposition:   " << pivot << "\n"
		<< "Targetposition:  " << targetPos << "\n"
		<< "Targetdeviation: " << deviation << "\n"
		<< "Resulting Skeleton: " << "\n";
	printSkeleton(skeleton);
}
