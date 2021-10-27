//
// Created by lukas on 02.10.21.
//

#include "VertexArray.h"
#include "Renderer.h"
#include "OpenGL/OpenGLVertexArray.h"
#include "../Core/Assert.h"

namespace Engine {
    Ref<VertexArray> VertexArray::Create() {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:    ASSERT("RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
        }

        ASSERT("Unknown RendererAPI!");
        return nullptr;
    }
}