# Inverse Kinematics Algorithms: CCD and FABRIK

This repository showcases the implementation of two popular Inverse Kinematics (IK) algorithms: **Cyclic Coordinate Descent (CCD)** and **Forward and Backward Reaching Inverse Kinematics (FABRIK)**. These algorithms are commonly used in robotics, computer graphics and animation to solve the problem of positioning an end-effector (such as a robotic arm or a character's foot) at a desired location by manipulating its joint angles.


## Introduction

Inverse Kinematics algorithms iteratively adjust joint angles in a chain of bones to minimize the distance between the end-effector's current position and the target. Both the CCD and FABRIK algorithms support variable-length bone chains and use iterative methods. As a result, they may fail if the target remains unreachable after n iterations.

The two algorithms use different approaches on solving IK:

### CCD (Cyclic Coordinate Descent)

- CCD iteratively adjusts each joint starting from the pivot and working backward towards the root. At each step, it modifies the angle of the current joint to minimize the distance between the end-effector and the target position.

- Implementation: [src/CCD.h](https://github.com/chFleschutz/inverse-kinematics-algorithms/blob/main/src/CCD.h)

### FABRIK (Forward and Backward Reaching Inverse Kinematics)

- FABRIK works by saving all joint-positions in a list and iteratively updating these in two passes:
  
  Forward Pass: The end-effector is moved to the target position, and each joint is adjusted to ensure it remains within reach of the connecting bone.

  Backward Pass: The root bone is placed back in the origin and each joint position is readjusted accordingly.
  
  After the positions are updated, the joint angles are calculated based of the new joint positions.

- Implementation: [src/FABRIK.h](https://github.com/chFleschutz/inverse-kinematics-algorithms/blob/main/src/FABRIK.h)

## Getting Started

1. Clone the Repository:

```bash
git clone https://github.com/chFleschutz/inverse-kinematics-algorithms.git
```
2. Ensure you have CMake installed or your IDE supports CMake (e. g. Visual Studio)

3. Generate the project files or open the folder directly in your IDE (if it supports CMake)

4. Build the project and run the `ik-algorithms-example` for a small demo


## Code Usage

To use the CCD / FABRIK algorithm, follow these steps:

1. Include `CCD.h` or `FABRIK.h`.

```cpp
#include "CCD.h"
#include "FABRIK.h"
```

3. Create a `Skeleton` and add `Bones` to it.

```cpp
Skeleton skeleton;
skeleton.addBone(1.5f, radians(30.0f));
skeleton.addBone(1.0f, radians(30.0f));
skeleton.addBone(1.0f, radians(30.0f));
```

4. Create an `IKSolver` and call the `solve` method to compute the new joint angles for the skeleton. 
  
```cpp
CCD solver;
solver.solve(skeleton, targetPosition, maxIterations, 0.01f);
```

Check the [example-folder](example/) for a demonstration of the CCD and FABRIK algorithms.
