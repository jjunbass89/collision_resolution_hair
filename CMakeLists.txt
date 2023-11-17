cmake_minimum_required(VERSION 3.27)
project(collision_resolution_hair)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# OpenGL
find_package(OpenGL REQUIRED)

# gl3w
FetchContent_Declare(gl3w
    GIT_REPOSITORY https://github.com/skaslev/gl3w)
FetchContent_MakeAvailable(gl3w)
set(gl3w_dir ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/gl3w-src)
set(gl3w_inc ${gl3w_dir}/include)
set(gl3w_src ${gl3w_dir}/src/gl3w.c)

# glfw
FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw)
FetchContent_MakeAvailable(glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# vtk
set(VTK_DIR "C:/RND/VTK-9.3.0/build")
find_package(VTK REQUIRED)

# imgui
FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git)
FetchContent_MakeAvailable(imgui)
set(imgui_dir ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/imgui-src)
file(GLOB imgui_src ${imgui_dir}/*.cpp)
set(imgui_backend ${imgui_dir}/backends/imgui_impl_glfw.cpp ${imgui_dir}/backends/imgui_impl_opengl3.cpp)

# imgui-vtk
set(imgui_vtk_viewer_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(imgui_vtk_viewer_src ${imgui_vtk_viewer_dir}/vtkViewer.cpp)

# executable
set(EXEC_NAME imgui_vtk)
add_executable(${EXEC_NAME} 
    main.cpp 
    ${gl3w_src}
    ${imgui_src}
    ${imgui_backend}
    ${imgui_vtk_viewer_src}
)

target_include_directories(${EXEC_NAME} PRIVATE 
    ${gl3w_inc}
    ${imgui_dir}
    ${imgui_dir}/backends
    ${imgui_vtk_viewer_dir}
)

target_link_libraries(${EXEC_NAME}
    OpenGL::GL
    glfw
    ${VTK_LIBRARIES}
)

set_target_properties(${EXEC_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY 
    ${VTK_DIR}/bin)

vtk_module_autoinit(
    TARGETS ${EXEC_NAME}
    MODULES ${VTK_LIBRARIES}
)