#include <iostream>
#include "CCD.h"
#include "FABRIK.h"

using namespace std;

void setupSkeleton(Skeleton& skeleton);
void printResults(Skeleton& arm, Vector2D& target);
void runCCD(Skeleton& armature, Vector2D& target);
void runFABRIK(Skeleton& armature, Vector2D& target);

int main()
{
	// Setup Armature
	Skeleton arm{};
	setupSkeleton(arm);

	// Target Location
	Vector2D target = Vector2D(1.0f, 1.0f);
	cout << "Targetlocation: " << target << endl << endl;

	// Inverse Kinematik
	//runCCD(arm, target);
	runFABRIK(arm, target);

	// Print Results
	printResults(arm, target);
}

void setupSkeleton(Skeleton& skeleton)
{
	cout << "<< Input Values >>" << endl;
	Bone* node1 = new Bone(1.5f, 30.0f);
	Bone* node2 = new Bone(1.0f, 30.0f);
	Bone* node3 = new Bone(1.0f, 30.0f);
	skeleton.setRootBone(node1);
	node1->addChild(node2);
	node2->addChild(node3);
	cout << "Skeleton: " << endl;
	skeleton.print();
	Vector2D pivot = skeleton.getPivotPosition();
	cout << "Pivotposition:  " << pivot << endl;
}

void printResults(Skeleton& skeleton, Vector2D& target)
{
	cout << "<< Result Values >>" << endl;
	cout << "Skeleton: " << endl;
	skeleton.print();
	Vector2D pivot = skeleton.getPivotPosition();
	cout << "Pivotposition:   " << pivot << endl;
	cout << "Targetposition:  " << target << endl;
	cout << "Targetdeviation: " << (target - pivot).length() << endl;
}

void runCCD(Skeleton& skeleton, Vector2D& target)
{
	// Apply the CCD algorithm
	cout << "<< Running CCD >>" << endl;
	CCD ccd_solver = CCD(&skeleton, target);
	if (ccd_solver.apply(10, 0.01))
		cout << "CCD successful" << endl << endl;
	else
		cout << "CCD failure" << endl << endl;
}

void runFABRIK(Skeleton& skeleton, Vector2D& target)
{
	// Apply the FABRIK algorithm
	cout << "<< Running FABRIK >>" << endl;
	FABRIK fabrik_solver = FABRIK(&skeleton, target);
	if (fabrik_solver.apply(10, 0.1))
		cout << "FABRIK succesful" << endl << endl;
	else
		cout << "FABRIK failure" << endl << endl;
}
