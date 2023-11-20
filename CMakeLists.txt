cmake_minimum_required(VERSION 3.27)
project(collision_resolution_hair)

set(EXEC_NAME imgui_vtk)

set_property(GLOBAL PROPERTY USE_FOLDER ON)

set(CMAKE_CXX_STANDARD 20)

set(GL3W_DIR "C:/RND/gl3w") # IDLE(python).
set(VTK_DIR "C:/RND/VTK/build") # weild build path setting.
set(MPIR_DIR "C:/Users/jjbas/.conda/pkgs/mpir-3.0.0-he025d50_1002/Library/bin") # conda.
set(FTETWILD_DIR "C:/RND/fTetWild") # mpir.

# OpenGL
find_package(OpenGL REQUIRED)

# gl3w
set(gl3w_inc ${GL3W_DIR}/include)
set(gl3w_src ${GL3W_DIR}/src/gl3w.c)
source_group(gl3w FILES ${gl3w_src})

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
source_group(imgui FILES ${imgui_src})
set(imgui_backend_src ${imgui_dir}/backends/imgui_impl_glfw.cpp ${imgui_dir}/backends/imgui_impl_opengl3.cpp)
source_group(imgui_backend FILES ${imgui_backend_src})

# ImGuiFileDialog
FetchContent_Declare(imguifiledialog
    GIT_REPOSITORY https://github.com/aiekick/ImGuiFileDialog.git)
FetchContent_Populate(imguifiledialog) # head only.
set(imguifiledialog_dir ${CMAKE_CURRENT_SOURCE_DIR}/build/_deps/imguifiledialog-src)
set(imguifiledialog_src ${imguifiledialog_dir}/ImGuiFileDialog.cpp)
source_group(imguifiledialog FILES ${imguifiledialog_src})

# imgui_vtk
set(imgui_vtk_src 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui_vtk/vtkViewer.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/imgui_vtk/vtkViewer.cpp
)
source_group(imgui_vtk FILES ${imgui_vtk_src})

# fTetWild

# ui
set(ui_src 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ui/MouseInteractorHighLightActor.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui/MouseInteractorHighLightActor.cpp 
)
source_group(ui FILES ${ui_src})

# executable
add_executable(${EXEC_NAME} 
    main.cpp 
    ${ui_src}
    ${imgui_vtk_src}

    ${gl3w_src}
    ${imgui_src}
    ${imgui_backend_src}
    ${imguifiledialog_src}
)

target_include_directories(${EXEC_NAME} PRIVATE 
    include

    ${gl3w_inc}
    ${imgui_dir}
    ${imgui_dir}/backends
    ${imguifiledialog_dir}
)

target_link_libraries(${EXEC_NAME}
    OpenGL::GL
    glfw
    ${VTK_LIBRARIES}
)

# vtk
set_target_properties(${EXEC_NAME} 
    PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY 
    ${VTK_DIR}/bin     
)

vtk_module_autoinit(
    TARGETS ${EXEC_NAME}
    MODULES ${VTK_LIBRARIES}
)