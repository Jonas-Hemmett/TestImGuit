cmake_minimum_required(VERSION 3.30.5)
project(TestImGui)

set(CMAKE_CXX_STANDARD 20)

include_directories(imgui)
include_directories(imgui/backends)
include_directories(glfw/include)

link_directories(glfw/lib)

add_executable(Demo
        Demo.cpp

        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp

        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl3.cpp
)


add_executable(Test
        Test.cpp

        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp

        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl3.cpp
)
target_link_libraries(Demo
        glfw3
        opengl32
)

target_link_libraries(Test
        glfw3
        opengl32
)
