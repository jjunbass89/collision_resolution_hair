// Standard Library
#include <iostream>

// OpenGL Loader
// This can be replaced with another loader, e.g. glad, but
// remember to also change the corresponding initialize call!
#include <GL/gl3w.h> // GL3w, initialized with gl3wInit() below

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

// ImGui + imgui-vtk
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "vtkViewer.h"

#include "ImGuiFileDialog.h"

// VTK
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkOBJReader.h>
#include <vtkPolyDataMapper.h>

int main(int argc, char *argv[])
{
    // Initialize GLFW
    if (!glfwInit())
    {
        return 1;
    }

    // Create a GLFW window
    GLFWwindow *window = glfwCreateWindow(1280, 720, "Dear ImGui VTKViewer Example", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // Initialize OpenGL loader
    if (gl3wInit() != 0) {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Initialize VtkViewer objects
    VtkViewer obj_viewer;
    vtkNew<vtkActor> obj_actor;
    auto import_obj = false;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        auto import_obj_dialog = false;
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Import"))
            {
                if (ImGui::MenuItem("OBJ"))
                {
                    import_obj_dialog = true;
                }
                ImGui::EndMenu();
            }
        }
	
        ImGui::EndMainMenuBar();

        if (import_obj_dialog)
        {
            ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Import obj file", ".obj", "C:/RND/sample/");
		}

        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
        {
            // action if OK
            if (ImGuiFileDialog::Instance()->IsOk())
            {
                std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                
                vtkNew<vtkOBJReader> reader;
                reader->SetFileName(filePathName.c_str());
                reader->Update();

                vtkNew<vtkPolyDataMapper> mapper;
                mapper->SetInputConnection(reader->GetOutputPort());

                obj_actor->SetMapper(mapper);

                import_obj = true;
            }

            // close
            ImGuiFileDialog::Instance()->Close();
        }

        if (import_obj)
        {
            ImGui::SetNextWindowSize(ImVec2(280, 300), ImGuiCond_FirstUseEver);
            ImGui::Begin("obj viewer", nullptr, VtkViewer::NoScrollFlags());
            
            obj_viewer.addActor(obj_actor);
            obj_viewer.render();
            
            ImGui::End();
        }

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}