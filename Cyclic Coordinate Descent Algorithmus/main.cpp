#include <iostream>
#include "CCD.h"

using namespace std;

Skeleton* setupArmature();
void printResults(Skeleton* arm, Vector2D& target);

int main() 
{
	// Setup Armature
	Skeleton* arm = setupArmature();

	// Target Location
	Vector2D target = Vector2D(1.0f, 1.0f);
	cout << "Targetlocation: " << target << endl << endl;

	// Apply the CCD algorithm
	cout << "<< Running CCD >>" << endl;
	CCD algo = CCD(arm, target);
	// Check if pivot is within the deviation from the target
	if (algo.apply(10, 0.01)) cout << "CCD successful" << endl << endl;
	else cout << "CCD failure" << endl << endl;
	
	// Print Results
	printResults(arm, target);
}

Skeleton* setupArmature()
{
	// Setup Armature
	cout << "<< Input Values >>" << endl;
	Skeleton* arm = new Skeleton();
	SkeletonNode* node1 = new SkeletonNode(1.0f, 30.0f);
	SkeletonNode* node2 = new SkeletonNode(1.0f, 30.0f);
	//SkeletonNode* node3 = new SkeletonNode(1.0f, 30.0f);
	arm->setRoot(node1);
	node1->addChild(node2);
	//node2->addChild(node3);
	cout << "Skeleton: " << endl;
	arm->print();
	Vector2D pivot = arm->getPivotPosition();
	cout << "Pivotposition:  " << pivot << endl;
	return arm;
}

void printResults(Skeleton* arm, Vector2D& target)
{
	// Print Result
	cout << "<< Result Values >>" << endl;
	cout << "Skeleton: " << endl;
	arm->print();
	Vector2D pivot = arm->getPivotPosition();
	cout << "Pivotposition:   " << pivot << endl;
	cout << "Targetposition:  " << target << endl;
	cout << "Targetdeviation: " << (target - pivot).length() << endl;
}
