cmake_minimum_required(VERSION 2.8.12)

project(HWOC)


include_directories( ${CMAKE_SOURCE_DIR} /prj.include/)
include_directories( ${CMAKE_SOURCE_DIR} /prj.ar10/guiutil/)
include_directories( ${CMAKE_SOURCE_DIR} /prj.core/arcore/)
include_directories( ${CMAKE_SOURCE_DIR} /prj.core/framedata/)
include_directories(${KDE4_INCLUDES}
                    ${QT_QTCORE_INCLUDE_DIR}
                    ${QT_QTXML_INCLUDE_DIR}
                    ${QT_USE_FILE})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(OpenCV 3.1 REQUIRED)
find_package(Qt5Xml REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Xml ${OpenCV_LIBS}
    ${QT_QTXML_LIBRARY} ${QT_LIBRARIES})
