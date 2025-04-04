cmake_minimum_required(VERSION 3.10)
project(Sage)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Add All source files.
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.c)
add_executable(result ${SOURCES})

target_include_directories(result PRIVATE ${CMAKE_SOURCE_DIR}/external)
target_include_directories(result PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link the necessary libraries
target_link_libraries(result PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/libglfw3.a # Path to libglfw3.a
    opengl32 # OpenGL library
    gdi32 # Graphics Device Interface
    user32 # User interface components
    kernel32 # Core Windows API functions
)

include(FetchContent)

FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)

FetchContent_MakeAvailable(glm)

target_link_libraries(result PRIVATE glm::glm)