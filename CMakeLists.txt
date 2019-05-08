cmake_minimum_required(VERSION 2.8)
project(Harris)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
add_executable(harris main.cpp harrisCorner.cpp harrisCorner.h)
target_link_libraries(harris
        ${OpenCV_LIBS})
