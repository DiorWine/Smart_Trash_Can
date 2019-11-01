cmake_minimum_required(VERSION 3.10)
project (Trash)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_ROOT_DIRECTROY ${CMAKE_CURRENT_SOURCE_DIR})

# find_package(OpenCV)
find_package(Boost REQUIRED
    system
    filesystem
    thread
    )

add_definitions(-DROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(Transport)
include_directories(${SERIAL_INCLUDE})
add_subdirectory(Driver)
include_directories(${DRIVER_INCLUDE})
