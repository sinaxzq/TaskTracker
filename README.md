# TaskTracker

A small C++ task management project built to practice clean project structure, CMake, Git workflow, basic testing, and separation between core logic, application code, and tests.

## Features

- Add tasks with stable IDs
- Rename tasks
- Change task status
- Remove tasks by ID
- Remove tasks by status
- Find tasks by ID
- Print tasks in a simple console format
- Run self-tests with `assert`
- Run tests through CTest

## Project Structure

```text
TaskTracker/
├── include/
│   ├── Task.h
│   ├── TaskManager.h
│   └── TaskManagerTests.h
├── main.cpp
├── TestMain.cpp
├── Task.cpp
├── TaskManager.cpp
├── TaskManagerTests.cpp
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## Targets

The project builds three CMake targets:

```text
TaskTrackerCore   - core task logic
TaskTrackerApp    - console application
TaskTrackerTests  - test executable
```

`TaskTrackerCore` is shared by both the app and the tests.

## Build

Configure the project:

```powershell
cmake -S . -B build
```

Build the project:

```powershell
cmake --build build --config Debug
```

## Run Tests

Run tests with CTest:

```powershell
ctest --test-dir build -C Debug --output-on-failure
```

Expected result:

```text
100% tests passed
```

## Notes

This project is intentionally small. The goal is not to build a full task app, but to practice practical C++ engineering habits:

- clear ownership of responsibilities
- no global state
- stable task IDs instead of relying on vector indexes
- const-correct API design
- separate app and test executables
- CMake-based build workflow
- Git-based development workflow