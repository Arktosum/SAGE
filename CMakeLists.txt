cmake_minimum_required(VERSION 3.10)
project(SAGEProject)

# Add All source files.

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)
add_executable(result ${SOURCES})

target_include_directories(result PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link the necessary libraries
target_link_libraries(result PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/libglfw3.a # Path to libglfw3.a
    opengl32 # OpenGL library
    gdi32 # Graphics Device Interface
    user32 # User interface components
    kernel32 # Core Windows API functions
)
