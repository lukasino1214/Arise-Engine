//
// Created by lukas on 02.10.21.
//

#include "RendererAPI.h"

#include "OpenGL/OpenGLRendererAPI.h"

namespace Engine {

    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    Scope<RendererAPI> RendererAPI::Create()
    {
        switch (s_API)
        {
            case RendererAPI::API::None:    /*HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");*/ return nullptr;
            case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
        }

        //HZ_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}