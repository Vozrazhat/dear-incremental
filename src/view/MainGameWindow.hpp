#pragma once
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "../viewmodel/MainGameViewModel.hpp"

namespace DI {
class MainGameWindow {
public:
    MainGameWindow(MainGameViewModel &view_model);
    ~MainGameWindow();

    void run();

    // No copying or any of that nonsense. This owns OpenGL and window resources.
    MainGameWindow(const MainGameWindow &other) = delete;
    MainGameWindow &operator=(const MainGameWindow &other) = delete;
    MainGameWindow(MainGameWindow &&other) = delete;
    MainGameWindow &operator=(MainGameWindow &&other) = delete;

private:
    MainGameViewModel &view_model_;
    GLFWwindow *window_;
    const char *glsl_version_ = "#version 330";

    void initGLFW();
    void initImGui();
};

} // namespace DI
