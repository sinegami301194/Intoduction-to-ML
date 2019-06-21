cmake_minimum_required(VERSION 2.8.12)

project(hw_opencv)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(OpenCV 3.1 REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME} Qt5::Core ${OpenCV_LIBS})
