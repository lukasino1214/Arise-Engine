//
// Created by lukas on 26.09.21.
//

#include "Renderer.h"

namespace Engine {
    void Renderer::BeginScene() {

    }

    void Renderer::EndScene() {

    }

    /*void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray) {
        RenderCommand::DrawIndexed(vertexArray);
    }*/

    void Renderer::Submit(const Ref<VertexArray>& vertexArray) {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}
