#include "Application.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <Windows.h>

#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>

Application::Application()
{
    if (!glfwInit())
        m_State = State::CRASH;

    // Create window with graphics context
    m_Window = glfwCreateWindow(1080, 720, "Vocabulary Cracker", nullptr, nullptr);
    if (m_Window == nullptr)
        m_State = State::CRASH;

    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);

    // Setup Dear ImGui context
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // This single line breaks EVERYTHING
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void Application::Run()
{
    while (!glfwWindowShouldClose(m_Window))
    {
        Update();
    }
}

Application::~Application()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Application::Update()
{
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();

    //Frame content
    //Dockspace Window
    {
        ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_NoUndocking | ImGuiDockNodeFlags_AutoHideTabBar;
        ImGuiWindowFlags dockWindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        dockWindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        dockWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

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

    ImGuiWindowFlags basicWindowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
    basicWindowFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad | ImGuiConfigFlags_DockingEnable;
    basicWindowFlags |= ImGuiWindowFlags_NoCollapse;

    // SideBar window
    {
        ImGui::Begin("SideBar", nullptr, basicWindowFlags);
        ImGui::Text("This is text");
        ImGui::End();
    }

    // Main window
    {
        ImGui::Begin("Main", nullptr, basicWindowFlags);

        switch (m_State)
        {
        case Application::State::CRASH:
            glfwSetWindowShouldClose(m_Window, true);
            break;

        case Application::State::LOGVIEW:
            LogView();
            break;

        case Application::State::DICTIONARYVIEW:
            DictionaryView();
            break;

        case Application::State::SETTINGSVIEW:
            SettingsView();
            break;
        }

        ImGui::End();
    }

    // Rendering
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(m_Window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_Window);
}

void Application::LogView()
{
    std::vector<std::pair<std::string, int>> confirmedWords;

    std::string input;
    std::ifstream readLog("../VCCore/User Data/Log.txt");
    while (std::getline(readLog, input))
    {
        std::stringstream line(input);
        std::pair<std::string, int> word;

        std::getline(line, word.first, ' ');
        std::string count;
        std::getline(line, count, ' ');
        word.second = std::stoi(count);

        confirmedWords.push_back(word);
    }
    readLog.close();

    ImGui::Text("Sorting Options:");
    ImGui::Separator();

    ImGui::Text("By Count ");
    ImGui::SameLine();
    if (ImGui::Button("Ascending"))
    {
        std::sort(confirmedWords.begin(), confirmedWords.end(),
            [](auto& left, auto& right)
            {
                return left.second > right.second;
            });
    }
    ImGui::SameLine();
    if (ImGui::Button("Descending"))
    {
        std::sort(confirmedWords.begin(), confirmedWords.end(),
            [](auto& left, auto& right)
            {
                return left.second < right.second;
            });
    }

    ImGui::Text("By Length");
    ImGui::SameLine();
    if (ImGui::Button("Ascending##1"))
    {
        std::sort(confirmedWords.begin(), confirmedWords.end(),
            [](auto& left, auto& right)
            {
                return left.first.length() > right.first.length();
            });
    }
    ImGui::SameLine();
    if (ImGui::Button("Descending##1"))
    {
        std::sort(confirmedWords.begin(), confirmedWords.end(),
            [](auto& left, auto& right)
            {
                return left.first.length() < right.first.length();
            });
    }

    ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable;

    if (ImGui::BeginTable("word table", 2, flags))
    {
        ImGui::TableSetupColumn("Word", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("Count", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableHeadersRow();

        for (auto words : confirmedWords)
        {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("%s", words.first.c_str());
            ImGui::TableNextColumn();
            ImGui::Text("%d", words.second);
        }
        ImGui::EndTable();
    }
}

void Application::DictionaryView()
{
}

void Application::SettingsView()
{
}
