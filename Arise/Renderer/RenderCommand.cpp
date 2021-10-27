//
// Created by lukas on 02.10.21.
//

#include "RenderCommand.h"
#include "OpenGL/OpenGLRendererAPI.h"

namespace Engine {
    Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}