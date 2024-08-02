# Inverse Kinematics Algorithms: CCD and FABRIK
This repository contains two popular Inverse Kinematics (IK) algorithms: **Cyclic Coordinate Descent (CCD)** and **Forward and Backward Reaching Inverse Kinematics (FABRIK)**. These algorithms are commonly used in robotics, computer graphics and animation to solve the problem of positioning an end effector (such as a robotic arm or a character's limb) in a desired position by manipulating its joint angles.

## Introduction

Inverse Kinematics is an essential concept in robotics and animation. The algorithms in this repository offer solutions for solving IK problems.

- **CCD (Cyclic Coordinate Descent)**: This algorithm iteratively adjusts each joint angle to minimize the difference between the current end effector position and the desired position.

- **FABRIK (Forward and Backward Reaching Inverse Kinematics)**: FABRIK works by iteratively adjusting the positions of joints along the chain to reach the desired target.


## Getting Started

1. Clone the Repository:

```bash
git clone https://github.com/chFleschutz/inverse-kinematics-algorithms.git
```
2. Ensure you have CMake installed or your IDE supports CMake (e. g. Visual Studio)

3. Generate the project files or open the folder directly in your IDE (if it supports CMake)

4. Build the project and run the `IKExample` for a small demo


### Using the library

The project builds as a static library. To use it in another project:

1. Include the directory in your CMakeLists.txt file
  ```cmake
  add_subdirectory(path/to/inverse-kinematics-algorithms)
  ```

2. Link the library
  ```cmake
  target_link_libraries(your_target PRIVATE ik-algorithms)
  ```

3. Optionally you can disable building the example project by setting `BUILD_EXAMPLE` to `OFF`


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
skeleton.addBone(1.5f, 30.0f);
skeleton.addBone(1.0f, 30.0f);
skeleton.addBone(1.0f, 30.0f);
```

4. Create an IKSolver and call the `solve` method to compute the new joint angles for the skeleton. 
  
```cpp
CCD ikSolver;
ikSolver.solve(skeleton, targetPosition, maxIterations, 0.01f);
```
   
6. Use the updated joint angles to control your robotic arm or animation rig.


For a concrete example, check the [example-folder](example/) in the repo. The example demonstrates the setup and usage of the CCD and FABRIK algorithms.
