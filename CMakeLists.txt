cmake_minimum_required(VERSION 3.16)

project(TaskTracker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(TaskTrackerCore
    Task.cpp
    TaskManager.cpp
)

target_include_directories(TaskTrackerCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(TaskTrackerApp
    main.cpp
)

target_link_libraries(TaskTrackerApp PRIVATE
    TaskTrackerCore
)

add_executable(TaskTrackerTests
    TestMain.cpp
    TaskManagerTests.cpp
)

target_link_libraries(TaskTrackerTests PRIVATE
    TaskTrackerCore
)