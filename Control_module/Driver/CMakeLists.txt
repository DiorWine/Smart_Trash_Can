cmake_minimum_required(VERSION 3.10)
find_package(OpenCV)
include_directories(./include)
include_directories(${PROJECT_SOURCE_DIR}/Transport/include)

add_library(Driver SHARED ./src/TrashControl.cpp)
target_link_libraries(Driver SerialPort)

get_property(include_dir DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
set(DRIVER_INCLUDE ${include_dir} PARENT_SCOPE)

add_executable(test_trash ./test/test_ctl.cpp)
target_link_libraries(test_trash Driver ${OpenCV_LIBS})

add_executable(Movetrash ./test/MoveTrash.cpp)
target_link_libraries(Movetrash Driver)
