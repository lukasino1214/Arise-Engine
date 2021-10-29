//
// Created by lukas on 02.10.21.
//

#ifndef ARISE_ENGINE_RENDERCOMMAND_H
#define ARISE_ENGINE_RENDERCOMMAND_H

#include "RendererAPI.h"
//#include "VertexArray.h"

namespace Engine {
    class RenderCommand {
    public:
        static void Init() {
            s_RendererAPI->Init();
        }

        static void SetClearColor(const glm::vec4& color) {
            s_RendererAPI->SetClearColor(color);
        }

        static void Clear() {
            s_RendererAPI->Clear();
        }

        static void DrawIndexed(const Ref<VertexArray>& vertexArray) {
            s_RendererAPI->DrawIndexed(vertexArray);
        }

        static void Draw(const Ref<VertexArray>& vertexArray) {
            s_RendererAPI->Draw(vertexArray);
        }

        /*static void Draw(const Ref<VertexArray>& vertexArray) {
            s_RendererAPI->DrawIndexed(vertexArray);
        }*/
    private:
        static Scope<RendererAPI> s_RendererAPI;
    };

}



#endif //ARISE_ENGINE_RENDERCOMMAND_H
