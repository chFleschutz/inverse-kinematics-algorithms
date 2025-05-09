#include "CCD.h"
#include "FABRIK.h"

#include <format>
#include <iomanip>
#include <iostream>

std::ostream& operator<<(std::ostream& os, glm::vec2& other)
{
	return os << std::format("( {:.3f}, {:.3f} )", other.x, other.y);
}

std::ostream& operator<<(std::ostream& os, glm::vec2&& other)
{
	return os << std::format("( {:.3f}, {:.3f} )", other.x, other.y);
}

void printSkeleton(const Skeleton& skeleton)
{
	for (const auto& bone : skeleton.bones())
	{
		std::cout << std::format("\tangle: {:>6.2f}, length: {:>6.2f}\n", glm::degrees(bone.angle), bone.length);
	}
}

int main()
{
	glm::vec2 targetPos(1.0f, 1.0f);

	Skeleton skeleton;
	skeleton.addBone(1.5f, glm::radians(30.0f));
	skeleton.addBone(1.0f, glm::radians(30.0f));
	skeleton.addBone(1.0f, glm::radians(30.0f));

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
