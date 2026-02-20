#include "engine/App.h"
#include "engine/Game.h"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "engine/debug/openglErrorReporting.h"

namespace
{
    static void error_callback(int error, const char* description)
    {
        std::cout << "GLFW Error(" << error << "): " << description << "\n";
    }
}

namespace engine
{
    App::App(int width, int height, const char* title)
        : mWidth(width), mHeight(height), mTitle(title)
    {
    }

    App::~App()
    {
        Shutdown();
    }

    int App::Run(Game& game)
    {
        if (!Init())
            return -1;

        if (!game.Load())
        {
            Shutdown();
            return -1;
        }

        auto* window = reinterpret_cast<GLFWwindow*>(mWindow);

        while (!glfwWindowShouldClose(window))
        {
            float dt = CalcDeltaTime();

            FrameBegin();
            game.Update(dt);
            game.Render();
            FrameEnd();
        }

        game.Unload();
        Shutdown();
        return 0;
    }

    bool App::Init()
    {
        glfwSetErrorCallback(error_callback);
        if (!glfwInit()) return false;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(mWidth, mHeight, mTitle, nullptr, nullptr);
        if (!window)
        {
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        mWindow = window;

        if (!InitGL())
            return false;

        return true;
    }

    bool App::InitGL()
    {
        auto* window = reinterpret_cast<GLFWwindow*>(mWindow);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            glfwDestroyWindow(window);
            mWindow = nullptr;
            glfwTerminate();
            return false;
        }

        enableReportGlErrors();
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        return true;
    }

    float App::CalcDeltaTime()
    {
        static double last = glfwGetTime();
        double now = glfwGetTime();
        double dt = now - last;
        last = now;
        return static_cast<float>(dt);
    }

    void App::FrameBegin()
    {
        auto* window = reinterpret_cast<GLFWwindow*>(mWindow);

        int width = 0, height = 0;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void App::FrameEnd()
    {
        auto* window = reinterpret_cast<GLFWwindow*>(mWindow);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void App::Shutdown()
    {
        // 이미 종료된 경우
        if (!mWindow) return;

        auto* window = reinterpret_cast<GLFWwindow*>(mWindow);
        glfwDestroyWindow(window);
        mWindow = nullptr;

        glfwTerminate();
    }
}