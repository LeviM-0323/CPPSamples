# CPPSamples

CPPSamples is a small collection of C++ sample projects built with Visual Studio 2022 on Windows and `g++` on Linux.

## Projects

- `CPPSamples` - General-purpose object-oriented C++ samples
- `SortingTests` - Sorting algorithm benchmark and comparison tool
- `FakeGambling` - Slot machine style console game
- `FileUtility` - Command-line file viewing and sorting utility
- `BudgetTool` - Monthly budget calculator
- `DnDHelper` - Lightweight Dungeons & Dragons-style helper
- `MemTests` - Memory-focused sample project
- `CppRPG` - Small RPG prototype
- `MemoryTests` - Memory test harness
- `ShinobiSim` - Naruto-inspired simulation project

## Toolchain

- C++17
- Visual Studio 2022 Community for Windows builds
- `g++` for Linux builds
- Windows 10/11

## Continuous Integration

Automated builds run on every push to `main`.

- Windows CI produces `.exe` files for every project in the solution.
- Linux CI produces native Linux executables for every project that builds with `g++`.
- Each release includes the compiled binaries and the matching GitHub source archive.

[Latest releases](https://github.com/LeviM-0323/CPPSamples/releases)

![Windows Build](https://github.com/LeviM-0323/CPPSamples/actions/workflows/windows-build.yml/badge.svg)
![Linux Build](https://github.com/LeviM-0323/CPPSamples/actions/workflows/linux-build.yml/badge.svg)

## Building Locally

### Windows

Open `CPPSamples.sln` in Visual Studio 2022 and build the project you want, or use MSBuild from a Developer Command Prompt:

```bat
msbuild CPPSamples.sln /p:Configuration=Release /p:Platform=x64
```

### Linux

Install `g++`, then compile the source files for the project you want. Example:

```bash
g++ -std=c++17 -O2 -pthread BudgetTool/BudgetTool.cpp -o BudgetTool/BudgetTool
```

Some projects are Windows-specific and are intended for the Visual Studio build on Windows. The Linux workflow builds the portable projects that compile cleanly with `g++`.

## Future Work

- Add more sample projects
- Expand the existing samples

