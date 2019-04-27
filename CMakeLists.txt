cmake_minimum_required(VERSION 3.10)
project("OpenGL Test")

set(CMAKE_CXX_STANDARD 17)

include_directories($(CMAKE_CURRENT_SOURCE_DIR))

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
  include_directories(${GLEW_INCLUDE_DIRS})
  link_libraries(${GLEW_LIBRARIES})
endif()

find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIR})
  link_libraries(${OPENGL_gl_LIBRARY})
endif()

find_package(glfw3 REQUIRED)

add_executable(out main.cpp)
target_link_libraries(out glfw)
