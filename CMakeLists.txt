cmake_minimum_required(VERSION 3.13)
project(Harris-Corner-master)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
add_executable(op main.cpp harrisCorner.cpp harrisCorner.h)
target_link_libraries(op
        ${OpenCV_LIBS})
