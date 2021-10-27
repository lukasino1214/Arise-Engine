//
// Created by lukas on 27.09.21.
//

#include "Buffer.h"
#include "Renderer.h"
#include "OpenGL/OpenGLBuffer.h"
#include "../Core/Assert.h"

namespace Engine {
    Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:    ASSERT("RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(vertices, size);
        }

        //HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:    ASSERT("RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLIndexBuffer>(indices, size);
        }

        ASSERT("Unknown RendererAPI!");
        return nullptr;
    }
}