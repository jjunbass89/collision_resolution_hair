cmake_minimum_required(VERSION 3.27)
project(collision_resolution_hair)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# gl3w
FetchContent_Declare(gl3w
    GIT_REPOSITORY https://github.com/skaslev/gl3w)
FetchContent_MakeAvailable(gl3w)

# glfw
FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw)
FetchContent_MakeAvailable(glfw)

# imgui
FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git)
FetchContent_MakeAvailable(imgui)
set(imgui_src ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/imgui-src)

# vtk
FetchContent_Declare(vtk
    GIT_REPOSITORY https://github.com/Kitware/VTK.git)
FetchContent_MakeAvailable(vtk)

# executable
set(EXEC_NAME test_imgui)
add_executable(${EXEC_NAME} main.cpp)
target_include_directories(${EXEC_NAME} PRIVATE ${imgui_src})