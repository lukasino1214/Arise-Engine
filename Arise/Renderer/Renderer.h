//
// Created by lukas on 26.09.21.
//

#ifndef ARISE_ENGINE_RENDERER_H
#define ARISE_ENGINE_RENDERER_H

#include "RenderCommand.h"

namespace Engine {
    class Renderer {
    public:
        static void BeginScene();
        static void EndScene();
        //static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
        static void Submit(const Ref<VertexArray>& vertexArray);
        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };
}

#endif //ARISE_ENGINE_RENDERER_H
