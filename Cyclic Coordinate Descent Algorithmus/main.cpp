#include <iostream>
#include "CCD.h"

using namespace std;

int main() 
{
	// Setup Armature
	cout << "<< Input Values >>" << endl;
	Skeleton* arm = new Skeleton();
	SkeletonNode* node1 = new SkeletonNode(1.0f, 30.0f);
	SkeletonNode* node2 = new SkeletonNode(1.0f, 30.0f);
	arm->setRoot(node1);
	node1->addChild(node2);
	cout << "Skeleton: " << endl;
	arm->print();
	// Target Location
	Vector2D target = Vector2D(1.0f, 1.0f);
	cout << "Targetlocation: " << target << endl;
	// Current Pivot Position
	Vector2D pivot = arm->getPivotPosition();
	cout << "Pivotposition: " << pivot << endl << endl;

	// apply the CCD algorithm
	cout << "<< Running CCD >>" << endl;
	CCD algo = CCD(arm, target);
	if (algo.apply(10, 0.01)) cout << "CCD succes" << endl << endl;
	else cout << "CCD failure" << endl << endl;
	
	// Print Result
	cout << "<< Result Values >>" << endl;
	cout << "Skeleton: " << endl;
	arm->print();
	pivot = arm->getPivotPosition();
	cout << "Pivotposition: " << pivot << endl << endl;

}