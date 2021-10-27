//
// Created by lukas on 26.09.21.
//

#ifndef ARISE_OPENGLGRAPHICSCONTEXT_H
#define ARISE_OPENGLGRAPHICSCONTEXT_H

#include "../GraphicsContext.h"
#include "../../Core/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Engine {
    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow* windowHandle);
        void Init() override;
        void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };
}

#endif //ARISE_OPENGLGRAPHICSCONTEXT_H
