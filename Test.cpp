// See code from Demo

// https://www.youtube.com/watch?v=790aMkbsBm8&t=4014s
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
using namespace std;
// ------------------------------------------------------------
// Screen declarations
// ------------------------------------------------------------
void DrawMainScreen(int& screen);
void DrawSecondScreen(int& screen);


// ------------------------------------------------------------
// Error callback for GLFW
// ------------------------------------------------------------
static void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}


// ------------------------------------------------------------
// MAIN
// ------------------------------------------------------------
int main()
{
    // --------------------------------------------------------
    // GLFW setup
    // --------------------------------------------------------
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Register", NULL, NULL);
    if (window == NULL)
        return -1;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);


    // --------------------------------------------------------
    // ImGui setup
    // --------------------------------------------------------
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(nullptr);


    // --------------------------------------------------------
    // Screen state
    // --------------------------------------------------------
    enum Screen {
        SCREEN_MAIN = 0,
        SCREEN_SECOND = 1
    };

    int currentScreen = SCREEN_MAIN;


    // --------------------------------------------------------
    // Main loop
    // --------------------------------------------------------
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        // --------------------------------------------------------
        // Fullscreen window
        // --------------------------------------------------------
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(io.DisplaySize);

        ImGuiWindowFlags flags =
              ImGuiWindowFlags_NoDecoration
            | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoSavedSettings
            | ImGuiWindowFlags_NoBringToFrontOnFocus
            | ImGuiWindowFlags_NoNavFocus;

        ImGui::Begin("FullWindow", nullptr, flags);


        // --------------------------------------------------------
        // Call the current screen function
        // --------------------------------------------------------
        switch (currentScreen)
        {
            case SCREEN_MAIN:
                DrawMainScreen(currentScreen);
                break;

            case SCREEN_SECOND:
                DrawSecondScreen(currentScreen);
                break;
        }

        ImGui::End();


        // --------------------------------------------------------
        // Render
        // --------------------------------------------------------
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(0.13f, 0.13f, 0.13f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }


    // --------------------------------------------------------
    // Cleanup
    // --------------------------------------------------------
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


// ------------------------------------------------------------
// SCREEN IMPLEMENTATIONS
// ------------------------------------------------------------

// MAIN SCREEN
void DrawMainScreen(int& screen)
{
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 buttonSize(300, 120);

    float centerX = (io.DisplaySize.x - buttonSize.x) * 0.5f;
    float centerY = (io.DisplaySize.y - buttonSize.y) * 0.5f;

    static const vector<char*> items = { "A", "B" };
    ImGui::SetCursorPos(ImVec2(0, 0));

    static int selected = -1;
    ImGui::BeginChild("Scroll", ImVec2(io.DisplaySize.x, 200), true);
    for (int i = 0; i < items.size(); i++) {
        if (ImGui::Selectable(items[i]), selected == i) {
            selected = i;
        }
    }
    ImGui::EndChild();
    if (selected >= 0) cout << "Selected: " << items[selected] << endl;
    ImGui::SetCursorPos(ImVec2(centerX, centerY));

    if (ImGui::Button("Go To Second Screen", buttonSize))
        screen = 1;
}


// SECOND SCREEN
void DrawSecondScreen(int& screen)
{
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 buttonSize(300, 120);

    float centerX = (io.DisplaySize.x - buttonSize.x) * 0.5f;
    float centerY = (io.DisplaySize.y - buttonSize.y) * 0.5f;

    ImGui::SetCursorPos(ImVec2(centerX, centerY));
    ImGui::Text("Welcome to the SECOND SCREEN!");

    ImGui::SetCursorPos(ImVec2(centerX, centerY + 100));

    if (ImGui::Button("Back", buttonSize))
        screen = 0;
}
