cmake_minimum_required(VERSION 3.10)
project(SAGE)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRCFILES src/*.cpp src/*.c)
add_executable(SAGE ${SRCFILES})

# 1) Includes
target_include_directories(SAGE PUBLIC
  ${CMAKE_SOURCE_DIR}/external
  ${CMAKE_SOURCE_DIR}/include
)

# 3) Link libraries
target_link_libraries(SAGE PRIVATE
  ${CMAKE_SOURCE_DIR}/lib/libglfw3.a # Path to libglfw3.a
  opengl32 # OpenGL library
  gdi32 # Graphics Device Interface
  user32 # User interface components
  kernel32 # Core Windows API functions
)

# 4) Diagnostics
message(STATUS "Library search path: ${CMAKE_SOURCE_DIR}/lib")
message(STATUS "External search path: ${CMAKE_SOURCE_DIR}/external")
message(STATUS "Includes search path: ${CMAKE_SOURCE_DIR}/include")
