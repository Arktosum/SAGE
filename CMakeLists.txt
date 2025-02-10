cmake_minimum_required(VERSION 3.10)
project(SAGEProject)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

# Add All source files.
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE EXTERNAL_SOURCES ${CMAKE_SOURCE_DIR}/external/*.cpp ${CMAKE_SOURCE_DIR}/external/*.c)
add_executable(result ${SOURCES} ${EXTERNAL_SOURCES})

target_include_directories(result PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(result PRIVATE ${CMAKE_SOURCE_DIR}/external)

# Link the necessary libraries
target_link_libraries(result PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/libglfw3.a # Path to libglfw3.a
    opengl32 # OpenGL library
    gdi32 # Graphics Device Interface
    user32 # User interface components
    kernel32 # Core Windows API functions
)
