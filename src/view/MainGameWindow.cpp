#include "MainGameWindow.hpp"
#include "../common/Resource.hpp"
#include "../model/MainGameState.hpp"
#include "../viewmodel/MainGameViewModel.hpp"
#include <spdlog/spdlog.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <format>

namespace DI {

static void glfw_error_callback(int error, const char *description) {
    SPDLOG_ERROR("Glfw Error {}: {}\n", error, description);
}

MainGameWindow::MainGameWindow(MainGameViewModel &view_model) : view_model_(view_model) {
    initGLFW();
    initImGui();
}

MainGameWindow::~MainGameWindow() {
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window_);
    glfwTerminate();
}

void MainGameWindow::run() {
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 0.8f);

    while (!glfwWindowShouldClose(window_)) {

        glfwPollEvents();
        if (glfwGetWindowAttrib(window_, GLFW_ICONIFIED) != 0) {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Imgui Running");
            ImGui::ColorEdit4("WindowColor", &clear_color.x);
            ImGui::End();
        }

        {
            ImGui::Begin("Neurons");
            ImGui::Text(std::format("{:.0f}", view_model_.getValue(Resource::NEURONS)).c_str());
            // if (ImGui::Button("Add 1 to big number")) {
            //     view_model_.incrementNeurons();
            // }
            ImGui::End();
        }

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window_, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window_);
    }
}

void MainGameWindow::initGLFW() {
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        SPDLOG_ERROR("Failed to init glfw");
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    window_ = glfwCreateWindow(1920, 1080, "Dear Incremental", NULL, NULL);
    if (window_ == NULL) {
        SPDLOG_ERROR("Failed to create glfw Window");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window_);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    // glfwSwapInterval(1); // Enables Vsync. Still not sure I need this.
    glfwSwapInterval(0); // Disables Vsync.
}

void MainGameWindow::initImGui() {
    // Set up IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;                                             // What is this doing?
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init(glsl_version_);
}
} // namespace DI
