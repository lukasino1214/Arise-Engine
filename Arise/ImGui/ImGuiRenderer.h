//
// Created by lukas on 17.09.21.
//

#ifndef ARISE_ENGINE_IMGUIRENDERER_H
#define ARISE_ENGINE_IMGUIRENDERER_H

#include "../Core/Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

namespace Engine {
    class ImGuiRenderer {
    public:
        ImGuiRenderer(GLFWwindow* window);
        ~ImGuiRenderer();
        void begin() const;

        void end(GLFWwindow* window) const;

        //void setStyle();
    };
}

#endif //ARISE_ENGINE_IMGUIRENDERER_H
