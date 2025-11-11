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

struct SPass2 {
    int itemId = -1;
    int currentScreen = 0;

};
// ------------------------------------------------------------
// Screen declarations
// ------------------------------------------------------------

void DrawCartMenu(SPass2& sPass2);
void DrawSecondScreen(SPass2& sPass2);


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

    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(nullptr);


    // --------------------------------------------------------
    // Screen state
    // --------------------------------------------------------
    enum Screen {
        SCREEN_MAIN = 0,
        SCREEN_SECOND = 1
    };
    SPass2 sPass2;
    sPass2.currentScreen = SCREEN_MAIN;


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
        switch (sPass2.currentScreen)
        {
            case SCREEN_MAIN:
                DrawCartMenu(sPass2);
                break;

            case SCREEN_SECOND:
                DrawSecondScreen(sPass2);
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

// TODO: Stop reloading the entire vector every time, update it only when searched.
// MAIN SCREEN
void DrawCartMenu(SPass2& sPass2)
{
    static char buffer[128] = ""; // empty C-string initially
    ImGui::SetNextItemWidth(240);
    ImGui::SetCursorPos(ImVec2(150, 410));
    ImGui::InputText("Search", buffer, IM_ARRAYSIZE(buffer));
    int typeSelect;
    try {
        typeSelect = stoi(buffer);
    } catch (...) {
        typeSelect = -1;
    }

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetCursorPos(ImVec2(io.DisplaySize.x / 2, 10));

    // ImGui stores text as character pointers
    ImGui::SetWindowFontScale(2.0f);
    const char* text0 = "Items";
    ImGui::SetCursorPos(ImVec2((io.DisplaySize.x - ImGui::CalcTextSize(text0).x) * 0.5f, 10));
    ImGui::Text("%s", text0);
    ImGui::SetWindowFontScale(1.0f);

    ImGui::SetCursorPos(ImVec2(io.DisplaySize.x / 2, 50));
    const char* text2 = "Items Available";
    ImGui::SetCursorPos(ImVec2((io.DisplaySize.x - ImGui::CalcTextSize(text2).x) * 0.5f, 50));
    ImGui::Text("%s", text2);


    static vector<string> items;
    items.clear();
    for (int i = 0; i < 20; ++i) {
        if (typeSelect == -1) {
            items.push_back(to_string(i));
        } else {
            if (to_string(i).find(to_string(typeSelect)) != std::string::npos) {
                items.push_back(to_string(i));
            }
        }
    }

    ImGui::SetCursorPos(ImVec2(150, 70));

    static int selected = -1;
    ImGui::BeginChild("storeCart", ImVec2(io.DisplaySize.x - 300, 200), true);
    for (int i = 0; i < items.size(); i++) {
        // c_str() gives pointer to chars inside string, ImGui needs it like this to work
        if (ImGui::Selectable(items[i].c_str(), selected == i)) {
            selected = i;
        }
    }
    ImGui::EndChild();

    ImGui::SetCursorPos(ImVec2(io.DisplaySize.x / 2, 280));
    const char* text1 = "Your Cart";
    ImGui::SetCursorPos(ImVec2((io.DisplaySize.x - ImGui::CalcTextSize(text1).x) * 0.5f, 280));
    ImGui::Text("%s", text1);

    ImGui::SetCursorPos(ImVec2(150, 300));

    ImGui::BeginChild("yourCart", ImVec2(io.DisplaySize.x - 300, 100), true);
    for (int i = 0; i < items.size(); i++) {
        // c_str() gives pointer to chars inside string, ImGui needs it like this to work
        if (ImGui::Selectable(items[i].c_str(), selected == i)) {
            selected = i;
        }
    }
    ImGui::EndChild();



    ImGui::SetCursorPos(ImVec2(150, 463.75));

    string s = "Item Selected: " + ((selected != -1) ? std::to_string(selected) : "none");
    ImGui::Text("%s", s.c_str());

    ImVec2 buttonSize(240, 60);

    if (selected != -1) {
        ImGui::SetCursorPos(ImVec2((io.DisplaySize.x - buttonSize.x) * 3 * 0.25f - 10, 440));
        if (ImGui::Button("Go To ", buttonSize)) {
            sPass2.itemId = selected;
            cout << "itemId: " << sPass2.itemId << endl;
            sPass2.currentScreen = 1;
        }
    }

    ImGui::SetCursorPos(ImVec2((io.DisplaySize.x - buttonSize.x) * 1 * 0.25f + 10, 510));
    if (ImGui::Button("Save Transaction", buttonSize)) {
        sPass2.currentScreen = 1;
    }

    ImGui::SetCursorPos(ImVec2((io.DisplaySize.x - buttonSize.x) * 3 * 0.25f - 10, 510));
    if (ImGui::Button("Cancel Transaction ", buttonSize)) {
        sPass2.currentScreen  = 1;
    }



}


// SECOND SCREEN
void DrawSecondScreen(SPass2& sPass2)
{
    if (sPass2.itemId  == -1) {
        cerr << "Item " << sPass2.itemId << " does not exist" << endl;
    }

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetWindowFontScale(2.0f);
    const char* text0 = "Menu";
    ImGui::SetCursorPos(ImVec2((io.DisplaySize.x - ImGui::CalcTextSize(text0).x) * 0.5f, 10));
    ImGui::Text("%s", text0);
    ImGui::SetWindowFontScale(1.0f);

    ImGui::SetCursorPos(ImVec2(150, 30));
    string s = "Item selected: " + std::to_string(sPass2.itemId);
    ImGui::Text("%s", s.c_str());

    ImGui::SetCursorPos(ImVec2(150, 50));
    string s1 = "Quantity in cart: " + std::to_string(6);
    ImGui::Text("%s", s1.c_str());

    ImGui::SetCursorPos(ImVec2(150, 70));
    string s2 = "Quantity available: " + std::to_string(7);
    ImGui::Text("%s", s2.c_str());
}
