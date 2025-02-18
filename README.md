# C/C++ Development Environment Setup Guide

This guide covers setting up a C/C++ development environment including compilers (GCC/Clang), CMake, and essential tools across Windows, Linux, and macOS.

## Table of Contents
- [Windows Setup](#windows-setup)
- [Linux Setup](#linux-setup)
- [macOS Setup](#macos-setup)
- [CMake Setup](#cmake-setup)
- [Verifying Installation](#verifying-installation)

## Windows Setup

### Method 1: Using MSYS2 (Recommended)
1. Download MSYS2 from https://www.msys2.org/
2. Run the installer and follow the prompts
3. Open MSYS2 terminal and run:
```bash
pacman -Syu
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-clang
pacman -S mingw-w64-x86_64-cmake
pacman -S mingw-w64-x86_64-make
```
4. Add to PATH: `C:\msys64\mingw64\bin`

### Method 2: Using Visual Studio
1. Download Visual Studio Community Edition
2. During installation, select:
   - "Desktop development with C++"
   - "C++ CMake tools for Windows"
   - "Windows 10/11 SDK"

## Linux Setup

### Ubuntu/Debian
```bash
# Update package list
sudo apt update

# Install GCC
sudo apt install build-essential

# Install Clang
sudo apt install clang

# Install CMake
sudo apt install cmake

# Install additional tools
sudo apt install ninja-build
```

### Fedora
```bash
# Install GCC
sudo dnf install gcc gcc-c++

# Install Clang
sudo dnf install clang

# Install CMake
sudo dnf install cmake

# Install additional tools
sudo dnf install ninja-build
```

### Arch Linux
```bash
# Install GCC
sudo pacman -S base-devel

# Install Clang
sudo pacman -S clang

# Install CMake
sudo pacman -S cmake

# Install additional tools
sudo pacman -S ninja
```

## macOS Setup

### Using Homebrew (Recommended)
1. Install Homebrew:
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

2. Install required packages:
```bash
# Install Command Line Tools (includes GCC)
xcode-select --install

# Install Clang (included with Command Line Tools)
# Install CMake
brew install cmake

# Install additional tools
brew install ninja
```

### Using MacPorts
```bash
# Install MacPorts from https://www.macports.org/

# Install GCC
sudo port install gcc

# Install CMake
sudo port install cmake
```

## CMake Setup

CMake is a cross-platform build system generator. Here's a basic project structure:

```
project/
├── CMakeLists.txt
├── src/
│   └── main.cpp
└── include/
    └── header.h
```

Basic CMakeLists.txt example:
```cmake
cmake_minimum_required(VERSION 3.10)
project(YourProjectName)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(${PROJECT_NAME} 
    src/main.cpp
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${PROJECT_SOURCE_DIR}/include
)
```

## Verifying Installation

Create a test file `hello.cpp`:
```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
```

### Test GCC
```bash
g++ --version
g++ hello.cpp -o hello
./hello
```

### Test Clang
```bash
clang++ --version
clang++ hello.cpp -o hello
./hello
```

### Test CMake
```bash
cmake --version
```

## Common Issues and Solutions

1. **Windows PATH Issues**
   - Ensure compiler binaries are in system PATH
   - Restart terminal/IDE after PATH changes

2. **Linux Permission Issues**
   - Use `sudo` for installations
   - Check file permissions with `ls -l`

3. **macOS Xcode Issues**
   - Run `xcode-select --install` if compiler not found
   - Accept Xcode license if needed: `sudo xcodebuild -license`

## IDE Recommendations

1. **Visual Studio Code**
   - Install C/C++ extension
   - Install CMake Tools extension
   - Configure `tasks.json` and `launch.json`

2. **CLion**
   - Includes built-in CMake support
   - Automatic toolchain detection
   - Debugger integration

3. **Visual Studio**
   - Native C++ support
   - Integrated CMake support
   - Windows-focused development

## Getting Help

- Official Documentation:
  - GCC: https://gcc.gnu.org/onlinedocs/
  - Clang: https://clang.llvm.org/docs/
  - CMake: https://cmake.org/documentation/

- Community Resources:
  - Stack Overflow tags: [c++], [gcc], [clang], [cmake]
  - Reddit: r/cpp, r/cpp_questions
  - Discord: C++ Server