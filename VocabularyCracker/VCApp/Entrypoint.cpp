#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <GLFW/glfw3.h>
#include <Windows.h>

#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>

// Main code
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    if (!glfwInit())
        return 1;

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Vocabulary Cracker", nullptr, nullptr);
    if (window == nullptr)
        return 1;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    std::unordered_map<std::string, unsigned int> confirmedWords;

    std::string input;
    std::ifstream readLog("C:\\Programs\\VocabularyCracker\\VocabularyCracker\\VCCore\\User Data\\Log.txt");
    while (std::getline(readLog, input))
    {
        std::stringstream line(input);

        std::string word;
        std::getline(line, word, ' ');
        std::string count;
        std::getline(line, count, ' ');

        confirmedWords[word] = std::stoi(count);
    }
    readLog.close();

    // Setup Dear ImGui context
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // This single line breaks EVERYTHING
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_NoUndocking | ImGuiDockNodeFlags_AutoHideTabBar;
    ImGuiWindowFlags dockWindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    dockWindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    dockWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGuiWindowFlags basicWindowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
    basicWindowFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad | ImGuiConfigFlags_DockingEnable;
    basicWindowFlags |= ImGuiWindowFlags_NoCollapse;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //Frame content
        //Dockspace Window
        {
            ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

            ImGui::Begin("Dockspace Window", nullptr, dockWindowFlags);
            ImGui::PopStyleVar();

            ImGui::BeginMainMenuBar();
            ImGui::MenuItem("Hello world");
            ImGui::EndMainMenuBar();

            ImGui::DockSpace(ImGui::GetID("Dockspace"), ImVec2(0.0f, 0.0f), dockspaceFlags);
            ImGui::End();
        }

        // SideBar window
        {
            ImGui::Begin("SideBar", nullptr, basicWindowFlags);
            ImGui::Text("This is text");
            ImGui::End();
        }

        // Main window
        {
            ImGui::Begin("Main", nullptr, basicWindowFlags);
            ImGui::Text("This is main window text");

            for (auto words : confirmedWords)
            {
                ImGui::Text("%s, %d", words.first.c_str(), words.second);
            }

            ImGui::End();
        }

        // Rendering
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
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