//
// Created by lukas on 26.09.21.
//

#include "Framebuffer.h"

#include "Renderer.h"

#include "OpenGL/OpenGLFramebuffer.h"
#include "../Core/Assert.h"

namespace Engine {

    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec) {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:    ASSERT("RendererAPI::None is currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
        }

        ASSERT("Unknown RendererAPI!");
        return nullptr;
    }
}