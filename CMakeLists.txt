cmake_minimum_required(VERSION 3.27)
project(collision_resolution_hair)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# imgui
FetchContent_Declare(imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git)
FetchContent_MakeAvailable(imgui)
set(imgui_src ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/imgui-src)

# executable
set(EXEC_NAME test_imgui)
add_executable(${EXEC_NAME} main.cpp)
target_include_directories(${EXEC_NAME} PRIVATE ${imgui_src})