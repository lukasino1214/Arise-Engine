#include "Window.h"
#include "../Renderer/OpenGL/OpenGLGraphicsContext.h"

namespace Engine {
    Window::Window() {
        glfwInit();
        m_Window = glfwCreateWindow(1280, 720, "ARISE ENGINE", nullptr, nullptr);
        if (m_Window == nullptr) {
            //std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(m_Window);
        OpenGLContext Context(m_Window);
        Context.Init();
    }

    Window::Window(uint32_t width, uint32_t height) {
        glfwInit();
        m_Window = glfwCreateWindow(width, height, "ARISE ENGINE", nullptr, nullptr);
        if (m_Window == nullptr) {
            //std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(m_Window);
        OpenGLContext Context(m_Window);
        Context.Init();
    }

    Window::Window(GLFWwindow *window) : m_Window(window) {}

    void Window::Update() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void Window::Close() {
        glfwSetWindowShouldClose(m_Window, true); //
    }
}
