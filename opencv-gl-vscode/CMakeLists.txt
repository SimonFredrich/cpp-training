# cmake needs this line
cmake_minimum_required(VERSION 3.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# set flags (OpenGL)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall") # -Werror is very strict

# Ubuntu PC
set("OpenCV_DIR" "/mnt/8668734168732F55/Libraries/opencv-4.1.0-new/build/")

project(main LANGUAGES CXX)

find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# Declare the executable target built from your sources
add_executable(a.out 
	src/main.cpp)

# Link your application with OpenCV libraries
target_link_libraries(a.out ${OpenCV_LIBS} -lSDL2 -lGL -lGLEW)
