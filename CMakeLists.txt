cmake_minimum_required(VERSION 3.27)
project(collision_resolution_hair)

set(CMAKE_CXX_STANDARD 20)

set(GL3W_DIR "C:/RND/gl3w")
set(VTK_DIR "C:/RND/VTK-9.3.0/build")

# OpenGL
find_package(OpenGL REQUIRED)

# gl3w
set(gl3w_inc ${GL3W_DIR}/include)
set(gl3w_src ${GL3W_DIR}/src/gl3w.c)

include(FetchContent)

# glfw
FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw)
FetchContent_MakeAvailable(glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# vtk
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

# ImGuiFileDialog
FetchContent_Declare(imguifiledialog
    GIT_REPOSITORY https://github.com/aiekick/ImGuiFileDialog.git)
set(imguifiledialog_dir ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/imguifiledialog-src)

# executable
set(EXEC_NAME imgui_vtk)
add_executable(${EXEC_NAME} 
    main.cpp 
    ${gl3w_src}
    ${imgui_src}
    ${imgui_backend}
    ${imgui_vtk_viewer_src}
    ${imgui_dir}/imgui.h
    ${imguifiledialog_dir}/ImGuiFileDialog.cpp
)

target_include_directories(${EXEC_NAME} PRIVATE 
    ${gl3w_inc}
    ${imgui_dir}
    ${imgui_dir}/backends
    ${imgui_vtk_viewer_dir}
    ${imgui_dir}/imgui.h
    ${imguifiledialog_dir}
)

target_link_libraries(${EXEC_NAME}
    OpenGL::GL
    glfw
    ${VTK_LIBRARIES}
)

set_target_properties(${EXEC_NAME} 
    PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY 
    ${VTK_DIR}/bin
)

vtk_module_autoinit(
    TARGETS ${EXEC_NAME}
    MODULES ${VTK_LIBRARIES}
)