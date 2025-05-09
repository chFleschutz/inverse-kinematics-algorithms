# Inverse Kinematics Algorithms: CCD and FABRIK

This repository showcases the implementation of two popular Inverse Kinematics (IK) algorithms: **Cyclic Coordinate Descent (CCD)** and **Forward and Backward Reaching Inverse Kinematics (FABRIK)**. These algorithms are commonly used in robotics, computer graphics and animation to solve the problem of positioning an end-effector for a skeleton (such as a robotic arm or a character's foot) at a desired location by manipulating its joint angles.

![grafik](https://github.com/user-attachments/assets/3787015e-c027-4bbd-af04-154a3cf6b97c)

## Introduction

Inverse Kinematics algorithms iteratively adjust joint angles in a chain of bones to minimize the distance between the end-effector's current position and the target. Both the CCD and FABRIK algorithms support variable-length bone chains and use iterative methods. As a result, both algorithms may fail to converge if the target remains unreachable after a specified number of iterations.

## CCD (Cyclic Coordinate Descent)

CCD iteratively adjusts each joint starting from the end-effector and working backward towards the root. At each step, it modifies the angle of the current joint to minimize the distance between the end-effector and the target position.

- Implementation: [src/CCD.h](https://github.com/chFleschutz/inverse-kinematics-algorithms/blob/main/src/CCD.h)

## FABRIK (Forward and Backward Reaching Inverse Kinematics)

FABRIK works by saving all joint-positions in a list and iteratively updating these in two passes:
  
- **Forward Pass**: The end-effector (last joint) is placed at the target position, and each joint is adjusted to ensure it remains within reach of the connecting bone.

- **Backward Pass**: The root joint (first joint) is placed back at the origin and each joint position is readjusted accordingly again.
  
After the positions are updated, the new bone angles are calculated based on the updated joint positions.

- Implementation: [src/FABRIK.h](https://github.com/chFleschutz/inverse-kinematics-algorithms/blob/main/src/FABRIK.h)

---

## Getting Started

1. Clone the Repository:
  ```bash
  git clone --recurse-submodules https://github.com/chFleschutz/inverse-kinematics-algorithms.git
  ```

2. Ensure you have CMake installed or your IDE supports CMake (e.g. Visual Studio).

3. Generate the project files or open the folder directly in your IDE.

4. Build and run the `ik-console-demo` project for a small console-based demo.

### GUI Demo

1. Ensure [Qt](https://www.qt.io/download-dev) (Version 6.9.0 recommended) is installed.

2. Regenerate the project files after installing Qt.

3. Build and run the `ik-gui-demo` project.

---

## Code Usage

To use the CCD or FABRIK solver:

1. Include the headers:

```cpp
#include "CCD.h"
#include "FABRIK.h"
```

3. Create a `Skeleton` and add bones:

```cpp
Skeleton skeleton;
skeleton.addBone(1.5f, glm::radians(30.0f));
skeleton.addBone(1.0f, glm::radians(30.0f));
skeleton.addBone(1.0f, glm::radians(30.0f));
```

4. Create an `IKSolver` and call `solve`: 
  
```cpp
CCD solver;
int maxIterations = 100;
float precision = 0.01f;
glm::vec2 target{ 2.0f, 1.0f };

solver.solve(skeleton, target, maxIterations, precision);
```

> Note: This project uses [GLM](https://github.com/g-truc/glm) for vector math (`glm::vec2`).

Check the [demo](demo/) folder for example usages of the CCD and FABRIK algorithms.
