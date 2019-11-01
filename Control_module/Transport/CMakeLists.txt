cmake_minimum_required(VERSION 3.5)

include_directories(./include)

find_package(OpenCV)
find_package(Boost REQUIRED
    system
    filesystem
    thread
    )

add_library(SerialPort SHARED ./src/SerialPort.cpp)
target_link_libraries(SerialPort pthread ${Boost_LIBRARIES} ${OpenCV_LIBS})

set(SERIAL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
