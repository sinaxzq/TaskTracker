cmake_minimum_required(VERSION 3.16)

project(TaskTracker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(enable_strict_warnings target_name)
    if(MSVC)
        target_compile_options(${target_name} PRIVATE /W4 /WX)
    else()
        target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endfunction()

add_library(TaskTrackerCore
    Task.cpp
    TaskManager.cpp
)

target_include_directories(TaskTrackerCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

enable_strict_warnings(TaskTrackerCore)

add_executable(TaskTrackerApp
    main.cpp
)

target_link_libraries(TaskTrackerApp PRIVATE
    TaskTrackerCore
)

enable_strict_warnings(TaskTrackerApp)

add_executable(TaskTrackerTests
    TestMain.cpp
    TaskManagerTests.cpp
)

target_link_libraries(TaskTrackerTests PRIVATE
    TaskTrackerCore
)

enable_strict_warnings(TaskTrackerTests)

enable_testing()

add_test(NAME TaskManagerTests COMMAND TaskTrackerTests)