# LSHADE-NGS: Enhancing Q-Coverage in Directional Sensor Networks (Accepted in Neural Computing and Applications (NCAA) – Q1 Journal)

This repository provides a reference implementation and resources related to the paper:

*LSHADE-NGS: enhancing Q-coverage in directional sensor networks through navigated generation search*,  
*Neural Computing and Applications*, Springer, 2025.  
[Link to paper](https://link.springer.com/article/10.1007/s00521-025-11479-w)

---

## Table of Contents
- [Overview](#overview)
- [Key Contributions](#key-contributions)
- [Installation](#installation)
- [Usage](#usage)

---

## Overview

Directional sensor networks require optimal sensor activation and orientation to ensure efficient coverage.  
This work proposes **LSHADE-NGS (Navigated Generation Search)**, an evolutionary algorithm that improves Q-coverage under both under-provisioned and over-provisioned scenarios.

The main goal is to:

- Maximize coverage quality in under-provisioned scenarios.
- Minimize the number of active sensors in over-provisioned scenarios.
- Optimize trade-offs between power consumption and coverage.

---

## Key Contributions

1. **Enhanced Initialization**: Refined method to boost diversity in the starting population.
2. **Heuristic Adjustment JADE Mutation (HA-JADE)**: Adaptive mutation strategy to improve convergence.
3. **Greedily-Jumped Binomial Crossover (GJ-Bi)**: Accelerates convergence by exploiting promising directions.
4. **Extensive Evaluation**: Benchmarked against traditional LSHADE using multiple metrics including coverage quality, power consumption, and active sensor count.

---



## ⚙️ Build Instructions

Make sure you have [CMake](https://cmake.org/) and [MinGW](http://www.mingw.org/) installed and available in your system PATH.

### 🔧 Step-by-step:

```bash
git clone https://github.com/DucCuong12/LSHADE.git
cd LSHADE/src
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
.\L_SHADE_DWSNs_CPP.exe
```


