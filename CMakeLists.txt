cmake_minimum_required(VERSION 3.12)
project(OpenGL_FinalProject)

set(CMAKE_CXX_STANDARD 11)

add_executable(OpenGL_FinalProject main.cpp)

find_package (OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})