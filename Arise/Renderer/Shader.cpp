//
// Created by lukas on 26.09.21.
//

#include "Shader.h"

#include "OpenGL/OpenGLShader.h"
#include "Renderer.h"
#include "../Core/Assert.h"
//#include <vector>

namespace Engine {
    Ref<Shader> Shader::Create(const std::string& filepath) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:    ASSERT("RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(filepath);
        }

        ASSERT("Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:    ASSERT("RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(vertexSrc, fragmentSrc);
        }

        ASSERT("Unknown RendererAPI!");
        return nullptr;
    }
}
