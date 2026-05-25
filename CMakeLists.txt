cmake_minimum_required(VERSION 3.16)

project(TaskTracker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(TaskTracker
    main.cpp
    Task.cpp
    TaskManager.cpp
    TaskManagerTests.cpp
)

target_include_directories(TaskTracker PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)