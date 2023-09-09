# Inverse Kinematics Algorithms: CCD and FABRIK
This repository contains two popular Inverse Kinematics (IK) algorithms: **Cyclic Coordinate Descent (CCD)** and **Forward and Backward Reaching Inverse Kinematics (FABRIK)**. These algorithms are commonly used in robotics, computer graphics, and animation to solve the problem of positioning an end effector (such as a robotic arm or a character's limb) in a desired position by manipulating its joints.

## Introduction

Inverse Kinematics is an essential concept in robotics and animation. These algorithms in this repository offer solutions for solving IK problems.

- **CCD (Cyclic Coordinate Descent)**: This algorithm iteratively adjusts each joint angle in a chain of joints to minimize the difference between the current end effector position and the desired position.

- **FABRIK (Forward and Backward Reaching Inverse Kinematics)**: FABRIK is an iterative method that works by iteratively adjusting the positions of joints along a chain to reach a desired target.

## Usage

To use the CCD / FABRIK algorithm, follow these steps:

1. Include `CCD.h` or `FABRIK.h`.

1. Create a `Skeleton` with `Bone`s as the joints.

2. Create an instance of the `CCD` or `FABRIK` class, providing the skeleton and the target position.

3. Call the `solve` method of the `CCD` or `FABRIK` instance to compute the new joint angles for the skeleton that will position the end effector closer to the target.

4. Use the updated joint angles to control your robotic arm or animation rig.


Here's a basic example of how to use the CCD algorithm:

```cpp
// Create simple skeleton
Skeleton skeleton;
Bone* bone1 = new Bone(1.5f, 30.0f);
Bone* bone2 = new Bone(1.0f, 30.0f);
skeleton.setRootBone(bone1);
bone1->addChild(bone2);

// Create target position
Vector2D target = Vector2D(1.0f, 1.0f);

// Apply CDD algorithm
CCD ccd_solver = CCD(skeleton, target);
ccd_solver.applyCCD(10, 0.01)
```
In addition, you can explore a small demo in the main.cpp file.


## Installation
You can simply clone this repository to get started:
```bash
https://github.com/chFleschutz/inverse-kinematics-algorithms.git
```
To view a brief demonstration, open the solution in Visual Studio and run it.
