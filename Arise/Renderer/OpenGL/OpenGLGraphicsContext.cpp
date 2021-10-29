//
// Created by lukas on 26.09.21.
//

#include "OpenGLGraphicsContext.h"

#include "../../Core/Log.h"

namespace Engine {
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {}

    void OpenGLContext::Init() {
        glfwMakeContextCurrent(m_WindowHandle);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            //std::cout << "Failed to initialize GLAD" << std::endl;
            //return -1;
        }

        Log::Init();
        CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
        CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }
}

