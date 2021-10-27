//
// Created by lukas on 17.09.21.
//

#ifndef ARISE_ENGINE_WINDOW_H
#define ARISE_ENGINE_WINDOW_H


#include <memory>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine {
    class Window {
    public:
        Window();
        Window(uint32_t width, uint32_t height);
        Window(GLFWwindow* window);
        void Update();
        void Close();

        GLFWwindow* GetWindow() { return m_Window; }

    private:
        GLFWwindow* m_Window;
    };
}

#endif //ARISE_ENGINE_WINDOW_H
