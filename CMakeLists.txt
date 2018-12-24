project(geometry)

cmake_minimum_required(VERSION 3.12)

#set C++ standard 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)

#check bin folder is exist, if not create
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/bin)
else()
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif()

IF (APPLE)
  ADD_DEFINITIONS(-DAPPLE)
ENDIF (APPLE)

#debug mode
set(CMAKE_BUILD_TYPE "Debug")

#set output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#find OpenGL package
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

#GLFW additions
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#GLFW
add_subdirectory(glfw)
include_directories(glfw/include)

#glad
set(GLAD_SRC_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/glad)
include_directories(${GLAD_SRC_DIRS}/include)
add_subdirectory(${GLAD_SRC_DIRS})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)