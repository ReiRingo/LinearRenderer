cmake_minimum_required(VERSION 3.10)
project(LinearRenderer C)

# c standard
set(CMAKE_C_STANDARD 11)

# find opengl
find_package(OpenGL REQUIRED)

# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(deps/glfw) # <- CRITICAL: this tells CMake to buikd GLFW

# library sources
set(SOURCES
    src/core/window.c 
    src/core/shader.c 
    src/core/mesh.c 
    deps/glad/src/glad.c 
)

# render library
add_library(LinearRender ${SOURCES})

# include paths
target_include_directories(LinearRender PUBLIC 
    include
    deps/glad/include
    deps/glfw/include
    deps/cglm/include
)

# internal headers for the library itself
target_include_directories(LinearRender PRIVATE src/core)

# linkage 
target_link_libraries(LinearRender PRIVATE 
    glfw 
    opengl32 
    m
)

# the demo exe
add_executable(Demo src/main.c)
target_link_libraries(Demo PRIVATE LinearRender)

file(COPY "${CMAKE_SOURCE_DIR}/shaders" 
     DESTINATION "${CMAKE_BINARY_DIR}")