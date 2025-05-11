# LSHADE: Differential Evolution for Q-Coverage in Directional Sensor Networks

**LSHADE** is a C++ implementation of an adaptive differential evolution algorithm designed to solve the Q-Coverage problem in Directional Wireless Sensor Networks (DWSNs). It is based on the LSHADE algorithm and tailored for optimization in sensor activation, directional angles, and energy efficiency.

## 📌 Features

- ✅ Q-Coverage optimization for DWSNs
- ✅ Adaptive differential evolution with historical learning
- ✅ Measures: CQ, QBI, DI, Power Consumption, etc.
- ✅ Modular and extensible C++ structure

## 📂 Project Structure


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
