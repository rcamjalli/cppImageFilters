cmake_minimum_required(VERSION 3.13)
project(ImageEditor)

set(CMAKE_CXX_STANDARD 14)

find_package( OpenCV REQUIRED )

set(SOURCE_FILES main.cpp)

add_executable(ImageEditor ${SOURCE_FILES})

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )